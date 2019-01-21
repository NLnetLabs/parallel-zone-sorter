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
#define  NO_DNS_DEFAULT_RRTYPES
#include "dns_config.h"
#include "dnsextlang.h"
#include <assert.h>
#include <inttypes.h>
#include <stdio.h>

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

static status_code p_print_ldh_radix(
    char *str, ldh_radix *r, void *userarg, return_status *st)
{
	size_t i, l = strlen(str);
	char *s, *d;
	size_t c;
	char *prefix = (char *)userarg;
	size_t pl = strlen(prefix);

	(void)userarg;
	(void)st;

	for (s = str; *s; s++)
		if (*s == '-')
			*s = '_';
	printf( "static ldh_radix %s%s = { \"%.*s\", %d, %d, %"PRIu32",\n\t{"
	      , prefix, *str ? str : "ldh_radix"
	      , (int)r->len, r->label, r->len
	      , r->has_value, r->value);
	c = 9;
	for (i = 0; i < 46; i++) {
		ldh_radix *e;

		if (i) {
			printf(",");
			c += 1;
		}
		if (!(e = r->edges[i])) {
			if (c + 6 > 76) {
				printf("\n\t  NULL");
				c = 8 + 6;
			} else {
				printf(" NULL");
				c += 5;
			}
			continue;
		}
		for ( d = str + l, s = (char *)e->label; *s; d++, s++)
			*d = *s == '-' ? '_' : *s;
		str[l + e->len] = 0;
		if (c + e->len + pl + 2 > 76) {
			printf("\n\t &%s%s", prefix, str);
			c = 8 + e->len + pl + 2;
		} else {
			printf("&%s%s", prefix, str);
			c += e->len + pl + 1;
		}
		str[l] = 0;
	}
	printf(" } };\n");
	return STATUS_OK;
}

typedef struct p_int_table_config {
	size_t width;
	char   prefix[1024];
	char  *final_type;
} p_int_table_config;

static const char *p_int_table_symbol(
    size_t width,  size_t depth, uint64_t n)
{
	static char symb[20];
	switch (width) {
	case 1:	switch (depth) {
		case 0: snprintf(symb, sizeof(symb), "xx");
			break;
		default: assert(depth < 1);
		}
		break;
	case 2:	switch (depth) {
		case 0: snprintf(symb, sizeof(symb), "xxxx");
			break;
		case 1: snprintf(symb, sizeof(symb), "%.2zxxx", n);
			break;
		default: assert(depth < 2);
		}
		break;
	case 4:	switch (depth) {
		case 0: snprintf(symb, sizeof(symb), "xxxxxxxx");
			break;
		case 1: snprintf(symb, sizeof(symb), "%.2zxxxxxxx", n);
			break;
		case 2: snprintf(symb, sizeof(symb), "%.4zxxxxx", n);
			break;
		case 3: snprintf(symb, sizeof(symb), "%.6zxxx", n);
			break;
		default: assert(depth < 4);
		}
		break;
	default: assert(width == 1 || width == 2 || width == 4);
	}
	return symb;
}

static void p_print_int_table(
    size_t depth, uint64_t n, const void *table_, void *userarg)
{
	const void * const *table = table_;
	p_int_table_config *cfg = (p_int_table_config *)userarg;
	static const char *stars_str = "****";
	const char *stars = stars_str + 4 - cfg->width + depth;
	size_t i, c, pl = strlen(cfg->prefix);

	printf("static %s %s%s%s[256] = {\n\t ", cfg->final_type, stars,
	    cfg->prefix, p_int_table_symbol(cfg->width, depth, n));
	c = 9;

	for (i = 0; i < 256; i++) {
		const char *s;
		size_t sl;

		if (i) {
			printf(",");
			c += 1;
		}
		if (!(s = (const char *)table[i])) {
			if (c + 6 > 76) {
				printf("\n\t  NULL");
				c = 8 + 6;
			} else {
				printf(" NULL");
				c += 5;
			}
			continue;
		}
		if (depth == cfg->width - 1) {
			sl = strlen(s);
			if (c + sl + 3 > 76) {
				printf("\n\t \"%s\"", s);
				c = 8 + sl + 3;
			} else {
				printf(" \"%s\"", s);
				c += sl + 3;
			}
			continue;
		}
		s = p_int_table_symbol(cfg->width, depth + 1, ((n << 8) | i));
		sl = strlen(s);
		if (c + pl + sl + 1 > 76) {
			printf("\n\t %s%s", cfg->prefix, s);
			c = 8 + pl + sl + 1;
		} else {
			printf(" %s%s", cfg->prefix, s);
			c += pl + sl + 1;
		}
	}
	printf("};\n");
}

