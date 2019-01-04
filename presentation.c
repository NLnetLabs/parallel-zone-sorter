/* Copyright (c) 2018, NLnet Labs. All rights reserved.
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
#include "presentation.h"
#include <assert.h>
#include <ctype.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

static inline void p_refer_remove(pf_refer *r)
{
	if (!r->prev) return;
	if ( r->next) r->next->prev = r->prev;
	*r->prev = r->next; r->prev = NULL;
}

static inline zonefile_iter *p_zfi_at_end(zonefile_iter *i)
{
	if (i->cur) {
		assert(i->cur == i->end);
		i->cur = NULL;
		i->current_piece->start = NULL;
		return i;
	}
	p_refer_remove(&i->origin.r);
	p_refer_remove(&i->owner.r);
	if (i->munmap && !i->refers) {
		munmap(i->to_munmap, (i->end - i->to_munmap));
		i->to_munmap = NULL;
	}
	close(i->fd);
	i->fd = -1;
	if (i->settings->origin_spc_sz) {
		if (!i->settings->origin_spc
		||   i->settings->origin_spc_sz != i->origin.spc_sz)
			free(i->origin.spc);
	}
	if (i->settings->owner_spc_sz) {
		if (!i->settings->owner_spc
		||   i->settings->owner_spc_sz != i->owner.spc_sz)
			free(i->owner.spc);
	}
	if (!i->settings->pieces
	||   i->settings->n_pieces != i->n_pieces)
		free(i->pieces);
	return NULL;
}

static inline void p_zfi_munmap_(zonefile_iter *i, const char *pos)
{
	size_t n;

	if ((pos - i->to_munmap) < i->munmap_treshold)
		return;
	n  =(pos - i->to_munmap) / i->munmap_treshold;
	n *= i->munmap_treshold;
	n -= i->munmap_preserve;
	munmap(i->to_munmap, n);
	i->to_munmap += n;
}

static inline void p_zfi_munmap(zonefile_iter *i)
{
	if (!i->munmap) return;

	if (i->refers) {
		assert(!i->line || i->refers->text < i->line);
		p_zfi_munmap_(i, i->refers->text);

	} else if (i->line)
		p_zfi_munmap_(i, i->line);
}

static zonefile_iter *p_zfi_get_piece(zonefile_iter *i);
static zonefile_iter *p_zfi_return(zonefile_iter *i)
{
	i->cur++;
	p_zfi_munmap(i);
	if (i->current_piece == i->pieces) {
		/* Nothing, so process next line*/
		i->line = i->cur;
		return i->line ? p_zfi_get_piece(i) : p_zfi_at_end(i);
	}
	i->current_piece->start = NULL;
	return i;
}

static zonefile_iter *p_zfi_get_closing_piece(zonefile_iter *i)
{
	switch (*i->cur) {
	case ';':
		/* A comment is NO PART, but skip till end-of-line */
		while (++i->cur < i->end)
			if (*i->cur == '\n') {
				i->cur += 1;
				return p_zfi_get_closing_piece(i);
			}
		return p_zfi_at_end(i);

	case ' ': case '\t': case '\f': case '\n':
		while (++i->cur < i->end)
			switch (*i->cur) {
			case ' ': case '\t': case '\f': case '\n':
				/* Skip whitespace */
				continue;
			default:
				/* Non whitespace get this piece */
				return p_zfi_get_closing_piece(i);
			}
		return p_zfi_at_end(i);

	case ')':
		i->cur += 1;
		return p_zfi_get_piece(i);

	case '"': /* quoted piece (may contain whitespace) */
		i->current_piece->start = i->cur;
		while (i->cur < i->end)
			switch (*i->cur) {
			case '\n':
				/* Newline is end of quoted piece too */
			case '"':
				/* Closing quote found, get next piece */
				i->cur += 1;
				i->current_piece->end = i->cur;
				i->current_piece += 1;
				return p_zfi_get_closing_piece(i);

			case '\\':
				i->cur += 1;
				if (i->cur < i->end && *i->cur == '"')
					i->cur += 1;
				continue;
			default:
				/* Skip non closing quote */
				i->cur += 1;
				continue;
			}

		i->current_piece->end = i->cur;
		i->current_piece += 1;
		return p_zfi_at_end(i);

	default:
		i->current_piece->start = i->cur;
		while (i->cur < i->end)
			switch (*i->cur) {
			case ' ': case '\t': case '\f': case '\n':
				/* Whitespace piece, get (but actually skip) */
				i->current_piece->end = i->cur;
				i->current_piece += 1;
				return p_zfi_get_closing_piece(i);

			case ')':
				i->current_piece->end = i->cur;
				i->current_piece += 1;
				i->cur += 1;
				return p_zfi_get_piece(i);

			default:
				/* Skip non whitespace */
				i->cur += 1;
				continue;
			}
		i->current_piece->end = i->cur;
		i->current_piece += 1;
		return p_zfi_at_end(i);
	}
}

