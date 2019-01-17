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
#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/types.h>

static inline void p_del_stanza_free(dnsextlang_stanza *s)
{
	if (s) {
		if (s->name)
			free((char *)s->name);
		if (s->description)
			free((char *)s->description);
		free(s);
	}
}

static inline status_code p_del_def_add_stanza(
    dnsextlang_def *d, dnsextlang_stanza *s, return_status *st)
{
	dnsextlang_rrradix **rrr_p;
	const char *name;
	dnsextlang_stanza *es; /* Existing stanza with same name or number */

	if (!d)
		return RETURN_INTERNAL_ERR(st,
		    "reference to dnsextlang_def missing");
	if (!s)
		return RETURN_INTERNAL_ERR(st,
		    "reference to dnsextlang_stanza missing");
	if (!s->name)
		return RETURN_INTERNAL_ERR(st,
		    "dnsextlang_stanza had no name");

	if (!d->stanzas_hi[s->number >> 8]) {
		if (!(d->stanzas_hi[s->number >> 8]
		    = calloc(256, sizeof(dnsextlang_stanza *))))
			return RETURN_MEM_ERR(st,
			    "allocating hi byte stanza array");

	} else if ((es = d->stanzas_hi[s->number >> 8][s->number & 0x00FF])) {
		if (s == es)
			/* This stanza was already registered in d */
			return STATUS_OK;
		rrr_p = &d->rrradix;
		if (!(name = es->name))
			return RETURN_DATA_ERR(st,
			    "existing stanza had no name");
		while (*name && *rrr_p) {
			rrr_p = &(*rrr_p)->next_char
			                   [(toupper(*name) - '-') & 0x2F];
			name++;
		}
		if (!*rrr_p)
			return RETURN_DATA_ERR(st,
			    "existing stanza not found in rrradix");
		if ((*rrr_p)->has_rrtype != 1)
			return RETURN_DATA_ERR(st,
			    "existing stanza not registered in rrradix");
		if ((*rrr_p)->rrtype != s->number)
			return RETURN_DATA_ERR(st,
			    "existing stanza had number inconsistency");
		(*rrr_p)->has_rrtype = 0;
		(*rrr_p)->rrtype = 0;
		p_del_stanza_free(es);
	}
	d->stanzas_hi[s->number >> 8][s->number & 0x00FF] = s;
	
	rrr_p = &d->rrradix;
	name = s->name;
	for (;;) {
		if (!*rrr_p
		&& !(*rrr_p = calloc(1, sizeof(dnsextlang_rrradix))))
			return RETURN_MEM_ERR(st,
			    "allocating dnsextlang_rrradix");
		if (!*name)
			break;
		rrr_p = &(*rrr_p)->next_char[(toupper(*name) - '-') & 0x2F];
		name++;
	}
	if ((*rrr_p)->has_rrtype && (*rrr_p)->rrtype != s->number) {
		uint8_t to_rm_hi = (*rrr_p)->rrtype >> 8;
		uint8_t to_rm_lo = (*rrr_p)->rrtype & 0x00FF;

		if (d->stanzas_hi[to_rm_hi]
		 && (es = d->stanzas_hi[to_rm_hi][to_rm_lo])) {
			p_del_stanza_free(es);
			d->stanzas_hi[to_rm_hi][to_rm_lo] = NULL;
		}
	}
	(*rrr_p)->has_rrtype = 1;
	(*rrr_p)->rrtype = s->number;
	return STATUS_OK;
}

/* Caller should produce MEM_ERR */
static inline const char *p_del_strdup(const char *start, const char *end)
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

static inline int p_scan_ftype(const char **p, const char *e)
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
                  switch (**p) {
                  case '6': *p += 1;
			    return del_ftype_X6;
                  case '8': *p += 1;
			    return del_ftype_X8;
	          default : return del_ftype_X;
	          }
	case 'T': if (*p >= e || **p != '6')
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