static void p_export_stanza2c(size_t n, const dnsextlang_stanza *s)
{
	char buf[1024];
	size_t i, not_first;
	static const char *ftype_str[] = {
	    "del_ftype_I1", "del_ftype_I2", "del_ftype_I4",
	    "del_ftype_A" , "del_ftype_AA", "del_ftype_AAAA",
	                 "del_ftype_EUI48", "del_ftype_EUI64",
	    "del_ftype_T" , "del_ftype_T6", "del_ftype_R",
	    "del_ftype_N" , "del_ftype_S" , "del_ftype_B32", "del_ftype_B64",
	    "del_ftype_X" , "del_ftype_Z" };
	static const char *qual_str[] = {
	    "del_qual_C", "del_qual_A", "del_qual_L", "del_qual_O",
	    "del_qual_M", "del_qual_X", "del_qual_P",
	    "del_qual_WKS", "del_qual_NSAP", "del_qual_NXT",
	    "del_qual_A6P", "del_qual_A6S", "del_qual_APL",
	    "del_qual_IPSECKEY", "del_qual_HIPHIT", "del_qual_HIPPK" };

	if (s->n_fields) {
		for (i = 0; i < s->n_fields; i++) {
			dnsextlang_field *f = &s->fields[i];
			p_int_table_config cfg;

			if (!f->symbols_by_ldh)
				continue;
			(void) snprintf(cfg.prefix, sizeof(cfg.prefix),
				        "t%.4zx_%zu_", n, i);
			buf[0] = 0;
			cfg.final_type = "const char";
			switch (f->ftype) {
			case del_ftype_I1:
				cfg.width = 1;
				uint8_table_walk(f->symbols_by_int.I1,
				    NULL, p_print_int_table, &cfg);
				break;
			case del_ftype_I2:
				cfg.width = 2;
				uint16_table_walk(f->symbols_by_int.I2,
				    NULL, p_print_int_table, &cfg);
				break;
			case del_ftype_I4:
				cfg.width = 4;
				uint32_table_walk(f->symbols_by_int.I4,
				    NULL, p_print_int_table, &cfg);
				break;
			default:
				assert(f->ftype == del_ftype_I1
				    || f->ftype == del_ftype_I2
				    || f->ftype == del_ftype_I4);
				break;
			}
			(void) ldh_radix_walk(buf, sizeof(buf),
	    			f->symbols_by_ldh, p_print_ldh_radix,
			       	cfg.prefix, NULL);
		}
		printf("static dnsextlang_field t%.4zx_fields[%zu] = {\n"
		      , n, s->n_fields);
		for (i = 0; i < s->n_fields; i++) {
			dnsextlang_field *f = &s->fields[i];
			size_t j;

			printf("\t{ ");
			if (f->ftype >= 0 && f->ftype <= del_ftype_Z)
				printf("%s", ftype_str[f->ftype]);
			else
				printf("%d", f->ftype);
			if (f->quals) {
				dnsextlang_qual q = f->quals;
				int qs = 0;

				printf(", (");
				for ( j = 0
				    ; j < sizeof(qual_str) / sizeof(const char *)
				    ; j++ ) {
					if (q & (1 << j)) {
						if (qs) putchar('|');
						qs = 1;
						printf("%s", qual_str[j]);
					}
					q &= ~(1 << j);
				}
				if (q)
					printf("|%x", q);
				printf(")");
			} else
				printf(", 0");

			if (f->symbols_by_ldh) {
				char label[100], *d = label;
				const char *s;

				for ( s = f->symbols_by_ldh->label
				    ; *s; s++, d++)
					*d = *s == '-' ? '_' : *s;
				*d = 0;

				printf("\n\t, { (void *)t%.4zx_%zu_%s }, "
				       "&t%.4zx_%zu_%s"
				      , n, i
				      , ( f->ftype == del_ftype_I1 ? "xx"
				        : f->ftype == del_ftype_I2 ? "xxxx"
				        : "xxxxxxxx" )
				      , n, i, *label ? label : "ldh_radix");
			} else
				printf(", { NULL }, NULL");
			if (f->tag)
				printf(", \"%s\"", f->tag);
			else
				printf(", NULL");

			if (f->description)
				printf("\n\t, \"%s\"", f->description);
			else
				printf(", NULL");

			printf(" }");
			if (i + 1 < s->n_fields)
				printf(",\n");
			else
				printf("\n");
		}
		printf("};\n");
	}
	printf("static dnsextlang_stanza t%.4zx = "
	       "{\n\t\"%s\", %zu,", n, s->name, (size_t)s->number);
	printf(" (");
	not_first = 0;
	for (i = 0; i < 26; i++) {
		if (s->options & (1 << i)) {
			if (not_first)
				printf("|");
			printf("del_option_%c", (char)(i + 'A'));
			not_first++;
		}
	}
	printf("),\n\t");
	if (s->description)
		printf("\"%s\",\n\t", s->description);
	else
		printf("NULL,");

	printf("%zu, ", s->n_fields);
	if (s->n_fields)
		printf("t%.4zx_fields", n);
	else
		printf("NULL");
	printf("\n};\n");
}

