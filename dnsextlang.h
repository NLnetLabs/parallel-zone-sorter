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
#include "return_status.h"
#include "dns_config.h"
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

#ifdef  DNS_DEFAULT_RRTYPES
#undef  DNS_DEFAULT_RRTYPES
#endif
#define DNS_DEFAULT_RRTYPES dns_default_rrtypes

#ifdef  DNS_CONFIG_DEFAULTS
#undef  DNS_CONFIG_DEFAULTS
#define DNS_CONFIG_DEFAULTS { DNS_DEFAULT_TTL   , DNS_DEFAULT_CLASS   \
                            , DNS_DEFAULT_ORIGIN, DNS_DEFAULT_RRTYPES }
#endif

struct dnsextlang_def;
extern struct dnsextlang_def *dns_default_rrtypes;

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
	dnsextlang_rrradix *next_char[48];
	uint16_t            rrtype;
	uint8_t         has_rrtype;
};
typedef struct dnsextlang_def dnsextlang_def;
struct dnsextlang_def {
	dnsextlang_stanza  **stanzas_hi[256];
	dnsextlang_rrradix  *rrradix;
	dnsextlang_def      *fallback;
};


static inline dnsextlang_stanza *dnsextlang_type2stanza_(
    dnsextlang_def *def, uint16_t rrtype)
{
	dnsextlang_stanza **s;

	if (!def) return dnsextlang_type2stanza_(dns_default_rrtypes, rrtype);
	s = def->stanzas_hi[rrtype >> 8];
	return !s ? NULL : s[rrtype & 0x00FF];
}

static inline dnsextlang_stanza *dnsextlang_type2stanza(uint16_t rrtype)
{ return dnsextlang_type2stanza_(NULL, rrtype); }


static inline int dnsextlang_str2type_(dnsextlang_def *def,
    const char *rrtype, size_t rrtype_strlen, return_status *st)
{
	if (!def)
		return dnsextlang_str2type_( dns_default_rrtypes
		                           , rrtype, rrtype_strlen, st);
	if (!rrtype)
		return -RETURN_USAGE_ERR(st, "missing rrtype");

	if (!rrtype_strlen)
		rrtype_strlen = strlen(rrtype);
	do {
		dnsextlang_rrradix *rrr = def->rrradix;
		const char *c = rrtype;
		size_t l = rrtype_strlen;

		for ( l = rrtype_strlen
		    ; rrr && l
		    ; rrr = rrr->next_char[(toupper(*c++)-'-') & 0x2F], l--)
			; /* pass */

		if (rrr && !l && rrr->has_rrtype)
			return rrr->rrtype;

		def = def->fallback;
	} while (def);

	if (rrtype_strlen > 4
	&& (rrtype[0] == 'T' || rrtype[0] == 't')
	&& (rrtype[1] == 'Y' || rrtype[1] == 'y')
	&& (rrtype[2] == 'P' || rrtype[2] == 'p')
	&& (rrtype[3] == 'E' || rrtype[3] == 'e')) {

		char numbuf[6], *endptr;
		unsigned long int n;

		if (rrtype_strlen - 4 > sizeof(numbuf) - 1)
			return -RETURN_PARSE_ERR(st,
			    "rrtype TYPE number too large", NULL, 0, 0);

		(void) memcpy(numbuf, rrtype + 4, rrtype_strlen - 4);
		numbuf[rrtype_strlen - 4] = 0;
		n = strtoul(numbuf, &endptr, 10);

		if (*endptr)
			return -RETURN_PARSE_ERR(st,
			    "syntax error in rrtype TYPE number", NULL, 0, 0);
		if (n > 65535)
			return -RETURN_PARSE_ERR(st,
			    "rrtype TYPE number must be < 65536", NULL, 0, 0);
		return n;
	}
	return -RETURN_NOT_FOUND_ERR(st, "rrtype not found"); 
}

static inline int dnsextlang_str2type(const char *rrtype)
{ return dnsextlang_str2type_(NULL, rrtype, 0, NULL); }


static inline dnsextlang_stanza *dnsextlang_str2stanza_(dnsextlang_def *def,
    const char *rrtype, size_t rrtype_strlen, return_status *st)
{ int rrtype_int = dnsextlang_str2type_(def, rrtype, rrtype_strlen, st)
; return rrtype_int >= 0 ? dnsextlang_type2stanza_(def, rrtype_int) : NULL; }

static inline dnsextlang_stanza *dnsextlang_str2stanza(const char *rrtype)
{ return dnsextlang_str2stanza_(NULL, rrtype, 0, NULL); }

dnsextlang_def *dnsextlang_def_new_from_text_(
    dns_config *cfg, const char *text, size_t text_len, return_status *st);

inline static dnsextlang_def *dnsextlang_def_new_from_text(
    const char *text, size_t text_len)
{ return dnsextlang_def_new_from_text_(NULL, text, text_len, NULL); }


dnsextlang_def *dnsextlang_def_new_from_fn_(
    dns_config *cfg, const char *fn, return_status *st);

inline static dnsextlang_def *dnsextlang_def_new_from_fn(const char *fn)
{ return dnsextlang_def_new_from_fn_(NULL, fn, NULL); }

#endif /* #ifndef DNSEXTLANG_H_ */