static zonefile_iter *p_zfi_get_piece(zonefile_iter *i)
{
	switch (*i->cur) {
	case ';':
		/* A comment is NO PART, but skip till end-of-line */
		while (++i->cur < i->end)
			if (*i->cur == '\n')
				return p_zfi_return(i);
		return p_zfi_at_end(i);

	case '\n':
		/* Remaining space is NO PART */
		return p_zfi_return(i);

	case ' ': case '\t': case '\f':
		while (++i->cur < i->end)
			switch (*i->cur) {
			case '\n':
				/* Remaining space is no piece */
				return p_zfi_return(i);

			case ' ': case '\t': case '\f':
				/* Skip whitespace */
				continue;
			default:
				/* Non whitespace get this piece */
				return p_zfi_get_piece(i);
			}
		return p_zfi_at_end(i);

	case '(':
		i->cur += 1;
		return p_zfi_get_closing_piece(i);

	case '"': /* quoted piece (may contain whitespace) */
		i->current_piece->start = i->cur;
		while (i->cur < i->end)
			switch (*i->cur) {
			case '\n':
				/* Remaining space is no piece */
				i->current_piece->end = i->cur;
				i->current_piece += 1;
				return p_zfi_return(i);

			case '"':
				/* Closing quote found, get next piece */
				i->cur += 1;
				i->current_piece->end = i->cur;
				i->current_piece += 1;
				return p_zfi_get_piece(i);

			case '\\':
				i->cur += 1;
				if (i->cur < i->end && *i->cur == '"')
					i->cur += 1;
				continue;
			default:
				/* Skip non closing quote */
				i->cur += 1;
				continue;
			}
		i->current_piece->end = i->cur;
		i->current_piece += 1;
		return p_zfi_at_end(i);

	default: /* unquoted piece (bounded by whitespace) */
		i->current_piece->start = i->cur;
		while (i->cur < i->end)
			switch (*i->cur) {
			case '\n':
				/* Remaining space is no piece */
				i->current_piece->end = i->cur;
				i->current_piece += 1;
				return p_zfi_return(i);

			case ' ': case '\t': case '\f':
				/* Whitespace piece, get (but actually skip) */
				i->current_piece->end = i->cur;
				i->current_piece += 1;
				return p_zfi_get_piece(i);

			case '\\':
				i->cur += 1;
				if (i->cur < i->end && isspace(*i->cur))
					i->cur += 1;
				continue;
			default:
				/* Skip non whitespace */
				i->cur += 1;
				continue;
			}
		i->current_piece->end = i->cur;
		i->current_piece += 1;
		return p_zfi_at_end(i);
	}
}

static inline uint32_t pf_ttl2u32(const char *pf_ttl, size_t pf_ttl_len)        
{
	char buf[11], *endptr;

	if (pf_ttl_len >= sizeof(buf))
		return 0;
	memcpy(buf, pf_ttl, pf_ttl_len);
	buf[pf_ttl_len] = '\0';
	return strtoul(buf, &endptr, 10);
}

