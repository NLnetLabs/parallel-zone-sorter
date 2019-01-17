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

#ifndef LDH_RADIX_H_
#define LDH_RADIX_H_
#include "return_status.h"
#include <stdint.h>
#include <stdlib.h>
#include <ctype.h>

#define UINT48_T uint64_t

typedef const void *uint8_table;
static inline const void *uint8_table_lookup(uint8_table *table, uint8_t value)
{ return !table ? NULL : table[value]; }

static inline status_code uint8_table_register(
    uint8_table **tabler, uint8_t value, const void *ptr, return_status *st)
{
	if (!tabler)
		return RETURN_USAGE_ERR(st,
		    "missing reference to uint8_table to register value");

	if (!*tabler && !(*tabler = calloc(256, sizeof(uint8_table))))
		return RETURN_MEM_ERR(st, "allocating uint8_table");

	(*tabler)[value] = ptr;
	return STATUS_OK;
}

#define DEF_UINT_TABLE(HI,LO,UINT_T,MASK) \
	typedef uint ## LO ## _table *uint ## HI ##_table; \
	\
	static inline const void *uint ## HI ## _table_lookup( \
	    uint ## HI ## _table *table, UINT_T value) \
	{ return !table ? NULL : uint ## LO ## _table_lookup(\
	    table[(value >> LO) & 0xFF], value & MASK); } \
	\
	static inline status_code uint ## HI ## _table_register( \
	    uint ## HI ## _table **table_r, UINT_T value, \
	    const void *ptr, return_status *st) \
	{ \
		if (!table_r) \
			return RETURN_USAGE_ERR(st, "missing reference to " \
			    "uint" #HI "_table to register value"); \
		if (!*table_r \
		&& !(*table_r = calloc(256, sizeof(uint ## HI ## _table)))) \
			return RETURN_MEM_ERR(st, \
			    "allocating uint_" #HI "table"); \
		return uint ## LO ## _table_register( \
		    &(*table_r)[(value >> LO) & 0xFF], value & MASK, ptr, st); \
	}


DEF_UINT_TABLE(16,  8, uint16_t, 0xFF)
DEF_UINT_TABLE(24, 16, uint32_t, 0xFFFFUL)
DEF_UINT_TABLE(32, 24, uint32_t, 0xFFFFFFUL)
DEF_UINT_TABLE(40, 32, uint64_t, 0xFFFFFFFFULL)
DEF_UINT_TABLE(48, 40, uint64_t, 0xFFFFFFFFFFULL)
DEF_UINT_TABLE(56, 48, uint64_t, 0xFFFFFFFFFFFFULL)
DEF_UINT_TABLE(64, 56, uint64_t, 0xFFFFFFFFFFFFFFULL)


typedef struct ldh_radix8 ldh_radix8;
struct ldh_radix8 {
	ldh_radix8 *next_char[48];
	uint8_t     value;
	uint8_t      has_value;
};

static inline status_code ldh_radix8_register(ldh_radix8 **rr,
    const char *str, size_t len, uint8_t value, return_status *st)
{
	if (!rr)
		return RETURN_USAGE_ERR(st,
		    "missing reference to ldh_radix8 to register value");

	for (;;) {
		if (!*rr && !(*rr = calloc(1, sizeof(ldh_radix8))))
			return RETURN_MEM_ERR(st,
			    "allocating ldh_radix8");
		if (!len)
			break;

		rr = &(*rr)->next_char[(toupper(*str) - '-') % 48];
		str++;
		len--;
	}
	(*rr)->has_value = 1;
	(*rr)->value = value;
	return STATUS_OK;
}

static inline uint8_t *ldh_radix8_lookup(
	ldh_radix8 *r, const char *str, size_t len)
{ return !r ? NULL : !len ? ( r->has_value ? &r->value : NULL )
: ldh_radix8_lookup(r->next_char[(toupper(*str)-'-')%48], str+1, len-1); }

typedef struct ldh_uint8_map {
	uint8_table *table;
	ldh_radix8  *ldhs;
} ldh_uint8_map;

static inline status_code ldh_uint8_register(
    ldh_uint8_map *m, const char *str, size_t len,
    uint8_t value, const void *ptr, return_status *st)
{
	status_code c;

	if (!m)
		return RETURN_USAGE_ERR(st,
		    "map missing to register string/value pair");
	if (!str && len)
		return RETURN_USAGE_ERR(st,
		    "string missing to register string/value pair");
	
	if ((c = ldh_radix8_register(&m->ldhs, str, len, value, st)))
		return c;

	return uint8_table_register(&m->table, value, ptr, st);
}

static inline const void *ldh_uint8_get(ldh_uint8_map *m, uint8_t value)
{ return !m ? NULL : uint8_table_lookup(m->table, value); }

static inline uint8_t *ldh_uint8_lookup_uint8(
      ldh_uint8_map *m, const char *str, size_t len)
{ return !m ? NULL : ldh_radix8_lookup(m->ldhs, str, len); }

static inline const void *ldh_uint8_lookup(
      ldh_uint8_map *m, const char *str, size_t len)
{ uint8_t *value = ldh_uint8_lookup_uint8(m, str, len);
  return !value ? NULL : ldh_uint8_get(m, *value); }



typedef struct ldh_radix16 ldh_radix16;
struct ldh_radix16 {
	ldh_radix16 *next_char[48];
	uint16_t     value;
	uint8_t      has_value;
};

static inline status_code ldh_radix16_register(ldh_radix16 **rr,
    const char *str, size_t len, uint16_t value, return_status *st)
{
	if (!rr)
		return RETURN_USAGE_ERR(st,
		    "missing reference to ldh_radix16 to register value");

	for (;;) {
		if (!*rr && !(*rr = calloc(1, sizeof(ldh_radix16))))
			return RETURN_MEM_ERR(st,
			    "allocating ldh_radix16");
		if (!len)
			break;

		rr = &(*rr)->next_char[(toupper(*str) - '-') % 48];
		str++;
		len--;
	}
	(*rr)->has_value = 1;
	(*rr)->value = value;
	return STATUS_OK;
}

static inline uint16_t *ldh_radix16_lookup(
	ldh_radix16 *r, const char *str, size_t len)
{ return !r ? NULL : !len ? ( r->has_value ? &r->value : NULL )
: ldh_radix16_lookup(r->next_char[(toupper(*str)-'-')%48], str+1, len-1); }

typedef struct ldh_uint16_map {
	uint16_table *table;
	ldh_radix16  *ldhs;
} ldh_uint16_map;

static inline status_code ldh_uint16_register(
    ldh_uint16_map *m, const char *str, size_t len,
    uint16_t value, const void *ptr, return_status *st)
{
	status_code c;

	if (!m)
		return RETURN_USAGE_ERR(st,
		    "map missing to register string/value pair");
	if (!str && len)
		return RETURN_USAGE_ERR(st,
		    "string missing to register string/value pair");
	
	if ((c = ldh_radix16_register(&m->ldhs, str, len, value, st)))
		return c;

	return uint16_table_register(&m->table, value, ptr, st);
}

static inline const void *ldh_uint16_get(ldh_uint16_map *m, uint16_t value)
{ return !m ? NULL : uint16_table_lookup(m->table, value); }

static inline uint16_t *ldh_uint16_lookup_uint16(
      ldh_uint16_map *m, const char *str, size_t len)
{ return !m ? NULL : ldh_radix16_lookup(m->ldhs, str, len); }

static inline const void *ldh_uint16_lookup(
      ldh_uint16_map *m, const char *str, size_t len)
{ uint16_t *value = ldh_uint16_lookup_uint16(m, str, len);
  return !value ? NULL : ldh_uint16_get(m, *value); }



typedef struct ldh_radix32 ldh_radix32;
struct ldh_radix32 {
	ldh_radix32 *next_char[48];
	uint32_t     value;
	uint8_t      has_value;
};

static inline status_code ldh_radix32_register(ldh_radix32 **rr,
    const char *str, size_t len, uint32_t value, return_status *st)
{
	if (!rr)
		return RETURN_USAGE_ERR(st,
		    "missing reference to ldh_radix32 to register value");

	for (;;) {
		if (!*rr && !(*rr = calloc(1, sizeof(ldh_radix32))))
			return RETURN_MEM_ERR(st,
			    "allocating ldh_radix32");
		if (!len)
			break;

		rr = &(*rr)->next_char[(toupper(*str) - '-') % 48];
		str++;
		len--;
	}
	(*rr)->has_value = 1;
	(*rr)->value = value;
	return STATUS_OK;
}

static inline uint32_t *ldh_radix32_lookup(
	ldh_radix32 *r, const char *str, size_t len)
{ return !r ? NULL : !len ? ( r->has_value ? &r->value : NULL )
: ldh_radix32_lookup(r->next_char[(toupper(*str)-'-')%48], str+1, len-1); }

typedef struct ldh_uint32_map {
	uint32_table *table;
	ldh_radix32  *ldhs;
} ldh_uint32_map;

static inline status_code ldh_uint32_register(
    ldh_uint32_map *m, const char *str, size_t len,
    uint32_t value, const void *ptr, return_status *st)
{
	status_code c;

	if (!m)
		return RETURN_USAGE_ERR(st,
		    "map missing to register string/value pair");
	if (!str && len)
		return RETURN_USAGE_ERR(st,
		    "string missing to register string/value pair");
	
	if ((c = ldh_radix32_register(&m->ldhs, str, len, value, st)))
		return c;

	return uint32_table_register(&m->table, value, ptr, st);
}

static inline const void *ldh_uint32_get(ldh_uint32_map *m, uint32_t value)
{ return !m ? NULL : uint32_table_lookup(m->table, value); }

static inline uint32_t *ldh_uint32_lookup_uint32(
      ldh_uint32_map *m, const char *str, size_t len)
{ return !m ? NULL : ldh_radix32_lookup(m->ldhs, str, len); }

static inline const void *ldh_uint32_lookup(
      ldh_uint32_map *m, const char *str, size_t len)
{ uint32_t *value = ldh_uint32_lookup_uint32(m, str, len);
  return !value ? NULL : ldh_uint32_get(m, *value); }

typedef union ldh_map {
	ldh_uint8_map  I1;
	ldh_uint16_map I2;
	ldh_uint32_map I4;
} ldh_map;

#endif /* #ifndef LDH_RADIX_H_ */
