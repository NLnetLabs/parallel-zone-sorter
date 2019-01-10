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

#ifndef  LDNS2_INT_H_
# define LDNS2_INT_H_
# include "ldns2.h"

static inline void *ldns2_set_error(ldns2_error *err,
    ldns2_error_code code, const char *msg, const char *loc)
{
	if (err) {
		err->code = code;
		err->msg = msg;
		err->loc = loc;
	}
	return NULL;
}

static inline void *ldns2_set_syntax_error(ldns2_error *err, const char *msg,
    const char *loc, const char *fn, size_t line_nr, size_t col_nr)
{
	if (err) {
		err->code    = LDNS2_ERROR_SYNTAX;
		err->msg     = msg;
		err->loc     = loc;
		err->fn      = fn;
		err->line_nr = line_nr;
		err->col_nr  = col_nr;
	}
	return NULL;
}

# define LDNS2_CONCAT_MACRO2(x) #x
# define LDNS2_CONCAT_MACRO(x) LDNS2_CONCAT_MACRO2(x)
# if 0
#  define LDNS2_ERROR(obj, code, msg) \
	(!(obj) ? NULL \
	: ldns2_set_error(&(obj)->err, (code), (msg), \
	     __FILE__ " : " LDNS2_CONCAT_MACRO(__LINE__)))
# else
#  define LDNS2_ERROR(err, code, msg) \
	ldns2_set_error((err), (code), (msg), \
	     __FILE__ " : " LDNS2_CONCAT_MACRO(__LINE__))
# endif
# define LDNS2_MEM_ERROR(ctxt, msg) LDNS2_ERROR((ctxt), LDNS2_ERROR_MEM, (msg))
# define LDNS2_IO_ERROR(ctxt, msg) LDNS2_ERROR((ctxt), LDNS2_ERROR_IO, (msg))
# if 0
#  define LDNS2_SYNTAX_ERROR(obj, msg, fn, line_nr, col_nr) \
	(!(obj) ? NULL \
	: ldns2_set_syntax_error(&(obj)->err, (msg), \
	     __FILE__ " : " LDNS2_CONCAT_MACRO(__LINE__), \
	     (fn), (line_nr), (col_nr)))
# else
#  define LDNS2_SYNTAX_ERROR(err, msg, fn, line_nr, col_nr) \
	ldns2_set_syntax_error((err), (msg), \
	     __FILE__ " : " LDNS2_CONCAT_MACRO(__LINE__), \
	     (fn), (line_nr), (col_nr))
# endif
# define LDNS2_USAGE_ERROR(ctxt, msg) \
    LDNS2_ERROR((ctxt), LDNS2_ERROR_USAGE, (msg))
# define LDNS2_DATA_ERROR(ctxt, msg) \
    LDNS2_ERROR((ctxt), LDNS2_ERROR_DATA, (msg))
# define LDNS2_INTERNAL_ERROR(ctxt, msg) \
    LDNS2_ERROR((ctxt), LDNS2_ERROR_INTERNAL, (msg))
# define LDNS2_OVERFLOW_ERROR(ctxt, msg) \
    LDNS2_ERROR((ctxt), LDNS2_ERROR_OVERFLOW, (msg))

#endif /* #ifndef LDNS2_INT_H_ */
