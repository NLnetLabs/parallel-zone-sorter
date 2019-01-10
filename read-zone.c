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
#include "dnsextlang.h"
#include "presentation.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
	ldns2_config cfg = LDNS2_CONFIG_DEFAULTS;
	dnsextlang_definitions *def;
	zonefile_iter zi_spc, *zi = NULL;
	size_t rr_count;

	cfg.rrtypes = NULL;
	def = dnsextlang_definitions_new_from_fn2(&cfg, "rrtypes.txt");

	if (argc < 2 || argc > 3) {
		printf("usage: %s <zonefile> [ <origin> ]\n", argv[0]);
		return EXIT_FAILURE;
	}
	rr_count = 0;
	for ( zi = zonefile_iter_init_fn2(&cfg, &zi_spc, argv[1]
	                                 , argc == 3 ? argv[2] : NULL)
	    ; zi ; zi = zonefile_iter_next(zi)) {
		dnsextlang_stanza *s = dnsextlang_str2stanza3(def,
		    zi->rr_type->start, zi->rr_type->end - zi->rr_type->start);

		if (!s) {
			fprintf( stderr, "Unknown RRTYPE: %.*s\n"
			       , (int)(zi->rr_type->end - zi->rr_type->start)
			       , zi->rr_type->start);

		}
#if 0
		else if (s->n_fields + 1 != (zi->current_piece - zi->rr_type)) {
			pf_piece *p;

			fprintf( stderr
			       , "%.*s %s (TYPE%d) has %d fields (%d pieces)\n"
			       , (int)(zi->owner.len)
			       , zi->owner.r.text
			       , s->name
			       , (int)s->number, (int)s->n_fields
			       , (int)(zi->current_piece - (zi->rr_type + 1)));
			for (p = zi->rr_type + 1; p < zi->current_piece; p++) {
				fprintf( stderr, "\t%d: (%3d) \"%.*s\"\n"
				       , (int)(p - zi->rr_type)
				       , (int)(p->end - p->start)
				       , (int)(p->end - p->start)
				       , p->start);
			}
		}
#endif
		rr_count++;
	}
	printf("Counted %zu RRs in zone %s\n", rr_count, argv[1]);
	return EXIT_SUCCESS;
}

