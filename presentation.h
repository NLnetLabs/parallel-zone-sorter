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
#define PRESENTATION_H_
#include "parser.h"
#include "return_status.h"
#include "dns_config.h"

typedef struct presentation_dname {
	parse_reference r;
	size_t   len;
	char    *spc;
	size_t   spc_sz;
	unsigned malloced: 1;
} presentation_dname;

typedef struct zonefile_iter {
	parser      p;
	dns_config *cfg;
	status_code code;
	const char *fn;
	int         fd;

	size_t      munmap_treshold; /* start munmapping when
	                              *     cur - to_munmap > munmap_treshold */
	size_t      munmap_preserve; /* when munmapping,
	                              *     hold on to  cur - munmap_preserve */

	char       *to_munmap; /* to_munmap - text has been munmapped */
	parse_reference *refs; /* referenced text will not be unmapped */

	const char *start_of_line; /* Start of line of start of this RR.
	                            * When this < p.pieces->start, then the
	                            * RR started with white space and should
	                            * reuse the previous owner
	                            */
	presentation_dname origin;
	presentation_dname owner;

	uint32_t     TTL;
	uint32_t     ttl;
	parse_piece *rr_type;  /* assert: current_piece > rr_type >= pieces */
	uint16_t     rr_class;

	unsigned munmap         : 1; /* 1 when text was mmapped */
	unsigned same_owner     : 1; /* owner same as with previous RR */
} zonefile_iter;

zonefile_iter *zonefile_iter_init_text_(dns_config *cfg, zonefile_iter *i,
    const char *text, size_t text_sz, const char *origin, return_status *st);

zonefile_iter *zonefile_iter_init_fd_(dns_config *cfg, zonefile_iter *i,
    int fd, const char *origin, return_status *st);

zonefile_iter *zonefile_iter_init_fn_(dns_config *cfg, zonefile_iter *i,
    const char *fn, const char *origin, return_status *st);

static inline zonefile_iter *zonefile_iter_init_text(
    zonefile_iter *i, const char *text, size_t text_sz)
{ return zonefile_iter_init_text_(NULL, i, text, text_sz, NULL, NULL); }

static inline zonefile_iter *zonefile_iter_init_fd(zonefile_iter *i, int fd)
{ return zonefile_iter_init_fd_(NULL, i, fd, NULL, NULL); }

static inline zonefile_iter *zonefile_iter_init_fn(
   zonefile_iter *i, const char *fn)
{ return zonefile_iter_init_fn_(NULL, i, fn, NULL, NULL); }

zonefile_iter *zonefile_iter_next_(zonefile_iter *i, return_status *st);

static inline zonefile_iter *zonefile_iter_next(zonefile_iter *i)
{ return zonefile_iter_next_(i, NULL); }

static inline zonefile_iter *zonefile_iter_up_ref(
    zonefile_iter *i, parse_reference *r, return_status *st)
{
	if (!i)
                return NULL_USAGE_ERR(&i->code, st,
                    "missing reference to the zonefile iterator "
                    "for which to up the reference");
	if (!r)
                return NULL_USAGE_ERR(&i->code, st, "missing reference to up");

	if (r->text < i->p.text || r->text >= i->p.end)
                return NULL_DATA_ERR(&i->code, st,
		    "cannot up an reference outside of the zonefile text");

	if ((i->code = parse_reference_add(&i->refs, r, st)))
		return NULL;
	return i;
}

#endif /* #ifndef PRESENTATION_H_ */