static void p_print_stanza(
    size_t depth, uint64_t n, const void *stanza, void *userarg)
{
	const dnsextlang_stanza *s = stanza;

	(void)depth; (void)userarg;
	p_export_stanza2c(n, s);
}

static void p_print_table(
    size_t depth, uint64_t n, const void *table_, void *userarg)
{
	const void * const *table = table_;
	size_t i;

	(void)userarg;
	if (depth) {
		printf("static const dnsextlang_stanza *"
		       "t%.2zxxx[256] = {", n);
		for (i = 0; i < 256; i++) {
			printf(i % 10 ? "," : i ? "\n\t," : "\n\t ");
			if (table[i])
				printf("&t%.4zx", (n << 8) | i);
			else
				printf(" NULL ");
		}
	} else {
		printf("static const dnsextlang_stanza **"
		       "rrtypes_table[256] = {");
		for (i = 0; i < 256; i++) {
			printf(i % 10 ? "," : i ? "\n\t," : "\n\t ");
			if (table[i])
				printf(" t%.2zxxx", i);
			else
				printf(" NULL ");
		}
	}
	printf("};\n");
}

status_code dnsextlang_export_def2c(dnsextlang_def *d, return_status *st)
{
	status_code c;
	char buf[1024] = "";

	printf("#include \"dnsextlang.h\"\n");

	uint16_table_walk(
	    d->stanzas_by_u16, p_print_stanza, p_print_table, NULL);
	if ((c = ldh_radix_walk(buf, sizeof(buf),
	    d->stanzas_by_ldh, p_print_ldh_radix, "rr_", NULL)))
		return c;
	printf("static dnsextlang_def p_dns_default_rrtypes = {\n\t");
	printf("(void *)rrtypes_table, &rr_ldh_radix, NULL };\n");
	printf("dnsextlang_def *dns_default_rrtypes = "
	       "&p_dns_default_rrtypes;\n");
	return STATUS_OK;
}

int main(int argc, char **argv)
{
	dns_config      cfg = DNS_CONFIG_DEFAULTS;
	return_status   st  = RETURN_STATUS_CLEAR;
	dnsextlang_def *def;

	if (argc < 2) {
		fprintf(stderr, "usage: %s <rrtypes.txt>\n", argv[0]);
		return EXIT_FAILURE;
	}
	cfg.rrtypes = NULL;
	if ((def = dnsextlang_def_new_from_fn_(&cfg, argv[1], &st)))
		(void) dnsextlang_export_def2c(def, &st);
       
	if (st.code)
		print_status(&st);
	if (def)
		dnsextlang_def_free(def);
	return st.code ? EXIT_FAILURE : EXIT_SUCCESS;
}

