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

#ifndef DNSEXTLANG_H_
#define DNSEXTLANG_H_
#include "dns_config.h"
#include "ldns2.h"
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

typedef enum dnsextlang_qual {
	del_qual_C         = 1 <<  0, /* With N: Compressed dname
	                               *         ( NS, MD, MF, CNAME, SOA,
	                               *           MB, MG, MR, PTR, MINFO & MX )
	                               * With X: Hex data with 1 byte length
	                               *         ( NSEC3 & NSEC3PARAM )
	                               */
	del_qual_A         = 1 <<  1, /* With N: Mailbox dname 
	                               *         ( SOA, MG, MR, MINFO & RP )
	                               */
	del_qual_L         = 1 <<  2, /* With N: Lowercased dname
	                               * With R: Type bitmap
	                               */
	del_qual_O         = 1 <<  3, /* Optional rdata field  (must be last) */
	del_qual_M         = 1 <<  4, /* Multiple rdata fields (must be last) */
	del_qual_X         = 1 <<  5, /* Remaining data field  (must be last)
	                               * Only applies to variable length types:
	                               * S, B32, B64 (default) & X (default)
	                               */
	del_qual_P         = 1 <<  6, /* Defined but not described in draft   */
	del_qual_WKS       = 1 <<  7,
	del_qual_NSAP      = 1 <<  8,
	del_qual_NXT       = 1 <<  9, /* Should this not be R[L] ?            */
	del_qual_A6P       = 1 << 10,
	del_qual_A6S       = 1 << 11,
	del_qual_APL       = 1 << 12,
	del_qual_IPSECKEY  = 1 << 13,
	del_qual_HIPHIT    = 1 << 14,
	del_qual_HIPPK     = 1 << 15
} dnsextlang_qual;

typedef enum dnsextlang_ftype {
	del_ftype_I1 = 0, del_ftype_I2 = 1, del_ftype_I4    =  2,
	del_ftype_A  = 3, del_ftype_AA = 4, del_ftype_AAAA  =  5,
	                  del_ftype_X6 = 6, del_ftype_EUI48 =  6,
	                  del_ftype_X8 = 7, del_ftype_EUI64 =  7,
	del_ftype_T  = 8, del_ftype_T6 = 9, del_ftype_R     = 10,

	del_ftype_N , del_ftype_S , del_ftype_B32, del_ftype_B64,
	del_ftype_X , del_ftype_Z
} dnsextlang_ftype;
	
static inline uint8_t dnsextlang_wf_field_len(
    dnsextlang_ftype ftype, dnsextlang_qual quals) {
	if (ftype < del_ftype_R)
		return "\x01\x02\x04\x04\x08\x10\x06\x08\x04\x06"[ftype];
	switch (ftype) {
	case del_ftype_S  :
	case del_ftype_B32: return quals & del_qual_X ?
                            0x80 : quals & del_qual_L ? 0x82 : 0x81;
	case del_ftype_X  :
	case del_ftype_B64: return quals & del_qual_C ?
	                    0x81 : quals & del_qual_L ? 0x82 : 0x80;
	case del_ftype_R  : return quals & del_qual_L ? 0xFF : 0x02;
	case del_ftype_N  : return 0x40;
	default           : return 0xFF;
	}
}

typedef struct dnsextlang_symbol {
	const char        *name;
	uint32_t           number;
} dnsextlang_symbol;

typedef struct dnsextlang_field {
	dnsextlang_ftype   ftype;
	const char        *name;
	dnsextlang_qual    quals;
	size_t           n_symbols;
	dnsextlang_symbol *symbols;
	const char        *tag;
	const char        *description;
} dnsextlang_field;

typedef struct dnsextlang_stanza {
	const char        *name;
	uint16_t           number;
	uint8_t            options[26];
	const char        *description;
	size_t           n_fields;
	dnsextlang_field   fields[];
} dnsextlang_stanza;

typedef struct dnsextlang_rrradix dnsextlang_rrradix;
struct dnsextlang_rrradix {
	unsigned int        has_rr_type: 1;
	uint16_t            rr_type;
	dnsextlang_rrradix *next_char[48];
};
typedef struct dnsextlang_definitions dnsextlang_definitions;
struct dnsextlang_definitions {
	dns_config           *cfg;
	dnsextlang_stanza     **stanzas_hi[256];
	dnsextlang_definitions *fallback;
	dnsextlang_rrradix     *rrradix;
};

