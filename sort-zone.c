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
/* #define NDEBUG 1 */
#define _LARGEFILE64_SOURCE
#include <assert.h>
#include <ctype.h>
#include <fcntl.h>
#include <inttypes.h>
#include <pthread.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <time.h>
#include <unistd.h>

#define THREAD_THRESHOLD 8192
#define SPLIT_SIZE 2145000000
#if 1
# define INLINE inline
#else
# define INLINE
#endif
#if 1
# define LOWER_CMP(x) tolower(x)
# define LOWER_CPY(x) (x)
#else
# define LOWER_CMP(x) (x)
# define LOWER_CPY(x) tolower(x)
#endif

long        pagesize          = 4096 * 64;
long        pagesize_preserve = 4096 *  1;
time_t      start_t           = 0;
typedef struct ttl_count ttl_count;
struct ttl_count {
	uint32_t   ttl;
	uint32_t   cnt;
	ttl_count *nxt;
};
ttl_count   ttl_counts[65536] = { 0 };
ttl_count  *max_ttl           = ttl_counts;
int         ttl_collisions    = 0;

#define ARLEN(X) (sizeof(X) / sizeof(*X))

ttl_count *find_ttl(uint32_t t)
{
	uint32_t x;
	ttl_count *r;

	if (!t)
		return ttl_counts;

	x = ((t >> 16) ^ t) * 0x119de1f3;
	x = ((x >> 16) ^ x) * 0x119de1f3;
	x =  (x >> 16) ^ x;

	r = &ttl_counts[x % ARLEN(ttl_counts)];
	if (x && r->ttl == 0)
		r->ttl = t;
	else {
		while (r->nxt) {
			if (r->nxt->ttl == t)
				return r->nxt;
			r = r->nxt;
		}
		r->nxt = malloc(sizeof(ttl_count));
		assert(r->nxt);
		ttl_collisions += 1;
		r->nxt->ttl = t;
		r->nxt->cnt = 0;
		r->nxt->nxt = NULL;
		return r->nxt;
	}
	return r;
}

INLINE void ttl_count_free(ttl_count *r)
{
	if (r) {
		ttl_count_free(r->nxt);
		free(r);
	}
}

void cleanup_ttl_counts()
{
	if (ttl_collisions) {
		ttl_count *r;

		for (r = ttl_counts; r < ttl_counts + ARLEN(ttl_counts); r++) {
			ttl_count_free(r->nxt);
		}
	}
}

typedef struct rr_part {
	const char *start;
	const char *end;
	size_t line_nr;
	size_t col_nr;
	const char *fn;
} rr_part;

typedef struct zone_iter {
	int         fd;
	char       *to_free;
	const char *text;
	const char *end;
	const char *cur;

	const char *line;
	size_t count;

	rr_part *current_part;
	rr_part *parts;
	size_t   parts_sz;
	rr_part  parts_spc[1024];

	unsigned int free : 1;
} zone_iter;

int zone_iter_init(zone_iter *i, const char *fn)
{
	struct stat statbuf;

	if ((i->fd = open(fn, O_RDONLY)) < 0)
		return -1;

	if (fstat(i->fd, &statbuf) < 0) {
		close(i->fd);
		return -1;
	}
	if ((i->to_free = mmap( NULL, statbuf.st_size, PROT_READ
	                      , MAP_PRIVATE, i->fd, 0)) == MAP_FAILED) {
		close(i->fd);
		return -1;
	}
	i->line = i->cur = i->text = i->to_free;
	i->end = i->text + statbuf.st_size;
	i->count = 0;
	i->parts = i->parts_spc;
	i->parts_sz = sizeof(*i->parts_spc);
	i->free = 1;
	return 0;
}

const char *zone_iter_get_part(zone_iter *i, size_t *olen);
INLINE const char *zone_iter_return(zone_iter *i, size_t *olen)
{
	const char *r = i->line;

	*olen = i->cur - r;
	i->count += 1;
	i->line = ++i->cur;
	if (i->free && (r - i->to_free) > pagesize) {
		size_t n = (r - i->to_free) / pagesize;

		n *= pagesize;
		n -= pagesize_preserve;

		munmap(i->to_free, n);
		i->to_free += n;
	}
	if (i->current_part == i->parts)
		return zone_iter_get_part(i, olen);

	i->current_part->start = NULL;

	return r;
}

