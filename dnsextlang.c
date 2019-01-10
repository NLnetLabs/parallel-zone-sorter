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
#include "ldns2-int.h"
#include "dnsextlang.h"
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

typedef struct del_file_iter {
	ldns2_config *cfg;
	ldns2_error err;

	const char *fn;
	int         fd;

	const char *text;
	const char *end;
	const char *cur;

	size_t      line_nr;

	ldns2_parse_piece   *cur_piece;
	ldns2_parse_piece   *pieces;
	size_t    n_pieces;
	unsigned    pieces_malloced: 1;
} del_file_iter;

static del_file_iter *p_dfi_cleanup(del_file_iter *i)
{
	if (i->pieces && i->pieces_malloced) {
		free(i->pieces);
		i->pieces = NULL;
		i->n_pieces = 0;
		i->cur_piece = NULL;
		i->pieces_malloced = 0;
	}
	return NULL;
}

static del_file_iter *p_dfi_at_end(del_file_iter *i)
{
	if (i->cur_piece == i->pieces && !i->cur_piece->start)
		return p_dfi_cleanup(i);

	else if (i->cur_piece->start && !i->cur_piece->end) {
		i->cur_piece->end = i->cur;
		i->cur_piece += 1;
		i->cur_piece->start = NULL;
	}
	return i;
}

static del_file_iter *p_dfi_get_fields(del_file_iter *i)
{
	while (i->cur < i->end) {
		const char *sol = i->cur;

		if (isalpha(*i->cur)) {
			/* Start of stanza */
			return p_dfi_at_end(i);
		}
		while (*i->cur != '\n' && isspace(*i->cur)) {
			if (++i->cur >= i->end)
				return p_dfi_at_end(i);
		}
		switch (*i->cur) {
		case '#' :
			if (++i->cur >= i->end)
				return p_dfi_at_end(i);
			while (*i->cur != '\n') {
				if (++i->cur >= i->end)
					return p_dfi_at_end(i);
			}
			i->cur += 1;
			i->line_nr += 1;
			break;
		case '\n':
			i->cur += 1;
			i->line_nr += 1;
			break;
		default:
			/* Start of field */
			i->cur_piece->start = i->cur;
			i->cur_piece->fn = i->fn;
			i->cur_piece->line_nr = i->line_nr;
			i->cur_piece->col_nr = i->cur - sol;
			while (*i->cur != '\n' && *i->cur != '#') {
				if (i->cur[0] == '\\' && i->cur + 1 < i->end
				&&  i->cur[1] == '\n') {
					i->line_nr += 1;
					i->cur += 1;
				}
				if (++i->cur >= i->end)
					return p_dfi_at_end(i);
			}
			i->cur_piece->end = i->cur;
			i->cur_piece += 1;
			i->cur_piece->start = NULL;
			i->cur_piece->end = NULL;
			if (*i->cur == '#') {
				i->cur += 1;
				while (*i->cur != '\n') {
					if (++i->cur >= i->end)
						return p_dfi_at_end(i);
				}
			}
			i->cur += 1;
			i->line_nr += 1;
			break;
		}
	}
	return p_dfi_at_end(i);
}

static del_file_iter *p_dfi_next(del_file_iter *i)
{
	i->cur_piece = i->pieces;
	i->cur_piece->start = NULL;
	i->cur_piece->end = NULL;
	while (i->cur < i->end) {
		const char *sol = i->cur;

		if (isalpha(*i->cur)) {
			i->cur_piece->start = i->cur;
			i->cur_piece->fn = i->fn;
			i->cur_piece->line_nr = i->line_nr;
			i->cur_piece->col_nr = 0;
			if (++i->cur >= i->end)
				return p_dfi_at_end(i);
			while (*i->cur != '\n' && *i->cur != '#') {
				if (i->cur[0] == '\\' && i->cur + 1 < i->end
				&&  i->cur[1] == '\n') {
					i->line_nr += 1;
					i->cur += 1;
				}
				if (++i->cur >= i->end)
					return p_dfi_at_end(i);
			}
			i->cur_piece->end = i->cur;
			i->cur_piece += 1;
			i->cur_piece->start = NULL;
			i->cur_piece->end = NULL;
			if (*i->cur == '#') {
				i->cur += 1;
				while (*i->cur != '\n') {
					if (++i->cur >= i->end)
						return p_dfi_at_end(i);
				}
			}
			i->cur += 1;
			i->line_nr += 1;
			return p_dfi_get_fields(i);
		}
		while (*i->cur != '\n' && isspace(*i->cur)) {
			if (++i->cur >= i->end)
				return p_dfi_at_end(i);
		}
		switch (*i->cur) {
		case '#' :
			if (++i->cur >= i->end)
				return p_dfi_at_end(i);
			while (*i->cur != '\n') {
				if (++i->cur >= i->end)
					return p_dfi_at_end(i);
			}
			i->cur += 1;
			i->line_nr += 1;
			break;
		case '\n':
			i->cur += 1;
			i->line_nr += 1;
			break;
		default:
			return LDNS2_SYNTAX_ERROR( &i->err
			                         , "Stanza's begin at "
			                           "start of line"
						 , i->fn
			                         , i->line_nr, (i->cur - sol));
		}
	}
	return p_dfi_at_end(i);
}

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