extern dnsextlang_definitions *dnsextlang_default_definitions;

#define DNSEXTLANG_DEFAULT_SETTINGS { dnsextlang_default_definitions }

static inline dnsextlang_stanza *dnsextlang_type2stanza2(
    dnsextlang_definitions *def, uint16_t rr_type)
{
	dnsextlang_stanza **s = !def ? NULL : def->stanzas_hi[rr_type >> 8];
	return !s ? NULL : s[rr_type & 0x00FF];
}

static inline dnsextlang_stanza *dnsextlang_type2stanza(uint16_t rr_type)
{ return dnsextlang_type2stanza2(dnsextlang_default_definitions, rr_type); }

static inline int dnsextlang_str2type3(
    dnsextlang_definitions *def, const char *rr_type, uint8_t str_len)
{
	size_t l;

	if (!def || !rr_type)
		return -2;
	if (!str_len) {
		l = strlen(rr_type);
		if (l > 255)
			return -3;
		str_len = l;
	}
	do {
		dnsextlang_rrradix *rrr = def->rrradix;
		const char *c = rr_type;

		for ( l = str_len
		    ; rrr && l
		    ; rrr = rrr->next_char[(toupper(*c++)-'-') & 0x2F], l--)
			; /* pass */

		if (rrr && !l && rrr->has_rr_type)
			return rrr->rr_type;

		def = def->fallback;
	} while (def);

	if (str_len > 4
	&& (rr_type[0] == 'T' || rr_type[0] == 't')
	&& (rr_type[1] == 'Y' || rr_type[1] == 'y')
	&& (rr_type[2] == 'P' || rr_type[2] == 'p')
	&& (rr_type[3] == 'E' || rr_type[3] == 'e')) {

		char numbuf[6], *endptr;
		unsigned long int n;

		if (str_len - 4 > sizeof(numbuf) - 1)
			return -4;

		(void) memcpy(numbuf, rr_type + 4, str_len - 4);
		numbuf[str_len - 4] = 0;
		n = strtoul(numbuf, &endptr, 10);

		if (*endptr)
			return -5;
		if (n > 65535)
			return -6;
		return n;
	}
	return -1;
}

static inline int dnsextlang_str2type2(const char *rr_type, uint8_t str_len)
{ return dnsextlang_str2type3(
    dnsextlang_default_definitions, rr_type, str_len); }

static inline int dnsextlang_str2type(const char *rr_type)
{ return dnsextlang_str2type2(rr_type, 0); }


static inline dnsextlang_stanza *dnsextlang_str2stanza3(
    dnsextlang_definitions *def, const char *rr_type, uint8_t str_len)
{ 
	int rr_type_int = dnsextlang_str2type3(def, rr_type, str_len);

	if (rr_type_int < 0)
		return NULL;
	return dnsextlang_type2stanza2(def, rr_type_int);
}

static inline dnsextlang_stanza *dnsextlang_str2stanza2(
    const char *rr_type, uint8_t str_len)
{ return dnsextlang_str2stanza3( dnsextlang_default_definitions
                               , rr_type, str_len); }

static inline dnsextlang_stanza *dnsextlang_str2stanza(const char *rr_type)
{ return dnsextlang_str2stanza2(rr_type, 0); }

dnsextlang_definitions *dnsextlang_definitions_new_from_text2(
    dns_config *cfg, const char *text, size_t text_sz);

dnsextlang_definitions *dnsextlang_definitions_new_from_fd2(
    dns_config *cfg, int fd);

dnsextlang_definitions *dnsextlang_definitions_new_from_fn2(
    dns_config *cfg, const char *fn);

inline static dnsextlang_definitions *dnsextlang_definitions_new_from_text(
    const char *text, size_t text_sz)
{ return dnsextlang_definitions_new_from_text2(NULL, text, text_sz); }

inline static dnsextlang_definitions *dnsextlang_definitions_new_from_fd(int fd)
{ return dnsextlang_definitions_new_from_fd2(NULL, fd); }

inline static dnsextlang_definitions *dnsextlang_definitions_new_from_fn(
    const char *fn)
{ return dnsextlang_definitions_new_from_fn2(NULL, fn); }

#endif /* #ifndef DNSEXTLANG_H_ */