INLINE const char *zone_iter_at_end(zone_iter *i, size_t *olen)
{
	if (i->line) {
		const char *r = i->line;

		i->current_part->start = NULL;

		*olen = i->end - r;
		i->count += 1;
		i->line = NULL;
		return r;
	}
	if (i->free) {
		munmap(i->to_free, (i->end - i->to_free));
		i->to_free = NULL;
	}
	close(i->fd);
	i->fd = -1;
	return NULL;
}

const char *zone_iter_get_closing_part(zone_iter *i, size_t *olen)
{
	switch (*i->cur) {
	case ';':
		/* A comment is NO PART, but skip till end-of-line */
		while (++i->cur < i->end)
			if (*i->cur == '\n') {
				i->cur += 1;
				return zone_iter_get_closing_part(i, olen);
			}
		return zone_iter_at_end(i, olen);

	case ' ': case '\t': case '\f': case '\n':
		while (++i->cur < i->end)
			switch (*i->cur) {
			case ' ': case '\t': case '\f': case '\n':
				/* Skip whitespace */
				continue;
			default:
				/* Non whitespace get this part */
				return zone_iter_get_closing_part(i, olen);
			}
		return zone_iter_at_end(i, olen);

	case ')':
		i->cur += 1;
		return zone_iter_get_part(i, olen);

	default:
		i->current_part->start = i->cur;
		while (i->cur < i->end)
			switch (*i->cur) {
			case ' ': case '\t': case '\f': case '\n':
				/* Whitespace part, get (or skip) */
				i->current_part->end = i->cur;
				i->current_part += 1;
				return zone_iter_get_closing_part(i, olen);

			case ')':
				i->current_part->end = i->cur;
				i->current_part += 1;
				i->cur += 1;
				return zone_iter_get_part(i, olen);

			default:
				/* Skip non whitespace */
				i->cur += 1;
				continue;
			}
		i->current_part->end = i->cur;
		i->current_part += 1;
		return zone_iter_at_end(i, olen);
	}
}


const char *zone_iter_get_part(zone_iter *i, size_t *olen)
{
	switch (*i->cur) {
	case ';':
		/* A comment is NO PART, but skip till end-of-line */
		while (++i->cur < i->end)
			if (*i->cur == '\n')
				return zone_iter_return(i, olen);
		return zone_iter_at_end(i, olen);

	case '\n':
		/* Remaining space is NO PART */
		return zone_iter_return(i, olen);

	case ' ': case '\t': case '\f':
		while (++i->cur < i->end)
			switch (*i->cur) {
			case '\n':
				/* Remaining space is no part */
				return zone_iter_return(i, olen);

			case ' ': case '\t': case '\f':
				/* Skip whitespace */
				continue;
			default:
				/* Non whitespace get this part */
				return zone_iter_get_part(i, olen);
			}
		return zone_iter_at_end(i, olen);

	case '(':
		i->cur += 1;
		return zone_iter_get_closing_part(i, olen);

	default:
		i->current_part->start = i->cur;
		while (i->cur < i->end)
			switch (*i->cur) {
			case '\n':
				/* Remaining space is no part */
				i->current_part->end = i->cur;
				i->current_part += 1;
				return zone_iter_return(i, olen);

			case ' ': case '\t': case '\f':
				/* Whitespace part, get (or skip) */
				i->current_part->end = i->cur;
				i->current_part += 1;
				return zone_iter_get_part(i, olen);

			case '\\':
				i->cur += 1;
				if (i->cur < i->end && isspace(*i->cur))
					i->cur += 1;
				continue;
			default:
				/* Skip non whitespace */
				i->cur += 1;
				continue;
			}
		i->current_part->end = i->cur;
		i->current_part += 1;
		return zone_iter_at_end(i, olen);
	}
}

const char *zone_iter_next(zone_iter *i, size_t *olen)
{
	i->current_part = i->parts;
	return zone_iter_get_part(i, olen);
}

typedef struct wf_labels {
	uint8_t l[128][64];
	size_t  n;
} wf_labels;

INLINE int wf_labels_are_fqdn(wf_labels *labels)
{ return labels->n != 0 && labels->l[labels->n - 1][0] == 0; }

INLINE int wf_labels_equal(wf_labels *a, wf_labels *b)
{
	size_t i;

	if (a->n != b->n)
		return 0;

	for (i = 0; i < a->n; i++) {
		uint8_t *l, *r, j;

		l = a->l[i];
		r = b->l[i];
		if (*l != *r)
			return 0;
		for (j = *l++, r++; j; j--, l++, r++)
			if (*l != *r && LOWER_CMP(*l) != LOWER_CMP(*r))
				return 0;
	}
	return 1;
}