static inline void p_refer_insert(pf_refer **refers, pf_refer *r)
{
	if (!*refers || r->text < (*refers)->text) {
		r->next = *refers;
		r->prev =  refers;
		*refers =  r;
	} else
		p_refer_insert(&(*refers)->next, r);
}

static inline void p_zfi_set_dname(
    zonefile_iter *i, pf_dname *dname, const char *text, size_t len)
{
	p_refer_remove(&dname->r);
	dname->len = len;
	if (dname->spc && len < dname->spc_sz) {
		(void) memcpy(dname->spc, text, len);
		dname->r.text = dname->spc;
		return;
	}
	dname->r.text = text;
	if (text < i->text || text >= i->end)
		return;

	p_refer_insert(&i->refers, &dname->r);
}

static zonefile_iter *p_zfi_process_rr(zonefile_iter *i)
{
	pf_piece *piece = i->pieces;
	ssize_t piece_sz;

	piece_sz = (piece->end - piece->start);
	if (piece->start > i->line) {
		i->same_owner = 1; /* pass: Owner is previous owner */

	} else if (piece_sz <= 0)
		return zonefile_iter_next(i); /* Empty line? */

	else if ((piece->start[0] == '@' && piece_sz == 1)
	       || piece->start[0] != '$') {
		/* Owner */

		p_zfi_set_dname(i, &i->owner, piece->start, piece_sz);
		piece++;
		piece_sz = (piece->end - piece->start);

	} else if (piece_sz == 7
	       && strncasecmp(piece->start, "$ORIGIN", 7) == 0) {
		/* $ORIGIN */
		piece++;
		p_zfi_set_dname(i, &i->origin,
		   piece->start, piece->end - piece->start);
		return zonefile_iter_next(i);

	} else if (piece_sz == 4 && strncasecmp(piece->start, "$TTL", 4) == 0) {
		/* $TTL */
		piece++;
		i->TTL = pf_ttl2u32(piece->start, piece->end - piece->start);
		return zonefile_iter_next(i);
	} else {
		/* Other $ directive */
		return zonefile_iter_next(i);
	}
	/* Skip class */
	if (piece->start && piece->start[0] >= '0' && piece->start[0] <= '9') {
		/* TTL */
		i->ttl = pf_ttl2u32(piece->start, piece->end - piece->start);
		piece++;
		piece_sz = (piece->end - piece->start);
	} else {
		i->ttl = i->TTL;
	}
	/* Is last piece class? */
	if (piece_sz == 2) {
		if ((piece->start[0] == 'I' || piece->start[0] == 'i')
		&&  (piece->start[1] == 'N' || piece->start[1] == 'n')) {
			i->rr_class = 1;
			piece++;

		} else if ((piece->start[0] == 'C' || piece->start[0] == 'c')
		       &&  (piece->start[1] == 'H' || piece->start[1] == 'h')) {
			i->rr_class = 3;
			piece++;

		} else if ((piece->start[0] == 'H' || piece->start[0] == 'h')
		       &&  (piece->start[1] == 'S' || piece->start[1] == 's')) {
			i->rr_class = 4;
			piece++;
		}
	} else if (piece_sz > 5 && piece_sz < 11
	       && (piece->start[0] == 'C' || piece->start[0] == 'c')
	       && (piece->start[1] == 'L' || piece->start[1] == 'l')
	       && (piece->start[2] == 'A' || piece->start[2] == 'a')
	       && (piece->start[3] == 'S' || piece->start[3] == 's')
	       && (piece->start[4] == 'S' || piece->start[4] == 's')) {
		char nptr[7], *endptr;
		unsigned long int c;
		
		memcpy(nptr, piece->start + 5, piece_sz - 5);
		nptr[piece_sz - 5] = 0;
		c = strtoul(nptr, &endptr, 10);
		if (*endptr == 0) {
			i->rr_class = c;
			piece++;
		}
	}
	i->rr_type = piece;
	return i;
}

