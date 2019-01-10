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

#ifndef  LDNS2_H_ 
# define LDNS2_H_
# include <stddef.h>
# include <stdint.h>
# include <stdarg.h>

typedef struct ldns2_parse_piece {
	const char *start;
	const char *end;
	size_t      line_nr;
	size_t      col_nr;
	const char *fn;
} ldns2_parse_piece;


typedef enum ldns2_error_code {
	LDNS2_STATUS_OK      = 0,
	LDNS2_ERROR_MEM      = 1,
	LDNS2_ERROR_IO       = 2, /* Check errno for details                 */
	LDNS2_ERROR_SYNTAX   = 3, /* Syntax error while parsing strings      */
	LDNS2_ERROR_USAGE    = 4, /* Wrong usage by library user. Check docs */
	LDNS2_ERROR_DATA     = 5, /* Error caused by incoherent data structs */
	LDNS2_ERROR_INTERNAL = 6, /* Internal deficiency! Submit bug report  */
	LDNS2_ERROR_OVERFLOW = 7, /* Something didn't fit                    */
} ldns2_error_code;

typedef struct ldns2_error {
	ldns2_error_code code;
	const char      *msg;     /* Details of error */
	const char      *loc;     /* <func> : <file> : <line> */
	const char      *fn;      /* With LDNS2_ERROR_SYNTAX */
	size_t           line_nr; /* With LDNS2_ERROR_SYNTAX */
	size_t           col_nr;  /* With LDNS2_ERROR_SYNTAX */
} ldns2_error;

static inline void ldns2_error_reset(ldns2_error *err)
{
	if (err) {
		err->code = LDNS2_STATUS_OK;
		err->msg = NULL;
		err->loc = NULL;
		err->fn = NULL;
		err->line_nr = 0;
		err->col_nr = 0;
	}
}

# define LDNS2_ERROR_RESET { LDNS2_STATUS_OK, NULL, NULL, NULL, 0, 0 }

typedef enum ldns2_log_system {
	LDNS2_SYS_PARSER_PRESENTATION = 1 << 1,
	LDNS2_SYS_PARSER_WIRE         = 1 << 2,
	LDNS2_SYS_PARSER_DNSEXTLANG   = 1 << 3,
} ldns2_log_system;

typedef enum ldns2_log_level {
	LDNS2_LOG_EMERG   = 0,
	LDNS2_LOG_ALERT   = 1,
	LDNS2_LOG_CRIT    = 2,
	LDNS2_LOG_ERR     = 3,

	LDNS2_LOG_WARNING = 4,
	LDNS2_LOG_NOTICE  = 5,
	LDNS2_LOG_INFO    = 6,
	LDNS2_LOG_DEBUG   = 7,
} ldns2_log_level;

typedef void (*ldns2_log_func)(void *userarg,ldns2_log_system systems,
    ldns2_log_level level, const char *format, va_list ap);

typedef struct ldns2_log_conf {
	ldns2_log_system  systems; /* Log when system (bit) set in systems */
	ldns2_log_level   level;   /* Log when level <= log_conf level   */
	void             *userarg;
	ldns2_log_func    func;
} ldns2_log_conf;

# define LDNS2_LOG_CONF_DEFAULTS { 0, LDNS2_LOG_ERR, NULL, NULL }

typedef void * (*ldns2_malloc_func)(void *userarg, size_t size);
typedef void   (*ldns2_free_func)(void *userarg, void *ptr);
typedef void * (*ldns2_calloc_func)(void *userarg, size_t nmemb, size_t size);
typedef void * (*ldns2_realloc_func)(void *userarg, void *ptr, size_t size);
typedef void * (*ldns2_reallocarray_func)(
    void *userarg, void *ptr, size_t nmemb, size_t size);

typedef struct ldns2_mem_conf {
	void                   *userarg;
	ldns2_malloc_func       malloc;
	ldns2_free_func         free;
	ldns2_calloc_func       calloc;
	ldns2_realloc_func      realloc;
	ldns2_reallocarray_func reallocarray;
} ldns2_mem_conf;

# define LDNS2_MEM_CONF_DEFAULTS { NULL, NULL, NULL, NULL, NULL, NULL }

# define LDNS2_DEFAULT_TTL 3600

struct dnsextlang_definitions;

typedef struct ldns2_config{
	ldns2_mem_conf                 mem;
	ldns2_log_conf                 log;
	uint32_t                       ttl;
	struct dnsextlang_definitions *rrtypes;
} ldns2_config;

# define LDNS2_CONFIG_DEFAULTS { LDNS2_MEM_CONF_DEFAULTS, \
    LDNS2_LOG_CONF_DEFAULTS, LDNS2_DEFAULT_TTL, NULL }

#endif /* #ifndef LDNS2_H_ */