INLINE void wf_labels_cpy(wf_labels *dst, wf_labels *src)
{
	memcpy(dst->l, src->l, src->n * sizeof(src->l[0]));
	dst->n = src->n;
}

INLINE int wf_labels_cat(wf_labels *dst, wf_labels *src)
{
	if (dst->n + src->n > 128)
		return 0;

	memcpy(dst->l + dst->n, src->l, src->n * sizeof(src->l[0]));
	dst->n += src->n;
	return 1;
}


typedef struct zone_wf_iter {
	zone_iter   zi;

	size_t      rr_len;
	const char *rr;

	wf_labels   origin;
	wf_labels   owner;
	int         same; /* owner & origin same as in previous iteration */
	ttl_count  *orig_ttl;
	uint32_t    ttl;
	rr_part    *rr_type;
	uint16_t    rr_class;
} zone_wf_iter;

int dname2wf(const char *dname, size_t len, wf_labels *labels)
{
	size_t old_n = labels->n;
	int same = 1;

	for (labels->n = 0; len; labels->n++) {
		uint8_t *pq = labels->l[labels->n], *q = pq + 1;

		while (len && (q - pq < 64)) {
			if (*dname == '.') {
				break;

			} else if (*dname == '\\' && len >= 2) {
				uint16_t val;
				if (len >= 4
				&&  isdigit(dname[1])
				&&  isdigit(dname[2])
				&&  isdigit(dname[3])) {
					val = (dname[1] - '0') * 100
					    + (dname[2] - '0') *  10
					    + (dname[3] - '0');
					if (*q != val) {
						same = 0;
						*q = val;
					}
					q++;
					dname += 4; len -= 4;
				} else {
					if (*q != LOWER_CPY(dname[1])) {
						same = 0;
						*q = LOWER_CPY(dname[1]);
					}
					q++;
					dname += 2; len -= 2;
				}
			} else {
				if (*q != LOWER_CPY(*dname)) {
					same = 0;
					*q = LOWER_CPY(*dname);
				}
				q++;
				dname += 1;
				len--;
			}
		}
		if ((q - pq) - 1 == 0)
			break;

		if (*pq != (q - pq) - 1) {
			same = 0;
			*pq = (q - pq) - 1;
		}
		if (len) {
			/* assert(*dname == '.'); */
			dname++; len--;
			if (len == 0)
				labels->l[++labels->n][0] = 0;
		}
	}
	return same ? (old_n == labels->n ? 1 : 2) : 0;
}

INLINE uint32_t wf_parse_ttl(const char *str, size_t sz)
{
	char buf[11], *endptr;

	assert(sz < sizeof(buf));
	memcpy(buf, str, sz);
	buf[sz] = 0;

	return strtoul(buf, &endptr, 10);
}