static void dnsextlang_definitions_add_stanza(
    dnsextlang_definitions *d, dnsextlang_stanza *s)
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
			assert((*rrr_p)->has_rr_type == 1);
			assert((*rrr_p)->rr_type == s->number);

			(*rrr_p)->has_rr_type = 0;
			(*rrr_p)->rr_type = 0;
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
	if ((*rrr_p)->has_rr_type && (*rrr_p)->rr_type != s->number) {
		uint8_t to_rm_hi = (*rrr_p)->rr_type >> 8;
		uint8_t to_rm_lo = (*rrr_p)->rr_type & 0x00FF;

		if (d->stanzas_hi[to_rm_hi]
		 && d->stanzas_hi[to_rm_hi][to_rm_lo]) {
			dnsextlang_stanza_free(
			    d->stanzas_hi[to_rm_hi][to_rm_lo]);
			d->stanzas_hi[to_rm_hi][to_rm_lo] = NULL;
		}
	}
	(*rrr_p)->has_rr_type = 1;
	(*rrr_p)->rr_type = s->number;
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

dnsextlang_stanza *dnsextlang_stanza_new_from_pieces(ldns2_config *cfg,
   ldns2_error *err, ldns2_parse_piece *piece, size_t n_pieces)
{
	dnsextlang_stanza *r;
	const char *s, *e;
	char numbuf[6], *endptr;
	unsigned long int n;
	dnsextlang_field *f;
       
	assert(piece);
	assert(n_pieces);
	(void)cfg;

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

dnsextlang_definitions *p_dfi2def(del_file_iter *i)
{
	dnsextlang_definitions *d = calloc(1, sizeof(dnsextlang_definitions));

	if (!d)
		return LDNS2_MEM_ERROR(&i->err, "cannot allocate space for "
		                                "dnsextlang definitions");
	d->cfg = i->cfg;

	while (i) {
		dnsextlang_stanza *s;

		if (!(s = dnsextlang_stanza_new_from_pieces(d->cfg, &i->err,
		    i->pieces, (i->cur_piece - i->pieces))))
			return NULL;

		dnsextlang_definitions_add_stanza(d, s);
		i = p_dfi_next(i);
	}
	return d;
}

static del_file_iter *p_dfi_init_text(
    del_file_iter *i, const char *text, size_t text_sz)
{
	i->line_nr = 1;
	i->text = i->cur = text;
	i->end = text + text_sz;

	i->n_pieces = 16;
	if (!(i->pieces = calloc(i->n_pieces, sizeof(ldns2_parse_piece))))
                return LDNS2_MEM_ERROR(&i->err, "allocating parser pieces "
                                       "when initializing zonefile iterator");
	i->pieces_malloced = 1;

	return p_dfi_next(i);
}

static del_file_iter *p_dfi_init_fd(del_file_iter *i, int fd)
{
	struct stat statbuf;
	char *text;

	i->fd = fd;
	if (fstat(fd, &statbuf) < 0)
		return LDNS2_IO_ERROR(&i->err,
		                      "determining size of dnsextlang file");

	if ((text = mmap( NULL, statbuf.st_size, PROT_READ
	                , MAP_PRIVATE, fd, 0)) == MAP_FAILED)
                return LDNS2_IO_ERROR(&i->err
		                     ,"allocating memory for dnsextlang file");
	else
		return p_dfi_init_text(i, text, statbuf.st_size);
}

static del_file_iter *p_dfi_init_fn(del_file_iter *i, const char *fn)
{
	int fd;

	i->fn = fn;
	if ((fd = open(fn, O_RDONLY)) < 0)
		return LDNS2_IO_ERROR(&i->err, "opening dnsextlang file");
	else
		return p_dfi_init_fd(i, fd);
}

static inline void p_dfi_init(ldns2_config *cfg, del_file_iter *i)
{
	(void) memset(i, 0, sizeof(del_file_iter));
	i->cfg = cfg;
}

dnsextlang_definitions *dnsextlang_definitions_new_from_text2(
    ldns2_config *cfg, const char *text, size_t text_sz)
{
	del_file_iter df_iter, *dfi;

	p_dfi_init(cfg, &df_iter);
	if (!(dfi = p_dfi_init_text(&df_iter, text, text_sz)))
		return NULL;

	return p_dfi2def(dfi);
}

dnsextlang_definitions *dnsextlang_definitions_new_from_fd2(
    ldns2_config *cfg, int fd)
{
	del_file_iter df_iter, *dfi;

	p_dfi_init(cfg, &df_iter);
	if (!(dfi = p_dfi_init_fd(&df_iter, fd)))
		return NULL;
	return p_dfi2def(dfi);
}

dnsextlang_definitions *dnsextlang_definitions_new_from_fn2(
    ldns2_config *cfg, const char *fn)
{
	del_file_iter df_iter, *dfi;

	p_dfi_init(cfg, &df_iter);
	if (!(dfi = p_dfi_init_fn(&df_iter, fn)))
		return NULL;
	return p_dfi2def(dfi);
}

static dnsextlang_definitions p_default_definitions = { 0 };
dnsextlang_definitions *dnsextlang_default_definitions =
    &p_default_definitions;