static inline int p_lookup_qual(const char *s, const char *e)
{
	switch (e - s) {
	case 1: switch (*s) {
		case 'C': case 'c': return del_qual_C;
		case 'A': case 'a': return del_qual_A;
		case 'L': case 'l': return del_qual_L;
		case 'O': case 'o': return del_qual_O;
		case 'M': case 'm': return del_qual_M;
		case 'X': case 'x': return del_qual_X;
		case 'P': case 'p': return del_qual_P;
		default : return -1;
		}
	case 3: switch (*s) {
		case 'W': case 'w': return ( s[1] == 'K' || s[1] == 'k')
		                        && ( s[2] == 'S' || s[2] == 's')
		                         ? del_qual_WKS : -1;
		case 'N': case 'n': return ( s[1] == 'X' || s[1] == 'x')
		                        && ( s[2] == 'T' || s[2] == 't')
		                         ? del_qual_NXT : -1;
		case 'A':
		case 'a': switch (s[1]) {
		          case '6': return ( s[2] == 'P' || s[2] == 'p' )
		                         ? del_qual_A6P
		                         : ( s[2] == 'S' || s[2] == 's' )
		                         ? del_qual_A6S : -1;
		          case 'P':
		          case 'p': return ( s[2] == 'L' || s[2] == 'l' )
		                         ? del_qual_APL : -1;
		          default : return -1;
		          }
		default : return -1;
		}
	case 4: return strncasecmp(s, "NSAP"    , 4) ? -1 : del_qual_NSAP;
	case 8: return strncasecmp(s, "IPSECKEY", 8) ? -1 : del_qual_IPSECKEY;
	case 6: return strncasecmp(s, "HIPHIT"  , 6) ? -1 : del_qual_HIPHIT;
	case 5: return strncasecmp(s, "HIPPK"   , 5) ? -1 : del_qual_HIPPK;
	default: return -1;
	}
}

static inline status_code p_del_parse_quals(dnsextlang_field *f,
    parse_piece *p, return_status *st)
{
	const char *s;

	s = p->start;
	while (s < p->end) {
		const char *e, *eq = NULL;

		while ((s < p->end     && isspace(*s))
		   ||  (s < p->end - 1 && *s == '\\' && isspace(s[1])))
			s++;
		if (s >= p->end)
			return STATUS_OK;

		e = s;
		if (!isalpha(*e)) {
			fprintf(stderr, "character: \'%c\', %d, %d\n", *e, isspace(*e), e < p->end);
			return RETURN_PARSE_ERR(st,
			    "qualifiers must start with an alpha character",
			    p->fn, p->line_nr, p->col_nr + (e - p->start));
		}
		while (e < p->end && (isalnum(*e) || *e == '-'))
			e++;
		if (e < p->end && *e == '=') {
			char numbuf[30] = "", *endptr;
			long long int ll;
			status_code c;
			const char *symbol;

			eq = e;
			if (++e >= p->end || !isdigit(*e))
				return RETURN_PARSE_ERR(st,
				    "missing number after equal sign",
				    p->fn, p->line_nr,
				    p->col_nr + (p->start - e));
			while (e < p->end && isdigit(*e))
				e++;
			assert(e > (eq + 1));
			(void) memcpy(numbuf, eq + 1, e - (eq + 1));
			numbuf[e - (eq + 1)] = 0;
			ll = strtoll(numbuf, &endptr, 10);
			fprintf(stderr, "   symbol: %.*s=%lli\n"
			       , (int)(eq - s), s, ll );
			if (!(symbol = p_del_strdup(s, eq)))
				return RETURN_MEM_ERR(st,
				    "could not duplicate symbolic field value");

			switch (f->ftype) {
			case del_ftype_I1:
				if (ll > 255)
					return RETURN_PARSE_ERR(st,
					    "I1 field value must be < 256",
					    p->fn, p->line_nr,
					    p->col_nr + (p->start - s));
				if ((c = ldh_uint8_register(
				    &f->symbols.I1, s, eq - s, ll, symbol, st)))
					return c;
				break;

			case del_ftype_I2:
				if (ll > 65535)
					return RETURN_PARSE_ERR(st,
					    "I2 field value must be < 65536",
					    p->fn, p->line_nr,
					    p->col_nr + (p->start - s));
				if ((c = ldh_uint16_register(
				    &f->symbols.I2, s, eq - s, ll, symbol, st)))
					return c;
				break;

			case del_ftype_I4:
				if (ll > 4294967295UL)
					return RETURN_PARSE_ERR(st,
					    "I4 field value must be "
					    "< 4294967296", p->fn, p->line_nr,
					    p->col_nr + (p->start - s));
				if ((c = ldh_uint32_register(
				    &f->symbols.I4, s, eq - s, ll, symbol, st)))
					return c;
				break;
			default:
				return RETURN_PARSE_ERR(st,
				    "symbolic values allowed with "
				    "integer fields only",
				    p->fn, p->line_nr,
				    p->col_nr + (p->start - s));
			}
		} else {
			int q = p_lookup_qual(s, e);

			if (q < 0)
				return RETURN_PARSE_ERR(st,
				    "unknown qualifier",
				    p->fn, p->line_nr,
				    p->col_nr + (p->start - s));
			f->quals |= q;
		}

		/* skip white space */
		s = e;
		while ((s < p->end     && isspace(*s))
		   ||  (s < p->end - 1 && *s == '\\' && isspace(s[1])))
			s++;

		/* skip comma */
		if (s < p->end && *s == ',')
			s++;

		else if (s < p->end)
			return RETURN_PARSE_ERR(st, "comma expected",
			    p->fn, p->line_nr, p->col_nr + (s - p->start));
	}
	return STATUS_OK;
}