zone_wf_iter *zone_wf_iter_next(zone_wf_iter *i);
zone_wf_iter *zone_wf_iter_process_rr(zone_wf_iter *i)
{
	rr_part *part = i->zi.parts;
	ssize_t part_sz;

	part_sz = (part->end - part->start);
	if (part->start > i->rr) {
		i->same = 1; /* pass: Owner is previous owner */

	} else if (part_sz <= 0)
		return zone_wf_iter_next(i); /* Empty line? */

	else if (part->start[0] == '@' && part_sz == 1) {
		/* Owner is origin */
		i->same = wf_labels_equal(&i->owner, &i->origin);
		wf_labels_cpy(&i->owner, &i->origin);
		part++;
		part_sz = (part->end - part->start);

	} else if (part->start[0] != '$') {
		/* Regular owner name */
		size_t old_n = i->owner.n;
		int s = dname2wf(part->start, part_sz, &i->owner);

		if (wf_labels_are_fqdn(&i->owner))
			i->same = s == 1;
		else {
			wf_labels_cat(&i->owner, &i->origin);
			i->same = s == 2 && old_n == i->owner.n;
		}
		part++;
		part_sz = (part->end - part->start);

	} else if (part_sz == 7
	       && strncasecmp(part->start, "$ORIGIN", 7) == 0) {
		/* $ORIGIN */
		part++;
		dname2wf(part->start, part->end-part->start, &i->origin);
		return zone_wf_iter_next(i);

	} else if (part_sz == 4 && strncasecmp(part->start, "$TTL", 4) == 0) {
		/* $TTL */
		part++;
		i->orig_ttl = find_ttl(wf_parse_ttl(
		    part->start, part->end - part->start));
		return zone_wf_iter_next(i);
	} else {
		/* Other $ directive */
		return zone_wf_iter_next(i);
	}
	/* Skip class */
	if (part->start && part->start[0] >= '0' && part->start[0] <= '9') {
		/* TTL */
		ttl_count *c; 
		i->ttl = wf_parse_ttl(part->start, part->end - part->start);
		c = find_ttl(i->ttl);
		if (++c->cnt > max_ttl->cnt)
			max_ttl = c;
		part++;
		part_sz = (part->end - part->start);
	} else {
		i->ttl = i->orig_ttl->ttl;
		if (++i->orig_ttl->cnt > max_ttl->cnt)
			max_ttl = i->orig_ttl;
	}
	/* Is last part class? */
	if (part_sz == 2) {
		if ((part->start[0] == 'I' || part->start[0] == 'i')
		&&  (part->start[1] == 'N' || part->start[1] == 'n')) {
			i->rr_class = 1;
			part++;

		} else if ((part->start[0] == 'C' || part->start[0] == 'c')
		       &&  (part->start[1] == 'H' || part->start[1] == 'h')) {
			i->rr_class = 3;
			part++;

		} else if ((part->start[0] == 'H' || part->start[0] == 'h')
		       &&  (part->start[1] == 'S' || part->start[1] == 's')) {
			i->rr_class = 4;
			part++;
		}
	} else if (part_sz > 5 && part_sz < 11
	       && (part->start[0] == 'C' || part->start[0] == 'c')
	       && (part->start[1] == 'L' || part->start[1] == 'l')
	       && (part->start[2] == 'A' || part->start[2] == 'a')
	       && (part->start[3] == 'S' || part->start[3] == 's')
	       && (part->start[4] == 'S' || part->start[4] == 's')) {
		char nptr[7], *endptr;
		unsigned long int c;
		
		memcpy(nptr, part->start + 5, part_sz - 5);
		nptr[part_sz - 5] = 0;
		c = strtoul(nptr, &endptr, 10);
		if (*endptr == 0) {
			i->rr_class = c;
			part++;
		}
	}
	i->rr_type = part;
	return i;
}

zone_wf_iter *zone_wf_iter_init(
    zone_wf_iter *i, const char *fn, const char *origin)
{
	if (zone_iter_init(&i->zi, fn) > 0)
		return NULL;

	if (!(i->rr = zone_iter_next(&i->zi, &i->rr_len)))
		return NULL;

	memset(&i->owner, 0, sizeof(i->owner));
	memset(&i->origin, 0, sizeof(i->origin));
	dname2wf(origin, strlen(origin), &i->origin);
	if (!wf_labels_are_fqdn(&i->origin))
		i->origin.l[i->origin.n++][0] = 0;

	i->orig_ttl = find_ttl(3600);
	i->rr_class = 1;
	i->same = 0;
	return zone_wf_iter_process_rr(i);
}

zone_wf_iter *zone_wf_iter_next(zone_wf_iter *i)
{
	if (!(i->rr = zone_iter_next(&i->zi, &i->rr_len)))
		return NULL;
	return zone_wf_iter_process_rr(i);
}

#define BIT32      0x80000000
#define BIT32_MASK 0x7FFFFFFF

typedef struct wf_dname_ref {
	uint32_t ttl;
	uint16_t txt_sz;
	uint8_t  origin_sz;
	uint8_t  dname_sz;
	uint8_t  dname[];
} wf_dname_ref;

INLINE int wf_dname_cmp(const void *A, const void *B)
{
	const wf_dname_ref *a = *(wf_dname_ref * const *)A;
	const wf_dname_ref *b = *(wf_dname_ref * const *)B;
	const uint8_t *l, *r;
	uint8_t lsz, rsz;

	if (a->origin_sz <= b->origin_sz) {
		l = a->dname + a->origin_sz;
		r = b->dname + a->origin_sz;
	} else  {
		l = a->dname + b->origin_sz;
		r = b->dname + b->origin_sz;
	}
	while (*l) {
		if (!*r)
			return 0;
		for (lsz = *l++, rsz = *r++; lsz; l++, r++, lsz--, rsz--) {
			if (!rsz)
				return 0;
			if (LOWER_CMP(*l) != LOWER_CMP(*r))
				return LOWER_CMP(*l) < LOWER_CMP(*r) ? 1 : 0;
		}
		if (rsz)
			return 1;
	}
	if (*r)
		return 1;
	return a < b ? 1 : 0;
}


