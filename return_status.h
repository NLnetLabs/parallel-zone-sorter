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

#ifndef RETURN_STATUS_H_ 
#define RETURN_STATUS_H_
#include <stddef.h>

typedef enum status_code {
	STATUS_OK           = 0,
	STATUS_IO_ERR       = 1, /* Check errno for details                 */
	STATUS_MEM_ERR      = 2, /* Failure to allocate memory              */
	STATUS_PARSE_ERR    = 3, /* Syntax error while parsing strings      */
	STATUS_USAGE_ERR    = 4, /* Wrong usage by library user. Check docs */
	STATUS_DATA_ERR     = 5, /* Error caused by incoherent data structs */
	STATUS_INTERNAL_ERR = 6, /* Internal deficiency! Submit bug report  */
	STATUS_OVERFLOW_ERR = 7, /* Something didn't fit                    */
} status_code;

static inline const char *status_code2str(status_code code)
{
	const char *error_strings[] = {
		"OK", "I/O", "memory", "parse", "library usage",
		"data integrity", "internal", "overflow"
	};
	if (code >= STATUS_OK && code <= STATUS_OVERFLOW_ERR)
		return error_strings[code];
	else	return "Unknown error";
}

typedef struct parse_error_details {
	const char *fn;
	size_t      line_nr;
	size_t      col_nr;
} parse_error_details;

typedef struct return_status {
	status_code code;
	const char *msg;
	const char *func;
	const char *file;
	int         line;
	union {
		parse_error_details parse;
	} details;
} return_status;

#define RETURN_STATUS_CLEAR { STATUS_OK, NULL, NULL, NULL, -1 }

static inline void return_status_reset(return_status *status)
{
	if (status) {
		status->code = STATUS_OK;
		status->msg = NULL;
		status->func = NULL;
		status->file = NULL;
		status->line = -1;
	}
}

#define RETURN_ERR(NAME, STAT, MSG) ( \
      (intptr_t)(STAT ) != (uintptr_t)NULL \
    ? ( ((STAT)->func = __func__ ) \
      , ((STAT)->file = __FILE__ ) \
      , ((STAT)->line = __LINE__ ) \
      , ((STAT)->msg  = (MSG) ) \
      , ((STAT)->code = STATUS_ ## NAME ## _ERR) ) \
    : STATUS_ ## NAME ## _ERR \
    )
#define NULL_ERR(NAME, RCODE, ...) ( \
      (uintptr_t)(RCODE) != (uintptr_t)NULL \
    ? ((*(RCODE) = RETURN_ ## NAME ## _ERR(__VA_ARGS__)), NULL) \
    : (            RETURN_ ## NAME ## _ERR(__VA_ARGS__) , NULL) \
    )

#define RETURN_PARSE_ERR(STAT, MSG, FN, LINE_NR, COL_NR) ( \
      (intptr_t)(STAT ) != (uintptr_t)NULL \
    ? ( ((STAT)->details.parse.fn      = (FN)) \
      , ((STAT)->details.parse.line_nr = (LINE_NR)) \
      , ((STAT)->details.parse.col_nr  = (COL_NR)) \
      , RETURN_ERR(PARSE, (STAT), (MSG))) \
    : STATUS_PARSE_ERR \
    )
#define   NULL_PARSE_ERR(...)      NULL_ERR(PARSE   , __VA_ARGS__)

#define RETURN_IO_ERR(...)       RETURN_ERR(IO      , __VA_ARGS__)
#define   NULL_IO_ERR(...)         NULL_ERR(IO      , __VA_ARGS__)
#define RETURN_MEM_ERR(...)      RETURN_ERR(MEM     , __VA_ARGS__)
#define   NULL_MEM_ERR(...)        NULL_ERR(MEM     , __VA_ARGS__)
#define RETURN_USAGE_ERR(...)    RETURN_ERR(USAGE   , __VA_ARGS__)
#define   NULL_USAGE_ERR(...)      NULL_ERR(USAGE   , __VA_ARGS__)
#define RETURN_DATA_ERR(...)     RETURN_ERR(DATA    , __VA_ARGS__)
#define   NULL_DATA_ERR(...)       NULL_ERR(DATA    , __VA_ARGS__)
#define RETURN_INTERNAL_ERR(...) RETURN_ERR(INTERNAL, __VA_ARGS__)
#define   NULL_INTERNAL_ERR(...)   NULL_ERR(INTERNAL, __VA_ARGS__)
#define RETURN_OVERFLOW_ERR(...) RETURN_ERR(OVERFLOW, __VA_ARGS__)
#define   NULL_OVERFLOW_ERR(...)   NULL_ERR(OVERFLOW, __VA_ARGS__)

#endif /* #ifndef RETURN_STATUS_H_ */
