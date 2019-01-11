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
# include "ldns2.h"

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
	unsigned malloced: 1;
} pf_dname;

typedef struct zonefile_iter {
	ldns2_config *cfg;
	ldns2_error err;
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

	ldns2_parse_piece *cur_piece; /* on iter return is last piece */
	ldns2_parse_piece *pieces;
	ldns2_parse_piece *end_of_pieces;

	pf_dname    origin;
	pf_dname    owner;

	uint32_t           TTL;
	uint32_t           ttl;
	ldns2_parse_piece *rr_type;  /* assert: current_piece > rr_type >= pieces */
	uint16_t           rr_class;

	unsigned munmap         : 1; /* 1 when text was mmapped */
	unsigned pieces_malloced: 1;
	unsigned same_owner     : 1; /* owner same as with previous RR */
} zonefile_iter;

zonefile_iter *zonefile_iter_init_text2(ldns2_config *cfg,
    zonefile_iter *i, const char *text, size_t text_sz, const char *origin);

zonefile_iter *zonefile_iter_init_fd2(ldns2_config *cfg,
    zonefile_iter *i, int fd, const char *origin);

zonefile_iter *zonefile_iter_init_fn2(ldns2_config *cfg,
    zonefile_iter *i, const char *fn, const char *origin);

static inline zonefile_iter *zonefile_iter_init_text(
    zonefile_iter *i, const char *text, size_t text_sz)
{ return zonefile_iter_init_text2(NULL, i, text, text_sz, NULL); }

static inline zonefile_iter *zonefile_iter_init_fd(zonefile_iter *i, int fd)
{ return zonefile_iter_init_fd2(NULL, i, fd, NULL); }

static inline zonefile_iter *zonefile_iter_init_fn(
   zonefile_iter *i, const char *fn)
{ return zonefile_iter_init_fn2(NULL, i, fn, NULL); }

zonefile_iter *zonefile_iter_next(zonefile_iter *i);

void zonefile_iter_up_ref(zonefile_iter *i, pf_refer *r);

void pf_refer_dereference(pf_refer *r);

#endif /* #ifndef PRESENTATION_H_ */
