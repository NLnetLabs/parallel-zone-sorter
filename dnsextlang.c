/* Copyright (c) 2019, NLnet Labs. All rights reserved.
 * 
 * This software is open source.
 * 
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 
 * Redistributions of source code must retain the above copyright notice,
 * this list of conditions and the following disclaimer.
 * 
 * Redistributions in binary form must reproduce the above copyright notice,
 * this list of conditions and the following disclaimer in the documentation
 * and/or other materials provided with the distribution.
 * 
 * Neither the name of the NLNET LABS nor the names of its contributors may
 * be used to endorse or promote products derived from this software without
 * specific prior written permission.
 * 
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 * HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED
 * TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
 * PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
 * LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
 * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */
#include "dnsextlang.h"
#include "parser.h"
#include <assert.h>
#include <ctype.h>
#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/types.h>

dnsextlang_stanza *dnsextlang_stanza_free(dnsextlang_stanza *s)
{
	if (s) {
		if (s->name)
			free((char *)s->name);
		if (s->description)
			free((char *)s->description);
		free(s);
	}
	return NULL;
}

static status_code dnsextlang_def_add_stanza(
    dnsextlang_def *d, dnsextlang_stanza *s, return_status *st)
{
	dnsextlang_rrradix **rrr_p;
	const char *name;

	assert(d);
	assert(s);
	assert(s->name);

	if (!d->stanzas_hi[s->number >> 8]) {
		d->stanzas_hi[s->number >> 8]
		    = calloc(256, sizeof(dnsextlang_stanza *));
	} else if (d->stanzas_hi[s->number >> 8][s->number & 0x00FF]) {
		rrr_p = &d->rrradix;
		name = s->name;

		while (*name && *rrr_p) {
			rrr_p = &(*rrr_p)->next_char
			                   [(toupper(*name) - '-') & 0x2F];
			name++;
		}
		if (*rrr_p && !*name) {
			assert((*rrr_p)->has_rrtype == 1);
			assert((*rrr_p)->rrtype == s->number);

			(*rrr_p)->has_rrtype = 0;
			(*rrr_p)->rrtype = 0;
		}
		dnsextlang_stanza_free(
		    d->stanzas_hi[s->number >> 8][s->number & 0x00FF]);
	}
	d->stanzas_hi[s->number >> 8][s->number & 0x00FF] = s;
	
	rrr_p = &d->rrradix;
	name = s->name;
	for (;;) {
		if (!*rrr_p)
			*rrr_p = calloc(1, sizeof(dnsextlang_rrradix));
		if (!*name)
			break;
		rrr_p = &(*rrr_p)->next_char[(toupper(*name) - '-') & 0x2F];
		name++;
	}
	if ((*rrr_p)->has_rrtype && (*rrr_p)->rrtype != s->number) {
		uint8_t to_rm_hi = (*rrr_p)->rrtype >> 8;
		uint8_t to_rm_lo = (*rrr_p)->rrtype & 0x00FF;

		if (d->stanzas_hi[to_rm_hi]
		 && d->stanzas_hi[to_rm_hi][to_rm_lo]) {
			dnsextlang_stanza_free(
			    d->stanzas_hi[to_rm_hi][to_rm_lo]);
			d->stanzas_hi[to_rm_hi][to_rm_lo] = NULL;
		}
	}
	(*rrr_p)->has_rrtype = 1;
	(*rrr_p)->rrtype = s->number;
	return STATUS_OK;
}

static const char *p_del_strdup(const char *start, const char *end)
{
	char *str;

	if (!start || !end)
		return (const char *)calloc(1, 1);

	assert(end > start);
	if (!(str = (char *)malloc(end - start + 1)))
		return NULL;
	(void) memcpy(str, start, end - start);
	str[end - start] = 0;
	return str;
}