typedef struct p_qsort_args {
	wf_dname_ref **arr;
	int64_t        left;
	int64_t        right;
} p_qsort_args;

void p_qsort(wf_dname_ref **arr, int64_t left, int64_t right);
void *p_qsort_start(void *args)
{
	p_qsort_args *a = (p_qsort_args *)args;
	p_qsort(a->arr, a->left, a->right);
	return NULL;
}

INLINE void swap(wf_dname_ref **arr, uint64_t i, uint64_t j)
{
	wf_dname_ref **a = arr + i;
	wf_dname_ref **b = arr + j;
	wf_dname_ref *tmp;

	tmp = *a;
	*a = *b;
	*b = tmp;
}

INLINE uint64_t average2(uint64_t a, uint64_t b)
{ return ((a ^ b) >> 1) + (a & b); }

void p_qsort(wf_dname_ref **arr, int64_t left, int64_t right)
{
	int64_t i, last;
	pthread_t lt;
	p_qsort_args qa;

	if (left >= right)
		return;
	swap(arr, left, average2(left, right));
	last = left;
	for (i = left + 1; i <= right; i++) {
		if (wf_dname_cmp(arr + i, arr + left)) {
			last++;
			swap(arr, last, i);
		}
	}
	swap(arr, left, last);
	if (right - left > THREAD_THRESHOLD) {
		qa.arr   = arr;
		qa.left  = left;
		qa.right = last - 1;
		if (!pthread_create( &lt, PTHREAD_CREATE_JOINABLE
		                   , p_qsort_start, (void*)&qa)) {
			p_qsort(arr, last + 1, right);
			pthread_join(lt, NULL);
			return;
		}
	}
	p_qsort(arr, left    , last - 1);
	p_qsort(arr, last + 1, right   );
}


typedef struct merger merger;
typedef void (*merger_nexter)(merger *m);
typedef void (*merger_destructor)(merger *m);
struct merger {
	wf_dname_ref     *cur;
	merger_nexter     next;
	merger_destructor free;
};

typedef struct combine {
	merger  m;
	merger *a;
	merger *b;
} combine;

void merger_next(merger *m)
{
	combine *c = (combine *)m;

	if (c->m.cur == c->a->cur)
		c->a->next(c->a);
	else {
		assert(c->m.cur == c->b->cur);
		c->b->next(c->b);
	}
	c->m.cur = c->a->cur == NULL ? (c->b->cur ? c->b->cur : NULL)
	         : c->b->cur == NULL ?  c->a->cur
	         : wf_dname_cmp(&c->a->cur, &c->b->cur) ? c->a->cur
	         : c->b->cur;
}

void merger_free(merger *m)
{
	combine *c = (combine *)m;

	if (c->a) {
		c->a->free(c->a);
		c->a = NULL;
	}
	if (c->b) {
		c->b->free(c->b);
		c->b = NULL;
	}
	free(c);
}

merger *merger_new(merger *a, merger *b)
{
	combine *c = malloc(sizeof(combine));

	assert(c != NULL);
	c->a = a;
	c->b = b;
	c->m.cur = a->cur == NULL ? (b->cur ? b->cur : NULL)
	         : b->cur == NULL ? a->cur
	         : wf_dname_cmp(&a->cur, &b->cur) ? a->cur : b->cur;
	c->m.next = merger_next;
	c->m.free = merger_free;
	return &c->m;
}


typedef struct part part;
struct part {
	merger         m;
	pthread_t      lt;
	wf_dname_ref **refs;
	wf_dname_ref **ref;
	wf_dname_ref **last_ref;
	uint8_t       *mem;
	uint8_t       *cur;
	uint8_t       *end;
	char           tmpfn[1024];
	int            tmpfd;
	size_t         mem_sz;
	size_t         n_refs;
	part          *prev;
};

