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

#ifndef PARSER_H_ 
#define PARSER_H_
#include "return_status.h"
#include <stddef.h>
#include <stdlib.h>

#define DEFAULT_N_PARSER_PIECES 32

typedef struct parse_piece     parse_piece;
typedef struct parse_reference parse_reference;
typedef struct parser {
	const char *text;
	const char *end;
	const char *cur;
	const char *sol;     /* Start of line */
	size_t      line_nr;

	parse_piece *pieces;
	parse_piece *end_of_pieces;
	parse_piece *cur_piece;
	int          pieces_malloced;
} parser;

static inline status_code parser_free_in_use(parser *p, return_status *st)
{
	if (!p)
		return RETURN_USAGE_ERR(st,
		    "missing reference to the parser "
		    "for which to free up in use space");
	if (p->pieces) {
		free(p->pieces);
		p->pieces = NULL;
		p->end_of_pieces = NULL;
		p->cur_piece = NULL;
		p->pieces_malloced = 0;
	}
	return STATUS_OK;
}

#define PARSER_CLEAR { NULL, NULL, NULL, NULL, 0, NULL, NULL, NULL, 0 }

struct parse_piece {
	const char *start;
	const char *end;
	size_t      line_nr;
	size_t      col_nr;
	const char *fn;
};

struct parse_reference {
	const char       *text;
	parse_reference  *next;
	parse_reference **prev;
};

static inline status_code parser_init(parser *p,
    const char *text, size_t len, return_status *st)
{
	if (!p)
		return RETURN_USAGE_ERR(st,
		    "missing reference to the parser to initialize");
	if (len && !text)
		return RETURN_USAGE_ERR(st,
		    "missing text to initialize parser");
	p->text = text;
	p->end = text + len;
	p->cur = text;
	p->sol = text;
	p->line_nr = 0;
	p->pieces = NULL;
	p->end_of_pieces = NULL;
	p->cur_piece = NULL;
	p->pieces_malloced = 0;
	return STATUS_OK;
}

/* To do before parsing each set of pieces */
static inline status_code reset_cur_piece(parser *p, return_status *st)
{
	if (!p)
		return RETURN_USAGE_ERR(st,
		    "missing reference to the parser "
		    "for which to reset the current piece");
	if (!p->pieces) {
		if (!(p->pieces = calloc(
		    DEFAULT_N_PARSER_PIECES, sizeof(parse_piece))))
			return RETURN_MEM_ERR(st, "allocating parser pieces");
		p->end_of_pieces = p->pieces + DEFAULT_N_PARSER_PIECES;
		p->pieces_malloced = 1;
	}
	p->cur_piece = p->pieces;
	p->cur_piece->start = NULL;
	return STATUS_OK;
}

static inline status_code equip_cur_piece(
    parser *p, const char *fn, return_status *st)
{
	if (!p)
		return RETURN_USAGE_ERR(st,
		    "missing reference to the parser "
		    "for which to equip the current piece");
	if (!p->cur_piece)
		return RETURN_DATA_ERR(st,
		    "uninitialized current piece to equip");
	if (!p->cur)
		return RETURN_DATA_ERR(st,
		    "missing data at cursor "
		    "when equipping the current piece");
	p->cur_piece->start = p->cur;
	p->cur_piece->line_nr = p->line_nr;
	p->cur_piece->col_nr = p->cur - p->sol;
	p->cur_piece->fn = fn;
	return STATUS_OK;
}

static inline status_code increment_cur_piece(parser *p, return_status *st)
{
	if (!p)
		return RETURN_USAGE_ERR(st,
		    "missing reference to the parser "
		    "for which to increment the current piece");
	if (!p->cur_piece)
		return RETURN_DATA_ERR(st,
		    "uninitialized current piece to increment");
	if (!p->cur)
		return RETURN_DATA_ERR(st,
		    "missing data at cursor "
		    "when incrementing the current piece");
	p->cur_piece->end = p->cur;
	p->cur_piece += 1;
	if (!p->end_of_pieces)
		return RETURN_DATA_ERR(st,
		    "uninitialized end_of_pieces "
		    "when incrementing current piece");
	if (p->cur_piece >= p->end_of_pieces) {
		size_t cur_piece_off, n_pieces;
		parse_piece *pieces;

		if (!p->pieces)
			return RETURN_DATA_ERR(st,
			    "cannot grow uninitialized parser pieces");
		if (p->cur_piece > p->end_of_pieces)
			return RETURN_DATA_ERR(st,
			    "current parser piece beyond end of pieces");
		cur_piece_off = p->cur_piece - p->pieces;
		n_pieces = (p->end_of_pieces - p->pieces) * 2;
		pieces = realloc(p->pieces, sizeof(parse_piece) * n_pieces);
		if (!pieces)
			return RETURN_MEM_ERR(st,
			    "could not grow parser pieces");
		p->pieces = pieces;
		p->end_of_pieces = p->pieces + n_pieces;
		p->cur_piece = p->pieces + cur_piece_off;
	}
	return STATUS_OK;
}

static inline status_code parse_dereference(
    parse_reference *r, return_status *st)
{
	if (!r)
		return RETURN_USAGE_ERR(st,
		    "missing reference to the dereference parse_reference");
	if (!r->prev)
		return RETURN_DATA_ERR(st,
		    "dereferencing already dereferenced reference");
	if (r->next)
		r->next->prev = r->prev;
	*r->prev = r->next;
	r->prev = NULL;
	return STATUS_OK;
}

static inline status_code parse_reference_add(
    parse_reference **refs, parse_reference *r, return_status *st)
{
	if (!refs)
		return RETURN_USAGE_ERR(st,
		    "missing references list "
		    "for which to up the reference");
	if (!r)
		return RETURN_USAGE_ERR(st, "missing reference to up");

	if (r->prev)
		return RETURN_DATA_ERR(st,
		    "cannot add an already added reference");

	for (;;) {
		if (!*refs || r->text < (*refs)->text) {
			r->next = *refs;
			r->prev =  refs;
			*refs =  r;
			return STATUS_OK;
		}
		refs = &(*refs)->next;
	}
}

#endif /* #ifndef PARSER_H_ */