static int p_scan_ftype(const char **p, const char *e)
{
	if (*p >= e) return -1;
	switch (toupper(*(*p)++)) {
	case 'I': if (*p >= e) return -1;
                  switch (*(*p)++) {
                  case '1': return del_ftype_I1;
                  case '2': return del_ftype_I2;
                  case '4': return del_ftype_I4;
	          default : return -1;
	          }
	case 'A': if (*p >= e || toupper(**p) != 'A')
	                  return del_ftype_A;
	          else if (++(*p) + 1 >= e || toupper(**p) != 'A'
	                                   || toupper((*p)[1]) != 'A')
	                  return del_ftype_AA;
		  else {
			  *p += 2;
	                  return del_ftype_AAAA;
		  }
	case 'X': if (*p >= e) return del_ftype_X;
                  switch ((*p)[1]) {
                  case '6': *p += 1;
			    return del_ftype_X6;
                  case '8': *p += 1;
			    return del_ftype_X8;
	          default : return del_ftype_X;
	          }
	case 'T': if (*p >= e || (*p)[1] != '6')
			  return del_ftype_T;
		  else {
			  *p += 1;
			  return del_ftype_T6;
		  }
	case 'E': if (*p + 4 >= e
	          ||  toupper((*p)[0]) != 'U'
		  ||  toupper((*p)[1]) != 'I') return -1;
		  if (toupper((*p)[2]) == '4'
	          &&  toupper((*p)[3]) == '8') {
			  *p += 4;
			  return del_ftype_EUI48;
		  }
		  if (toupper((*p)[2]) == '6'
	          &&  toupper((*p)[3]) == '4') {
			  *p += 4;
			  return del_ftype_EUI64;
		  }
		  return -1;
	case 'R': return del_ftype_R;
	case 'N': return del_ftype_N;
	case 'S': return del_ftype_S;
	case 'B': if (*p + 2 >= e) return -1;
	          if ((*p)[0] == '3' && (*p)[1] == '2') {
			  *p += 2;
			  return del_ftype_B32;
		  }
	          if ((*p)[0] == '6' && (*p)[1] == '4') {
			  *p += 2;
			  return del_ftype_B64;
		  }
		  return -1;
	case 'Z': return del_ftype_Z;
	default : return -1;
	}
}

dnsextlang_stanza *dnsextlang_stanza_new_from_pieces(
   parse_piece *piece, size_t n_pieces, return_status *st)
{
	dnsextlang_stanza *r;
	const char *s, *e;
	char numbuf[6], *endptr;
	unsigned long int n;
	dnsextlang_field *f;
       
	assert(piece);
	assert(n_pieces);

	r = calloc(1, sizeof(dnsextlang_stanza)
	            + sizeof(dnsextlang_field) * (n_pieces - 1));
	if (!r)
		return NULL;

	if (piece->end <= piece->start || !isalpha(*piece->start))
		return dnsextlang_stanza_free(r); /* syntax error */

	for (s = e = piece->start; e < piece->end; e++)
		if (!isalnum(*e) && *e != '-')
			break;
	if (e >= piece->end || *e != ':')
		return dnsextlang_stanza_free(r); /* syntax error */
	r->name = p_del_strdup(s, e);

	for (s = ++e; e < piece->end; e++)
		if (!isdigit(*e) && *e != '-')
			break;
	if (e == s || e - s > sizeof(numbuf) - 1)
		return dnsextlang_stanza_free(r); /* syntax error */

	(void)memcpy(numbuf, s, e - s);
	numbuf[e - s] = 0;
	n = strtoul(numbuf, &endptr, 10);
	if (*endptr || n > 65535)
		return dnsextlang_stanza_free(r); /* syntax error */
	r->number = n;

	if (e < piece->end && *e == ':') {
		for (s = ++e; e < piece->end; e++)
			if (isalpha(*e))
				r->options[toupper(*e) - 'A'] = 1;
			else
				break;
	}
	if (e < piece->end) {
		if (!isspace(*e))
			return dnsextlang_stanza_free(r); /* syntax error */
		/* trim whitespace */
		for (s = ++e; s < piece->end && isspace(*s); s++)
			; /* pass */
		for (e = piece->end - 1; e > s && isspace(*e); e--)
			; /* pass */
		if (e > s)
			r->description = p_del_strdup(s, e);
	}
	r->n_fields = --n_pieces;
	piece++;
	for (f = r->fields; n_pieces > 0; n_pieces--, f++, piece++) {
		int ft;

		s = e = piece->start;
		ft = p_scan_ftype(&e, piece->end);
		if (ft < 0)
			return dnsextlang_stanza_free(r); /* syntax error */
		f->ftype = ft;
		if (e >= piece->end)
			continue;
		if (*e == '[') {
		}
	}
	return r;
}

static inline parser *p_dfi_return(parser *p, return_status *st)
{
	if (p->cur_piece == p->pieces && !p->cur_piece->start) {
		assert(p->cur == p->end);
		(void) parser_free_in_use(p, NULL);
		return NULL;
	}
	if (p->cur_piece->start && !p->cur_piece->end) {
		p->cur_piece->end = p->cur;
		p->cur_piece += 1;
		p->cur_piece->start = NULL;
	}
	assert(p->pieces->start);
	p->start = p->pieces->start;
	return parser_progressive_munmap(p, st) ? NULL : p;
}