void part_merger_next(merger *m)
{
	uint32_t ttl;
	part *p = (part *)m;
	wf_dname_ref *r = (void *)p->cur;

	assert(m->cur == r);
	ttl = r->ttl;
	r = (void *)(r->dname + r->dname_sz + 1 + r->txt_sz);
	while (ttl & BIT32) {
		ttl = r->ttl;
		r = (void *)(r->dname + r->txt_sz);
	}
	p->cur = (void *)r;
	if (p->cur >= p->end) {
		p->cur = NULL;
		close(p->tmpfd);
		unlink(p->tmpfn);
		m->cur = NULL;
		return;
	}
	m->cur = (wf_dname_ref *)p->cur;
	while (p->cur - p->mem > pagesize) {
		size_t n = (p->cur - p->mem) / pagesize;

		n *= pagesize;
		n -= pagesize_preserve;
		munmap(p->mem, n);
		p->mem += n;
	}
}

void part_merger_free(merger *m)
{
	part *p = (part *)m;

	assert(p->cur == NULL && p->mem != NULL
	    && p->end != NULL && p->mem < p->end);

	/**
	 ** p->prev is freed by combine
	 **
	 *
	 * if (p->prev) {
	 * 	p->prev->m.free(&p->prev->m);
	 * 	p->prev = NULL;
	 * }
	 */
	munmap(p->mem, p->end - p->mem);
	free(p);
}

part *part_new()
{
	part *p;

	if (!(p = malloc(sizeof(part))))
		return NULL;
	if (!(p->cur = p->mem = malloc(SPLIT_SIZE)))
		return NULL;
	else	p->end = p->mem + SPLIT_SIZE;
	if (!(p->ref = p->refs= malloc(SPLIT_SIZE/32*sizeof(wf_dname_ref *))))
		return NULL;
	else	p->last_ref = &p->refs[SPLIT_SIZE/32];
	strcpy(p->tmpfn, "/tmp/sort-zone-XXXXXX");
	p->tmpfd = -1;
	p->mem_sz = 0;
	p->n_refs = 0;
	p->prev = NULL;
	p->lt = 0;
	return p;
}

void part_mktmpfn(part *p, const char *fn)
{
	size_t   cnt = 0;
	part *c = p->prev;
	const char *s = strrchr(fn, '/');

	s = s ? s + 1 : fn;
	while (c) {
		c = c->prev;
		cnt += 1;
	}
	snprintf( p->tmpfn, sizeof(p->tmpfn)
	        , "/tmp/sort-zone-%s-%.2zu-XXXXXX", s, cnt);
}

void *part_sort_save_(void *arg)
{
	part *p = (part *)arg;
	wf_dname_ref **ref;

	p->mem_sz = p->cur - p->mem;
	p->n_refs = p->ref - p->refs;
	fprintf(stderr, "Sorting %zu bytes in %zu RRs at %zd\n"
	              , p->mem_sz, p->n_refs, time(NULL) - start_t);
	p_qsort(p->refs, 0, (p->ref - p->refs) - 1);
	fprintf(stderr, "Saving  %zu bytes in %zu RRs at %zd\n"
	              , p->mem_sz, p->n_refs, time(NULL) - start_t);
	if ((p->tmpfd = mkstemp(p->tmpfn)) < 0)
		perror("Could not create temporary part file");

	FILE *f = fdopen(p->tmpfd, "w");
	for ( ref = p->refs; ref < p->ref; ref++) {
		wf_dname_ref *r = *ref;
		uint8_t *txt_pos = r->dname + r->dname_sz + 1;

		if (!fwrite(r, sizeof(wf_dname_ref) + r->dname_sz + 1
		                                    + r->txt_sz, 1, f))
			perror("Error writing to temporary part file");

		while (r->ttl & BIT32) {
			r = (void *)(txt_pos + r->txt_sz);
			txt_pos = r->dname;
			fwrite(r, sizeof(wf_dname_ref) + r->txt_sz, 1, f);
		}
	}
	fclose(f);
	p->tmpfd = -1;
	free(p->mem);
	free(p->refs);
	p->mem = p->cur = p->end = NULL;
	p->refs = p->ref = p->last_ref = NULL;
	fprintf(stderr, "Saved   %zu bytes in %zu RRs at %zd\n"
	              , p->mem_sz, p->n_refs, time(NULL) - start_t);
	return NULL;
}

INLINE void part_sort_save(part *p, const char *fn)
{
	part_mktmpfn(p, fn);
	part_sort_save_(p);
}

INLINE part *part_next(part *p, const char *fn)
{
	part *n;

	if ((n = part_new(p)))
		n->prev = p;

	part_mktmpfn(p, fn);
	if (pthread_create( &p->lt, PTHREAD_CREATE_JOINABLE
	                  , part_sort_save_, (void *)p))
		part_sort_save_(p);
	return n;
}