static zonefile_iter *p_zfi_init(zonefile_iter *i, zonefile_settings *settings)
{
	static zonefile_settings default_settings = ZONEFILE_DEFAULT_SETTINGS;

	i->settings = settings ? settings : &default_settings;

	i->TTL = i->settings->ttl;

	i->origin.spc_sz = i->settings->origin_spc_sz;
	if (i->settings->origin_spc)
		i->origin.spc = i->settings->origin_spc;
	else if (i->origin.spc_sz)
		i->origin.spc = calloc(1, i->origin.spc_sz);

	if (i->settings->origin)
		p_zfi_set_dname(i, &i->origin,
		    i->settings->origin, strlen(i->settings->origin));

	i->owner.spc_sz = i->settings->owner_spc_sz;
	if (i->settings->owner_spc)
		i->owner.spc = i->settings->owner_spc;
	else if (i->owner.spc_sz)
		i->owner.spc = calloc(1, i->owner.spc_sz);

	i->n_pieces = i->settings->n_pieces;
	if (i->settings->pieces)
		i->pieces = i->settings->pieces;
	else
		i->pieces = calloc(i->n_pieces, sizeof(pf_piece));

	i->rr_class = 1;
	i->same_owner = 0;

	i->line = i->cur;
	i->current_piece = i->pieces;
	if (!i->line)
		return p_zfi_at_end(i);
	else if (!p_zfi_get_piece(i))
		return NULL;
	return p_zfi_process_rr(i);
}

static inline zonefile_iter *p_zfi_init_text(
    zonefile_iter *i, const char *text, size_t text_sz)
{
	if (!i || (text_sz && !text))
		return NULL;

	(void) memset(i, 0, sizeof(*i));
	i->fd = -1;
	i->line = i->cur = i->text = text;
	i->end = text + text_sz;
	return i;
}

zonefile_iter *zonefile_iter_init_text_(
    zonefile_iter *i, const char *text, size_t text_sz, zonefile_settings *s)
{ return p_zfi_init_text(i, text, text_sz) ? p_zfi_init(i, s) : NULL; }

static inline zonefile_iter *p_zfi_init_fd(zonefile_iter *i, int fd)
{
	struct stat statbuf;
	const char *text;

	if (fstat(fd, &statbuf) < 0)
		return NULL;

	if ((text = mmap( NULL, statbuf.st_size, PROT_READ
	                , MAP_PRIVATE, fd, 0)) == MAP_FAILED)
		return NULL;

	if (!p_zfi_init_text(i, text, statbuf.st_size))
		return NULL;

	i->munmap_treshold = sysconf(_SC_PAGESIZE) * 64;
	i->munmap_preserve = sysconf(_SC_PAGESIZE);
	i->munmap = 1;
	i->to_munmap = (char *)i->text;
	i->fd   = fd;
	return i;
}

zonefile_iter *zonefile_iter_init_fd_(
    zonefile_iter *i, int fd, zonefile_settings *settings)
{ return p_zfi_init_fd(i, fd) ? p_zfi_init(i, settings) : NULL; }

static inline zonefile_iter *p_zfi_init_fn(zonefile_iter *i, const char *fn)
{
	int fd;

	if ((fd = open(fn, O_RDONLY)) < 0)
		return NULL;

	if (!p_zfi_init_fd(i, fd)) {
		close(fd);
		return NULL;
	}
	i->fn = fn;
	return i;
}

zonefile_iter *zonefile_iter_init_fn_(
    zonefile_iter *i, const char *fn, zonefile_settings *settings)
{ return p_zfi_init_fn(i, fn) ? p_zfi_init(i, settings) : NULL; }

zonefile_iter *zonefile_iter_next(zonefile_iter *i)
{
	i->line = i->cur;
	i->current_piece = i->pieces;
	if (!i->line)
		return p_zfi_at_end(i);
	else if (!p_zfi_get_piece(i))
		return NULL;

	return p_zfi_process_rr(i);
}

void zonefile_iter_up_ref(zonefile_iter *i, pf_refer *r)
{
	assert(r && !r->prev);

	if (r->text < i->text || r->text >= i->end)
		return;
	p_refer_insert(&i->refers, r);
}

void pf_refer_dereference(pf_refer *r)
{
	assert(r && r->prev);

	p_refer_remove(r);
}
