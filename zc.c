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
#include "zonefile_processor.h"
#include "dnsextlang.h"
#include <stdio.h>

typedef struct worker_data {
	size_t n_rrs;
	size_t rr_type_counts[65536];
	size_t rr_class_counts[65536];
	uint32_table *ttls;
} worker_data;

status_code process_rrs(
    presentation_rr *rr, presentation_rr *end_of_rrs,
    size_t n_worker, void *userarg, return_status *st)
{
	worker_data *wd = (worker_data *)userarg + n_worker;
	const void **ttl_count_ptr;
	(void)st;

	wd->n_rrs += end_of_rrs - rr;
	while (rr < end_of_rrs) {
		int rr_type = dnsextlang_get_type_(rr->rr_type->start,
		    rr->rr_type->end - rr->rr_type->start, NULL);

		wd->rr_type_counts[rr_type] += 1;
		wd->rr_class_counts[rr->rr_class] += 1;
		if ((ttl_count_ptr = uint32_table_lookup_(wd->ttls, rr->ttl))) {
			*(uintptr_t *)ttl_count_ptr += 1;
		} else
			(void) uint32_table_add(
			    &wd->ttls, rr->ttl, (void *)1, NULL);
		rr++;
	}
	return STATUS_OK;
}

void combine_ttls(
    size_t depth, uint64_t number, const void *ptr, void *userarg)
{
	uint32_table **ttls = (uint32_table **)userarg;
	const void **ttl_count_ptr;

	if ((ttl_count_ptr = uint32_table_lookup_(*ttls, number))) {
		*(uintptr_t *)ttl_count_ptr += (uintptr_t)ptr;
	} else
		(void) uint32_table_add(ttls, number, ptr, NULL);
}

void print_ttl(size_t depth, uint64_t number, const void *ptr, void *userarg)
{
	(void)depth;
	(void)userarg;
	printf("%10d: %9d\n", (int)number, (int)(uintptr_t)ptr);
}

int main(int argc, const char **argv)
{
	dns_config      cfg = DNS_CONFIG_DEFAULTS;
	return_status   st  = RETURN_STATUS_CLEAR;
	worker_data    *wd;
	size_t        n_workers, i, count, j;
	static char     spaces[] = "          ";
	int             count_only_rrs = 0;
	const char     *prog_name = argv[0];

	if (argc >= 2 && strcmp(argv[1], "-r") == 0) {
		count_only_rrs = 1;
		argc--;
		argv++;
	}
	if (argc < 2 || argc > 3) {
		fprintf( stderr
		       , "usage: %s [ -r ] <zonefile> [ <origin> ]\n"
		       , prog_name);
		return EXIT_FAILURE;
	}
	if (argc == 3)
		cfg.default_origin = argv[2];

	if (count_only_rrs) {
		return_status st = RETURN_STATUS_CLEAR;
		zonefile_iter zi;
		
		count = 0;
		if (!zonefile_iter_init_fn_(&cfg, &zi, argv[1], &st)) {
			while (!zonefile_iter_next_(&zi, &st))
				count += 1;
		}
		if (st.code) {
			(void) fprint_return_status(stderr, &st);
			return EXIT_FAILURE;
		}
		printf("RRs       : %9zu\n", count);
		return EXIT_SUCCESS;
	}
	n_workers = sysconf(_SC_NPROCESSORS_ONLN);
	if (!(wd = calloc(n_workers, sizeof(*wd)))) {
		fprintf(
		    stderr, "Memory error allocating worker data\n");
		return EXIT_FAILURE;
	}
	if (zonefile_process_rrs_fn_(
	    &cfg, argv[1], n_workers, process_rrs, wd, &st)) {

		fprint_return_status(stderr, &st);
		free(wd);
		return EXIT_FAILURE;
	}
	for (count = j = 0; j < n_workers; j++)
		count += wd[j].n_rrs;
	printf("RRs       : %9zu\n", count);
	printf("\nRR types  :");
	printf("\n======================\n");
	for (i = 0; i < 65536; i++) {
		const dnsextlang_stanza *s;

		for (count = j = 0; j < n_workers; j++)
			count += wd[j].rr_type_counts[i];

		if (!count)
			continue;

		s = dnsextlang_get_stanza(i);
		if (s) 
			printf( "%s%s"
			      , ( strlen(s->name) >= sizeof(spaces) ? ""
				: spaces + strlen(s->name))
			      , s->name );
		else
			printf( "%sTYPE%zu"
			      , spaces + ( i >= 10000 ? 9
				         : i >=  1000 ? 8
				         : i >=   100 ? 7
				         : i >=    10 ? 6 : 5)
			      , i );

		printf(": %9zu\n", count);
	}
	printf("\nRR classes:");
	printf("\n======================\n");
	for (i = 0; i < 65536; i++) {
		for (count = j = 0; j < n_workers; j++)
			count += wd[j].rr_class_counts[i];
		if (!count)
			continue;
		switch (i) {
		case   1: printf("%s%s", "IN", spaces + 2);
			  break;
		case   3: printf("%s%s", "CH", spaces + 2);
			  break;
		case   4: printf("%s%s", "HS", spaces + 2);
			  break;
		case 254: printf("%s%s", "NONE", spaces + 4);
			  break;
		case 255: printf("%s%s", "ANY", spaces + 3);
			  break;
		default : printf( "%sCLASS%zu"
		                , spaces + ( i >= 10000 ? 10
		                           : i >=  1000 ?  9
		                           : i >=   100 ?  8
		                           : i >=    10 ?  7 : 6)
		                , i
				);
			  break;
		}
		printf(": %9zu\n", count);
	}
	printf("\nTTL values:");
	printf("\n======================\n");
	for (j = 1; j < n_workers; j++)
		uint32_table_walk(wd[j].ttls, combine_ttls, NULL, &wd[0].ttls);
	uint32_table_walk(wd[0].ttls, print_ttl, NULL, NULL);
	for (j = 0; j < n_workers; j++)
		uint32_table_free(wd[j].ttls);
	free(wd);
	return EXIT_SUCCESS;
}

