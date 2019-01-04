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

#ifndef PRESENTATION_H_
# define PRESENTATION_H_
# include <stdint.h>
# include <stddef.h>

typedef struct pf_piece {
	const char *start;
	const char *end;
	size_t      line_nr;
	size_t      col_nr;
	const char *fn;
} pf_piece;

typedef struct zonefile_settings {
	uint32_t  ttl;
	char     *origin;
	char     *origin_spc;
	size_t    origin_spc_sz;
	char     *owner_spc;
	size_t    owner_spc_sz;
	pf_piece *pieces;
	size_t    n_pieces;
} zonefile_settings;

#define ZONEFILE_DEFAULT_SETTINGS {3600, "", NULL, 1024, NULL, 1024, NULL, 128}

typedef struct pf_refer pf_refer;
struct pf_refer {
	const char *text; /* Referred to text may not be unmapped */
	pf_refer   *next;
	pf_refer  **prev;
};

typedef struct pf_dname {
	pf_refer r;
	size_t   len;
	char    *spc;
	size_t   spc_sz;
} pf_dname;

typedef struct zonefile_iter {
	zonefile_settings *settings;
	const char *fn;
	int         fd;

	size_t      munmap_treshold; /* start munmapping when
	                              *     cur - to_munmap > munmap_treshold */
	size_t      munmap_preserve; /* when munmapping,
	                              *     hold on to  cur - munmap_preserve */

	char       *to_munmap; /* to_munmap - text has been munmapped */
	pf_refer   *refers;    /* Do not munmap pieces which are referenced */
	const char *cur;       /* on iter return is end of parsed RR */

	const char *text;
	const char *end;
	const char *line;

	size_t      line_nr;

	pf_piece   *current_piece;   /* on iter return is last piece */

	pf_piece   *pieces;          /* pieces = pieces_spc */
	size_t      n_pieces;        /* # available pieces */

	pf_dname    origin;
	pf_dname    owner;

	uint32_t    TTL;
	uint32_t    ttl;
	pf_piece   *rr_type;  /* assert: current_piece > rr_type >= pieces */
	uint16_t    rr_class;

	unsigned int munmap    : 1; /* 1 when text was mmapped */
	unsigned int same_owner: 1; /* owner same as with previous RR */
} zonefile_iter;

zonefile_iter *zonefile_iter_init_text_(
    zonefile_iter *i, const char *text, size_t text_sz, zonefile_settings *s);

zonefile_iter *zonefile_iter_init_fd_(
    zonefile_iter *i, int fd, zonefile_settings *settings);

zonefile_iter *zonefile_iter_init_fn_(
    zonefile_iter *i, const char *fn, zonefile_settings *settings);

static inline zonefile_iter *zonefile_iter_init_text(
    zonefile_iter *i, const char *text, size_t text_sz)
{ return zonefile_iter_init_text_(i, text, text_sz, NULL); }

static inline zonefile_iter *zonefile_iter_init_fd(zonefile_iter *i, int fd)
{ return zonefile_iter_init_fd_(i, fd, NULL); }

static inline zonefile_iter *zonefile_iter_init_fn(
    zonefile_iter *i, const char *fn)
{ return zonefile_iter_init_fn_(i, fn, NULL); }

zonefile_iter *zonefile_iter_next(zonefile_iter *i);

void zonefile_iter_up_ref(zonefile_iter *i, pf_refer *r);

void pf_refer_dereference(pf_refer *r);

#endif /* #ifndef PRESENTATION_H_ */
