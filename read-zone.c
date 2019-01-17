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
#include "ldh_radix.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

void print_status(return_status *stat)
{
	assert(stat);
	switch (stat->code) {
	case STATUS_OK:
		fprintf(stderr, "Everything OK\n");
		break;

	case STATUS_PARSE_ERR:
		fprintf( stderr
		       , "parse error: %s in \"%s\" "
		         "at line %zu col %zu\n\tin function %s at %s:%d\n"
		       , stat->msg
		       , stat->details.parse.fn
		       , stat->details.parse.line_nr + 1
		       , stat->details.parse.col_nr + 1
		       , stat->func
		       , stat->file
		       , stat->line
		       );
		break;
	default:
		fprintf( stderr
		       , "%s error: %s in function %s at %s:%d\n"
		       , status_code2str(stat->code)
		       , stat->msg
		       , stat->func
		       , stat->file
		       , stat->line
		       );
		break;
	}
	return_status_reset(stat);
}

void export_ldh_radix162c_(ldh_radix16 *r, const char *prefix, char *followed)
{
	size_t l = strlen(followed);
	size_t t, i, pl = strlen(prefix);

	if (!r)
		return;
	for (i = 0; i < 48; i++) {
		if (r->next_char[i]) {
			followed[l] = i ? '-' + i : '_';
			followed[l + 1] = 0;
			export_ldh_radix162c_( r->next_char[i]
			                     , prefix, followed);
		}
	}
	followed[l] = 0;
	printf("static ldh_radix16 %s%s = {\n\t{ ", prefix, followed);
	followed[++l] = 0;
	t = 10;
	for (i = 0; i < 48; i++) {
		size_t needed = i ? 2 : 0;

		needed += r->next_char[i] ? l + pl + 1 : 4;
		if (t + needed > 78) {
			printf("\n\t, ");
			t = 10;
		} else if (i) {
			printf(", ");
			t += 2;
		}
		if (r->next_char[i]) {
			followed[l - 1] = i ? '-' + i : '_';
			printf("&%s%s", prefix, followed);
			t += l + pl + 1;
		} else {
			printf("NULL");
			t += 4;
		}
	}
	printf(" }\n};\n");
}

void export_ldh_radix162c(ldh_radix16 *r, const char *prefix)
{
	static char followed[4096] = "";
	export_ldh_radix162c_(r, prefix, followed);
}

static inline status_code ldh_uint16_register_(
    ldh_uint16_map *m, const char *str, uint16_t value, return_status *st)
{ return ldh_uint16_register(m, str, strlen(str), value, str, st); }


typedef struct dnsextlang_qual_str {
	dnsextlang_qual  qual;
	const char      *str;
} dnsextlang_qual_str;

int main(int argc, char **argv)
{
	dns_config      cfg = DNS_CONFIG_DEFAULTS;
	return_status   st  = RETURN_STATUS_CLEAR;
	dnsextlang_def *def;
	zonefile_iter   zi_spc, *zi  = NULL;
	size_t rr_count = 0;
	ldh_uint16_map map = { NULL, NULL };
	dnsextlang_qual_str quals[] = { { del_qual_C, "C" }
	                              , { del_qual_A, "A" }
	                              , { del_qual_L, "L" }
	                              , { del_qual_O, "O" }
	                              , { del_qual_M, "M" }
	                              , { del_qual_X, "X" }
	                              , { del_qual_P, "P" }
	                              , { del_qual_WKS     , "WKS" }
	                              , { del_qual_NSAP    , "NSAP" }
	                              , { del_qual_NXT     , "NXT" }
	                              , { del_qual_A6P     , "A6P" }
	                              , { del_qual_A6S     , "A6S" }
	                              , { del_qual_APL     , "APL" }
	                              , { del_qual_IPSECKEY, "IPSECKEY" }
	                              , { del_qual_HIPHIT  , "HIPHIT" }
	                              , { del_qual_HIPPK   , "HIPPK" }
	};
	size_t i;

	for (i = 0; i < sizeof(quals) / sizeof(dnsextlang_qual_str); i++) {
		if (ldh_uint16_register_(
		    &map, quals[i].str, quals[i].qual, &st)) {
			print_status(&st);
			return EXIT_FAILURE;
		}
	}

	/*
	for (i = 0; i < sizeof(quals) / sizeof(dnsextlang_qual_str); i++) {
		const char *symb = ldh_uint16_get(&map, quals[i].qual);
		uint16_t *n;

		fprintf(stderr, "%s\n", symb);
		symb = ldh_uint16_lookup(
		    &map, quals[i].str, strlen(quals[i].str));
		fprintf(stderr, "%s\n", symb);
		if ((n = ldh_uint16_lookup_uint16(
		    &map, quals[i].str, strlen(quals[i].str)))) {
			fprintf( stderr, "%x == %x\n"
			       , (int)*n, (int)quals[i].qual);
		}
	}
	export_ldh_radix162c(map.ldhs, "qual_rad_");
	*/

	if (argc < 2 || argc > 3) {
		fprintf(stderr, "usage: %s <zonefile> [ <origin> ]\n", argv[0]);
		return EXIT_FAILURE;
	}
	cfg.rrtypes = NULL;
	if (argc == 3)
		cfg.default_origin = argv[2];

	def = dnsextlang_def_new_from_fn_(&cfg, "rrtypes.txt", &st);
	if (!def) {
		print_status(&st);
		return EXIT_FAILURE;
	}
	dnsextlang_export_def2c(def);
	return EXIT_SUCCESS;

	for ( zi = zonefile_iter_init_fn_(&cfg, &zi_spc, argv[1], &st)
	    ; zi ; zi = zonefile_iter_next_(zi, &st)) {
		dnsextlang_stanza *s;
	       
		if (!(s = dnsextlang_lookup_(def, zi->rr_type->start,
		    zi->rr_type->end - zi->rr_type->start, &st))) {
			print_status(&st);
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
	if (st.code)
		print_status(&st);
	printf("Counted %zu RRs in zone %s\n", rr_count, argv[1]);
	return EXIT_SUCCESS;
}