static inline dnsextlang_stanza *p_err(dnsextlang_stanza *r, status_code code)
{
	(void) code;
	p_del_stanza_free(r);
	return NULL;
}

dnsextlang_stanza *dnsextlang_stanza_new_from_pieces(
   parse_piece *piece, size_t n_pieces, return_status *st)
{
	dnsextlang_stanza *r = NULL;
	const char *s, *e;
	char numbuf[6], *endptr;
	unsigned long int n;
	dnsextlang_field *f;
       
	if (!piece)
		return p_err(r, RETURN_INTERNAL_ERR(st,
		    "missing reference to pieces"));

	if (!n_pieces)
		return p_err(r, RETURN_DATA_ERR(st,
		    "at least one piece needed to construct stanza"));

	if (piece->end == piece->start)
		return p_err(r, RETURN_DATA_ERR(st, "empty first piece"));

	if (piece->end < piece->start)
		return p_err(r, RETURN_INTERNAL_ERR(st,
		    "malformed first piece"));

	if (!isalpha(*piece->start))
		return p_err(r, RETURN_PARSE_ERR(st,
		    "stanza name must start with alpha character",
		    piece->fn, piece->line_nr, piece->col_nr));

	for (s = e = piece->start; e < piece->end; e++)
		if (!isalnum(*e) && *e != '-')
			break;

	if (e >= piece->end || *e != ':')
		return p_err(r, RETURN_PARSE_ERR(st, "colon expected",
		    piece->fn, piece->line_nr, piece->col_nr + (e - s)));

	if (!(r = calloc(1, sizeof(dnsextlang_stanza)
	                  + sizeof(dnsextlang_field) * (n_pieces - 1))))
		return p_err(r, RETURN_MEM_ERR(st,
		    "allocating dnsextlang_stanza"));
	r->fields = (void *)((uint8_t *)r + sizeof(dnsextlang_stanza));

	if (!(r->name = p_del_strdup(s, e)))
		return p_err(r, RETURN_MEM_ERR(st, "duplicating name"));

	for (s = ++e; e < piece->end; e++)
		if (!isdigit(*e) && *e != '-')
			break;
	if (e == s)
		return p_err(r, RETURN_PARSE_ERR(st,
		    "stanza number missing", piece->fn, piece->line_nr,
		    piece->col_nr + (s - piece->start)));

	if (e - s > sizeof(numbuf) - 1)
		return p_err(r, RETURN_PARSE_ERR(st,
		    "stanza number too large", piece->fn, piece->line_nr,
		    piece->col_nr + (s - piece->start)));

	(void) memcpy(numbuf, s, e - s);
	numbuf[e - s] = 0;
	n = strtoul(numbuf, &endptr, 10);
	if (*endptr || n > 65535)
		return p_err(r, RETURN_PARSE_ERR(st,
		    "stanza number overflow", piece->fn, piece->line_nr,
		    piece->col_nr + (s - piece->start)));
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
			return p_err(r, RETURN_PARSE_ERR(st,
			    "colon + options or white space expected",
			    piece->fn, piece->line_nr,       
	                    piece->col_nr + (e - piece->start)));
		/* trim whitespace */
		for (s = ++e; s < piece->end && isspace(*s); s++)
			; /* pass */
		for (e = piece->end - 1; e + 1 > s && isspace(*e); e--)
			; /* pass */
		if (e + 1 > s && !(r->description = p_del_strdup(s, e + 1)))
			return p_err(r, RETURN_MEM_ERR(st,
			    "duplicating description"));
	}
	r->n_fields = --n_pieces;
	piece++;
	for (f = r->fields; n_pieces > 0; n_pieces--, f++, piece++) {
		int ft;

		s = e = piece->start;
		ft = p_scan_ftype(&e, piece->end);
		if (ft < 0)
			return p_err(r, RETURN_PARSE_ERR(st,                            
	                    "unknown field type",
			    piece->fn, piece->line_nr,       
	                    piece->col_nr));
		f->ftype = ft;
		if (e >= piece->end)
			continue;
		if (*e == '[') {
			parse_piece tmp_p;

			/* Just skip for now */
			s = ++e;
			while (e < piece->end && *e != ']')
				e++;
			tmp_p.start = s; tmp_p.end = e;
			tmp_p.fn = piece->fn;
			tmp_p.line_nr = piece->line_nr;
			tmp_p.col_nr = piece->col_nr + (s - piece->start);
			if (p_del_parse_quals(f, &tmp_p, st)) {
				p_del_stanza_free(r);
				return NULL;
			}
			if (e >= piece->end || ++e >= piece->end)
				continue;
		}
		if (*e == ':') {
			s = ++e;
			while (e < piece->end && !isspace(*e))
				e++;
			if (e > s && !(f->tag = p_del_strdup(s, e)))
				return p_err(r, RETURN_MEM_ERR(st,
				    "duplicating field tag"));
			if (e >= piece->end)
				continue;
		}
		/* trim whitespace */
		for (s = ++e; s < piece->end && isspace(*s); s++)
			; /* pass */
		for (e = piece->end - 1; e + 1 > s && isspace(*e); e--)
			; /* pass */
		if (e + 1 > s && !(f->description = p_del_strdup(s, e + 1)))
			return p_err(r, RETURN_MEM_ERR(st,
			    "duplicating field description"));
	}
	return r;
}