static inline parser *p_dfi_get_fields(parser *p, return_status *st)
{
	while (p->cur < p->end) {
		p->sol = p->cur;

		if (isalpha(*p->cur)) /* Start of stanza */
			return p_dfi_return(p, st);

		while (*p->cur != '\n' && isspace(*p->cur)) {
			if (++p->cur >= p->end)
				return p_dfi_return(p, st);
		}
		switch (*p->cur) {
		case '#' :
			if (++p->cur >= p->end)
				return p_dfi_return(p, st);
			while (*p->cur != '\n') {
				if (++p->cur >= p->end)
					return p_dfi_return(p, st);
			}
			p->cur += 1;
			p->line_nr += 1;
			break;
		case '\n':
			p->cur += 1;
			p->line_nr += 1;
			break;
		default:
			/* Start of field */
			if (equip_cur_piece(p, st))
				return NULL;
			while (*p->cur != '\n' && *p->cur != '#') {
				if (p->cur[0] == '\\' && p->cur + 1 < p->end
				&&  p->cur[1] == '\n') {
					p->line_nr += 1;
					p->cur += 1;
				}
				if (++p->cur >= p->end)
					return p_dfi_return(p, st);
			}
			if (increment_cur_piece(p, st))
				return NULL;

			if (*p->cur == '#') {
				p->cur += 1;
				while (*p->cur != '\n') {
					if (++p->cur >= p->end)
						return p_dfi_return(p, st);
				}
			}
			p->cur += 1;
			p->line_nr += 1;
			break;
		}
	}
	return p_dfi_return(p, st);
}

static inline parser *p_dfi_next(parser *p, return_status *st)
{
	if (reset_cur_piece(p, st))
		return NULL;
	while (p->cur < p->end) {
		p->sol = p->cur;

		if (isalpha(*p->cur)) {
			if (equip_cur_piece(p, st))
				return NULL;
			if (++p->cur >= p->end)
				return p_dfi_return(p, st);
			while (*p->cur != '\n' && *p->cur != '#') {
				if (p->cur[0] == '\\' && p->cur + 1 < p->end
				&&  p->cur[1] == '\n') {
					p->line_nr += 1;
					p->cur += 1;
				}
				if (++p->cur >= p->end)
					return p_dfi_return(p, st);
			}
			if (increment_cur_piece(p, st))
				return NULL;
			if (*p->cur == '#') {
				p->cur += 1;
				while (*p->cur != '\n') {
					if (++p->cur >= p->end)
						return p_dfi_return(p, st);
				}
			}
			p->cur += 1;
			p->line_nr += 1;
			return p_dfi_get_fields(p, st);
		}
		while (*p->cur != '\n' && isspace(*p->cur)) {
			if (++p->cur >= p->end)
				return p_dfi_return(p, st);
		}
		switch (*p->cur) {
		case '#' :
			if (++p->cur >= p->end)
				return p_dfi_return(p, st);
			while (*p->cur != '\n') {
				if (++p->cur >= p->end)
					return p_dfi_return(p, st);
			}
			p->cur += 1;
			p->line_nr += 1;
			break;
		case '\n':
			p->cur += 1;
			p->line_nr += 1;
			break;
		default:
			(void) RETURN_PARSE_ERR(st,
			    "dnsextlang stanza's start at beginning of a line",
			    p->fn, p->line_nr, p->cur - p->sol);
			return NULL;
		}
	}
	return p_dfi_return(p, st);
}

dnsextlang_def *p_dfi2def(dns_config *cfg, parser *i, return_status *st)
{
	dnsextlang_def *d = calloc(1, sizeof(dnsextlang_def));

	if (!d) {
		(void) RETURN_MEM_ERR(st,
		    "cannot allocate space for dnsextlang definitions");
		return NULL;
	}

	while ((i = p_dfi_next(i, st))) {
		dnsextlang_stanza *s;

		if (!(s = dnsextlang_stanza_new_from_pieces(
		    i->pieces, (i->cur_piece - i->pieces), st)))
			break;

		if (dnsextlang_def_add_stanza(d, s, st))
			break;
	}
	if (i) parser_free_in_use(i, NULL);
	// TODO! return st->code ? dnsexitlang_def_free(d) : d;
	return st->code ? NULL : d;
}

dnsextlang_def *dnsextlang_def_new_from_text_(
    dns_config *cfg, const char *text, size_t text_len, return_status *st)
{
	parser p;
	return parser_init(&p, text, text_len, st)
	     ? NULL : p_dfi2def(cfg, &p, st);
}

dnsextlang_def *dnsextlang_def_new_from_fn_(
    dns_config *cfg, const char *fn, return_status *st)
{
	parser p;
	return parser_init_fn(&p, fn, st) ? NULL : p_dfi2def(cfg, &p, st);
}

static dnsextlang_def p_dns_default_rrtypes = { 0 };
dnsextlang_def *dns_default_rrtypes = &p_dns_default_rrtypes;
