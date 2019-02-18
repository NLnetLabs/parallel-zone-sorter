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
#include "dnsextlang.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

int main(int argc, char **argv)
{
	dns_config      cfg = DNS_CONFIG_DEFAULTS;
	return_status   st  = RETURN_STATUS_CLEAR;
	zonefile_iter   zi;
	size_t rr_count = 0;

	if (argc < 2 || argc > 3) {
		fprintf(stderr, "usage: %s <zonefile> [ <origin> ]\n", argv[0]);
		return EXIT_FAILURE;
	}
	if (argc == 3)
		cfg.default_origin = argv[2];

	if (zonefile_iter_init_fn_(&cfg, &zi, argv[1], &st)) {
		fprint_return_status(stderr, &st);
		zonefile_iter_free_in_use(&zi);
		return EXIT_FAILURE;
	}
	while (!zonefile_iter_next_(&zi, &st)) {
#if 1
		const dnsextlang_stanza *s;
		if (!(s = dnsextlang_lookup_(zi.rr_type->start,
		    zi.rr_type->end - zi.rr_type->start, &st))) {
			fprint_return_status(stderr, &st);
		}
#endif
	       
#if 0
		fprintf(stderr,
		    "origin: \"%.*s\", owner: \"%.*s\", "
		    "type: \"%.*s\", # rdata fields: %d\n",
		    (int)zi->origin.len, zi->origin.r.text,
		    (int)zi->owner.len, zi->owner.r.text,
		    (int)(zi->rr_type->end - zi->rr_type->start),
		    zi->rr_type->start,
		    (int)(zi->p.cur_piece - (zi->rr_type + 1))
		    );
#endif
#if 0
		else if (s->n_fields + 1 != (zi->p.cur_piece - zi->rr_type)) {
			parse_piece *p;

			fprintf( stderr
			       , "%.*s %s (TYPE%d) has %d fields (%d pieces)\n"
			       , (int)(zi->owner.len)
			       , zi->owner.r.text
			       , s->name
			       , (int)s->number, (int)s->n_fields
			       , (int)(zi->p.cur_piece - (zi->rr_type + 1)));
			for (p = zi->rr_type + 1; p < zi->p.cur_piece; p++) {
				fprintf( stderr, "\t%d: (%s:%zu:%zu) \"%.*s\"\n"
				       , (int)(p - zi->rr_type)
				       , p->fn, p->line_nr + 1, p->col_nr + 1
				       , (int)(p->end - p->start)
				       , p->start);
			}
		}
#endif
		rr_count++;
	}
	if (st.code) {
		fprint_return_status(stderr, &st);
		zonefile_iter_free_in_use(&zi);
	}
	printf("Counted %zu RRs in zone %s\n", rr_count, argv[1]);
	return st.code ? EXIT_FAILURE : EXIT_SUCCESS;
}