static inline parser *p_dfi_return(parser *p, return_status *st)
{
	if (p->cur_piece == p->pieces && !p->cur_piece->start) {
		assert(p->cur == p->end);
		(void) parser_free_in_use(p, NULL);
		return NULL; /* End of text to parse */
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

		if (p_del_def_add_stanza(d, s, st))
			break;
	}
	if (i)
		(void) parser_free_in_use(i, NULL);

	if (st->code) {
		dnsextlang_def_free(d);
		return NULL;
	}
	return d;
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

static void p_rrradix_free(dnsextlang_rrradix *rrr)
{
	size_t i;

	if (!rrr) return;
	for (i = 0; i < 48; i++)
		if (rrr->next_char[i])
			p_rrradix_free(rrr->next_char[i]);
	free(rrr);
}

void dnsextlang_def_free(dnsextlang_def *d)
{
	size_t i, j;

	if (!d) return;
	for (i = 0; i < 256; i++) {
		if (d->stanzas_hi[i]) {
			for (j = 0; j < 256; j++)
				p_del_stanza_free(d->stanzas_hi[i][j]);
			free(d->stanzas_hi[i]);
		}
	}
	p_rrradix_free(d->rrradix);
	free(d);
}

static void p_export_stanza2c(size_t n, dnsextlang_stanza *s)
{
	size_t i;
	static const char *ftype_str[] = {
	    "del_ftype_I1", "del_ftype_I2", "del_ftype_I4",
	    "del_ftype_A" , "del_ftype_AA", "del_ftype_AAAA",
	                 "del_ftype_EUI48", "del_ftype_EUI64",
	    "del_ftype_T" , "del_ftype_T6", "del_ftype_R",
	    "del_ftype_N" , "del_ftype_S" , "del_ftype_B32", "del_ftype_B64",
	    "del_ftype_X" , "del_ftype_Z" };
	static const char *qual_str[] = {
	    "del_qual_C", "del_qual_A", "del_qual_L", "del_qual_O",
	    "del_qual_M", "del_qual_X", "del_qual_P",
	    "del_qual_WKS", "del_qual_NSAP", "del_qual_NXT",
	    "del_qual_A6P", "del_qual_A6S", "del_qual_APL",
	    "del_qual_IPSECKEY", "del_qual_HIPHIT", "del_qual_HIPPK" };

	if (s->n_fields) {
		printf("static dnsextlang_field t_%.4zx_fields[%zu] = {\n"
		      , n, s->n_fields);
		for (i = 0; i < s->n_fields; i++) {
			dnsextlang_field *f = &s->fields[i];
			size_t j;

			printf("\t{ .ftype = ");
			if (f->ftype >= 0 && f->ftype <= del_ftype_Z)
				printf("%s", ftype_str[f->ftype]);
			else
				printf("%d", f->ftype);
			if (f->quals) {
				dnsextlang_qual q = f->quals;
				int qs = 0;

				printf(", .quals = (");
				for ( j = 0
				    ; j < sizeof(qual_str) / sizeof(const char *)
				    ; j++ ) {
					if (q & (1 << j)) {
						if (qs) putchar('|');
						qs = 1;
						printf("%s", qual_str[j]);
					}
					q &= ~(1 << j);
				}
				if (q)
					printf("|%x", q);
				printf(")");
			}
			if (f->tag)
				printf(", .tag = \"%s\"", f->tag);
			if (f->description)
				printf("\n\t, .description = \"%s\"", f->description);

			printf(" }");
			if (i + 1 < s->n_fields)
				printf(",\n");
			else
				printf("\n");
		}
		printf("};\n");
	}
	printf("static dnsextlang_stanza t_%.4zx = "
	       "{\n\t.name = \"%s\", .number = %zu,\n\t"
	      , n, s->name, (size_t)s->number);
	if (s->description)
		printf(".description = \"%s\",\n\t", s->description);
	printf(".options = {");
	for (i = 0; i < 26; i++) {
		putchar(s->options[i] ? '1' : '0');
		if (i < 25)
			putchar(',');
	}
	printf("},\n\t");
	if (s->n_fields)
		printf(".n_fields = %zu, .fields = t_%.4zx_fields"
		      , s->n_fields, n);
	printf("\n};\n");
}

static void p_export_hi2c(size_t hi, dnsextlang_stanza **stanzas_lo)
{
	char buf[4096];
	size_t i;

	sprintf(buf, "static dnsextlang_stanza *t_hi%.2zx[256] = {\n\t", hi);
	for (i = 0; i < 256; i++) {
		if (!stanzas_lo[i])
			(void) strcat(buf, " NULL  ");
		else {
			sprintf(buf + strlen(buf), "&t_%.2zx%.2zx", hi, i);
			p_export_stanza2c(((hi << 8) | i), stanzas_lo[i]);
		}
		if (i < 255) {
			(void) strcat(buf, ",");
			(void) strcat(buf, (i + 1) % 8 == 0 ? "\n\t" : "");
		}
	}
	printf("%s\n};\n", buf);
}

void dnsextlang_export_def2c(dnsextlang_def *d)
{
	char buf[4096] = "static dnsextlang_def p_dns_default_rrtypes = {\n";
	size_t i;

	printf("#include \"dnsextlang.h\"\n");
	(void) strcat(buf, "\t{ ");
	for (i = 0; i < 256; i++) {
		if (!d->stanzas_hi[i])
			(void) strcat(buf, "NULL  ");
		else {
			sprintf(buf + strlen(buf), "t_hi%.2zx", i);
			p_export_hi2c(i, d->stanzas_hi[i]);
		}
		if (i < 255) {
			(void) strcat(buf, ",");
			(void) strcat(buf, (i + 1) % 8 == 0 ? "\n\t  " : " ");
		}
	}
	(void) strcat(buf, "},\n");

	printf("%s\tNULL, NULL\n};\n", buf);
	printf("dnsextlang_def *dns_default_rrtypes = &p_dns_default_rrtypes;");
}