typedef struct zone_writer {
	uint32_t origin_ttl;
	FILE    *f;
	ssize_t  prev_dname_sz;
	ssize_t  origin_sz;
	const uint8_t *prev_dname;
} zone_writer;

void zone_writer_init(zone_writer *zw, uint32_t max_ttl, FILE *f)
{
	assert(zw);
	zw->origin_ttl    = max_ttl;
	zw->f             = f;
	zw->prev_dname_sz = -1;
	zw->origin_sz     = -1;
	zw->prev_dname    = NULL;
	fprintf(f, "$TTL %" PRIu32 "\n", max_ttl);
}

void print_dname(const uint8_t *dname, uint8_t dname_sz, FILE *f)
{
	const uint8_t  *labels[128];
	const uint8_t  *end = dname + dname_sz;
	const uint8_t **label;

	for ( label = labels
	    ; dname < end && *dname && label < &labels[ sizeof(labels)
	                                              / sizeof(*labels)]
	    ; dname += *dname + 1, label++)
		*label = dname;

	while (label > labels) {
		uint8_t sz;
		const uint8_t *l;

		label -= 1;

		for (l = *label, sz = *l++; sz; l++, sz--) {
			switch (*l) {
			case '.': case ';': case '(':
			case ')': case '\\':
				putc('\\', f);
				putc(*l, f);
				break;
			default:
				if (isascii(*l) && isgraph(*l))
					putc(*l, f);
				else
					fprintf(f, "\\%03u", *l);
				break;
			}
		}
		if (label > labels)
			putc('.', f);
	}
}

INLINE int dname_equal(const uint8_t *l, const uint8_t *r, size_t sz)
{
	while (sz--) {
		size_t i;

		if (*l != *r)
			return 0;
		else if (!*l)
			return 1;
		for (i = *l++, r++; sz && i > 0; i--, l++, r++, sz--)
			if (*l != *r && LOWER_CMP(*l) != LOWER_CMP(*r))
				return 0;
	}
	return 1;
}

void zone_writer_next(zone_writer *zw, const wf_dname_ref *r)
{
	uint32_t ttl;
	const uint8_t *txt_pos;

	if (zw->origin_sz != r->origin_sz) {
		zw->origin_sz = r->origin_sz;
		fputs("$ORIGIN ", zw->f);
		print_dname(r->dname, zw->origin_sz, zw->f);
		fputs(".\n", zw->f);
	}
	if (r->dname_sz != zw->prev_dname_sz) {
		zw->prev_dname_sz = r->dname_sz;
		if (r->dname_sz == zw->origin_sz)
			fputs("@ ", zw->f);
		else {
			print_dname( r->dname + zw->origin_sz
				   , r->dname_sz - zw->origin_sz
				   , zw->f);
			putc(' ', zw->f);
		}
	} else if (zw->prev_dname
	       &&  dname_equal( r->dname   + zw->origin_sz
			        , zw->prev_dname + zw->origin_sz
			        , zw->prev_dname_sz - zw->origin_sz ))
		putc(' ', zw->f);

	else if (zw->prev_dname_sz == zw->origin_sz)
		fputs("@ ", zw->f);
	else {
		print_dname( r->dname + zw->origin_sz
			   , zw->prev_dname_sz - zw->origin_sz
			   , zw->f);
		putc(' ', zw->f);
	}
	zw->prev_dname = r->dname;
	txt_pos = r->dname + r->dname_sz + 1;
	for (;;) {
		ttl = r->ttl;
		if ((ttl & BIT32_MASK) != zw->origin_ttl)
			fprintf(zw->f, "%" PRIu32 " ", (ttl & BIT32_MASK));
		fwrite(txt_pos, r->txt_sz, 1, zw->f);
		putc('\n', zw->f);
		if (ttl & BIT32) {
			r = (void *)(txt_pos + r->txt_sz);
			txt_pos = r->dname;
			putc(' ', zw->f);
		} else
			break;
	}
}

