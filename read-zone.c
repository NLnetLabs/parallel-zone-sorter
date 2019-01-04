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
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
	zonefile_iter zi_spc, *zi = NULL;
	char origin_spc[1024];
	/* char owner_spc[1024]; */
	size_t rr_count;

	if (argc < 2 || argc > 3) {
		printf("usage: %s <zonefile> [ <origin> ]\n", argv[0]);
		return EXIT_FAILURE;
	}
	if (!(zi = zonefile_iter_init_fn( &zi_spc, argv[1] ))) {
		perror("Could not open zonefile");
		return EXIT_FAILURE;
	}
	zonefile_iter_set_origin_spc(zi, origin_spc, sizeof(origin_spc));
	/* zonefile_iter_set_owner_spc(zi, owner_spc, sizeof(owner_spc)); */
	if (argc == 3)
		zonefile_iter_set_origin(zi, argv[2], 0);
	rr_count = 0;
	while (zi) {
		rr_count += 1;
		zi = zonefile_iter_next(zi);
	}
	printf("Counted %zu RRs in zone %s\n", rr_count, argv[1]);
	return EXIT_SUCCESS;
}