int main(int argc, char **argv)
{
	zone_wf_iter  zi_spc, *zi = NULL;
#ifndef NDEBUG
	int           s;
#endif
	part         *p = NULL;
	char          outfn[4096];
	FILE         *f;
	zone_writer   zw;
	size_t        n_ps;
	part         *c;
	merger       *ms[64], *m;
	wf_dname_ref *prev_ref = NULL;

	/* Initialize globals */
	pagesize          = sysconf(_SC_PAGESIZE) * 64;
	pagesize_preserve = sysconf(_SC_PAGESIZE) *  1;
	start_t           = time(NULL);
	max_ttl           = find_ttl(3600);

	if (argc < 2 || argc > 3) {
		printf("usage: %s <zonefile> [ <origin> ]\n", argv[0]);
		return 1;
	}
	if (!(zi = zone_wf_iter_init(&zi_spc, argv[1], argc==3?argv[2]:""))) {
		fprintf(stderr, "Could not open zone\n");
		return EXIT_FAILURE;
	}
	if (!(p = part_new())) {
		fprintf(stderr, "Memory allocation error\n");
		return EXIT_FAILURE;
	}
	while (zi) {
		ssize_t n;
		uint8_t *dname;
		wf_dname_ref *ref;

		if (p->ref >= p->last_ref
		||  p->cur + 1024 + zi->rr_len > p->end) {
			prev_ref = NULL;
			if (!(p = part_next(p, argv[1]))) {
				fprintf(stderr, "Could not create next part\n");
				return EXIT_FAILURE;
			}
		}
		ref         = (void *)p->cur;
		ref->txt_sz =  zi->rr_len
		            - (zi->rr_type->start - zi->rr);
		ref->ttl    =  zi->ttl;

		if (prev_ref && zi->same) {
			ref->dname_sz = 0;
			ref->origin_sz = 255;
			memcpy(ref->dname, zi->rr_type->start, ref->txt_sz);
			p->cur = ref->dname + ref->txt_sz;
			prev_ref->ttl |= BIT32;
			prev_ref = ref;
			zi = zone_wf_iter_next(zi);
			continue;
		}
		dname = ref->dname;
		for (n = (ssize_t)zi->owner.n - 2; n >= 0; n--) {
			memcpy(dname, zi->owner.l[n], zi->owner.l[n][0] + 1);
			dname += zi->owner.l[n][0] + 1;
			if (n == zi->owner.n - zi->origin.n)
				ref->origin_sz = dname - ref->dname;
		}
		ref->dname_sz = dname - ref->dname;
		*dname++ = 0;
		memcpy(dname, zi->rr_type->start, ref->txt_sz);
		p->cur = dname + ref->txt_sz;
		*p->ref++ = prev_ref = ref;
		zi = zone_wf_iter_next(zi);
	}
#ifndef NDEBUG
	s = 
#endif
	    snprintf(outfn, sizeof(outfn), "%s.sorted", argv[1]);
	assert(s < sizeof(outfn));
	if (!(f = fopen(outfn, "w")))
		perror("Could not create output file");
	zone_writer_init(&zw, max_ttl->ttl, f);
	if (!p->prev) {
		wf_dname_ref **ref;
		/* Just one part, just sort and save this single part */
		p_qsort(p->refs, 0, (p->ref - p->refs) - 1);
		for (ref = p->refs; ref < p->ref; ref++) {
			zone_writer_next(&zw, *ref);
		}
		fclose(f);
		free(p->mem);
		free(p->refs);
		free(p);
		cleanup_ttl_counts();
		return 0;
	}
	part_sort_save(p, argv[1]);

	for (n_ps = 0, c = p; c; c = c->prev) {
		pthread_join(c->lt, NULL);
		c->tmpfd = open(c->tmpfn, O_RDONLY);
		assert(c->tmpfd >= 0);
		c->cur = c->mem = mmap(NULL, c->mem_sz, PROT_READ,
		    MAP_PRIVATE, c->tmpfd, 0);
		assert(c->mem != MAP_FAILED);
		c->end = c->mem + c->mem_sz;
		c->m.cur = (wf_dname_ref *)c->cur;
		c->m.next = part_merger_next;
		c->m.free = part_merger_free;
		ms[n_ps++] = &c->m;
	}
	while (n_ps > 1) {
		size_t i, j;
		for (i = 0, j = 0; i < n_ps; i += 2, j++) {
			if (i + 1 < n_ps)
				ms[j] = merger_new(ms[i], ms[i + 1]);

			else	ms[j] = ms[i];
		}
		n_ps = j;
	}
	for (m = ms[0]; m->cur; m->next(m)) {
		zone_writer_next(&zw, m->cur);
	}
	fclose(f);
	m->free(m);
	cleanup_ttl_counts();
	return 0;
}
