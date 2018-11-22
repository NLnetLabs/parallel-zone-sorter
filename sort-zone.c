#define _LARGEFILE64_SOURCE
#include <sys/mman.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <assert.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <ctype.h>  /* isdigit() */
#include <stdlib.h> /* strtoul() */
#include <time.h>
#include <pthread.h>

#define THREAD_THRESHOLD 8192
#define SPLIT_SIZE 2145000000

static long pagesize;
static time_t start_t = 0;

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

static const char *p_zone_iter_get_part(zone_iter *i, size_t *olen);
static inline const char *p_zone_iter_return(zone_iter *i, size_t *olen)
{
	const char *r = i->line;

	*olen = i->cur - r;
	i->count += 1;
	i->line = ++i->cur;
	if (i->free && (r - i->to_free) > pagesize) {
		size_t n = (r - i->to_free) / pagesize;

		munmap(i->to_free, n * pagesize);
		i->to_free += n * pagesize;
	}
	if (i->current_part == i->parts)
		return p_zone_iter_get_part(i, olen);

	i->current_part->start = NULL;

	return r;
}

static inline const char *p_zone_iter_at_end(zone_iter *i, size_t *olen)
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

static const char *p_zone_iter_get_closing_part(zone_iter *i, size_t *olen)
{
	switch (*i->cur) {
	case ';':
		/* A comment is NO PART, but skip till end-of-line */
		while (++i->cur < i->end)
			if (*i->cur == '\n') {
				i->cur += 1;
				return p_zone_iter_get_closing_part(i, olen);
			}
		return p_zone_iter_at_end(i, olen);

	case ' ': case '\t': case '\f': case '\n':
		while (++i->cur < i->end)
			switch (*i->cur) {
			case ' ': case '\t': case '\f': case '\n':
				/* Skip whitespace */
				continue;
			default:
				/* Non whitespace get this part */
				return p_zone_iter_get_closing_part(i, olen);
			}
		return p_zone_iter_at_end(i, olen);

	case ')':
		i->cur += 1;
		return p_zone_iter_get_part(i, olen);

	default:
		i->current_part->start = i->cur;
		while (i->cur < i->end)
			switch (*i->cur) {
			case ' ': case '\t': case '\f': case '\n':
				/* Whitespace part, get (or skip) */
				i->current_part->end = i->cur;
				i->current_part += 1;
				return p_zone_iter_get_closing_part(i, olen);

			case ')':
				i->current_part->end = i->cur;
				i->current_part += 1;
				i->cur += 1;
				return p_zone_iter_get_part(i, olen);

			default:
				/* Skip non whitespace */
				i->cur += 1;
				continue;
			}
		i->current_part->end = i->cur;
		i->current_part += 1;
		return p_zone_iter_at_end(i, olen);
	}
}


static const char *p_zone_iter_get_part(zone_iter *i, size_t *olen)
{
	switch (*i->cur) {
	case ';':
		/* A comment is NO PART, but skip till end-of-line */
		while (++i->cur < i->end)
			if (*i->cur == '\n')
				return p_zone_iter_return(i, olen);
		return p_zone_iter_at_end(i, olen);

	case '\n':
		/* Remaining space is NO PART */
		return p_zone_iter_return(i, olen);

	case ' ': case '\t': case '\f':
		while (++i->cur < i->end)
			switch (*i->cur) {
			case '\n':
				/* Remaining space is no part */
				return p_zone_iter_return(i, olen);

			case ' ': case '\t': case '\f':
				/* Skip whitespace */
				continue;
			default:
				/* Non whitespace get this part */
				return p_zone_iter_get_part(i, olen);
			}
		return p_zone_iter_at_end(i, olen);

	case '(':
		i->cur += 1;
		return p_zone_iter_get_closing_part(i, olen);

	default:
		i->current_part->start = i->cur;
		while (i->cur < i->end)
			switch (*i->cur) {
			case '\n':
				/* Remaining space is no part */
				i->current_part->end = i->cur;
				i->current_part += 1;
				return p_zone_iter_return(i, olen);

			case ' ': case '\t': case '\f':
				/* Whitespace part, get (or skip) */
				i->current_part->end = i->cur;
				i->current_part += 1;
				return p_zone_iter_get_part(i, olen);

			default:
				/* Skip non whitespace */
				i->cur += 1;
				continue;
			}
		i->current_part->end = i->cur;
		i->current_part += 1;
		return p_zone_iter_at_end(i, olen);
	}
}

const char *zone_iter_next(zone_iter *i, size_t *olen)
{
	i->current_part = i->parts;
	return p_zone_iter_get_part(i, olen);
}

typedef struct wf_labels {
	uint8_t l[128][64];
	size_t  n;
} wf_labels;

static inline int p_wf_labels_are_fqdn(wf_labels *labels)
{ return labels->n != 0 && labels->l[labels->n - 1][0] == 0; }

static inline void p_wf_labels_cpy(wf_labels *dst, wf_labels *src)
{
	memcpy(dst->l, src->l, src->n * sizeof(src->l[0]));
	dst->n = src->n;
}

static inline int p_wf_labels_cat(wf_labels *dst, wf_labels *src)
{
	if (dst->n + src->n > 128)
		return 0;

	memcpy(dst->l + dst->n, src->l, src->n * sizeof(src->l[0]));
	dst->n += src->n;
	return 1;
}

static int p_dname2wf(const char *dname, size_t len, wf_labels *labels)
{
	// printf("p_dname2wf(%.*s)\n", (int)len, dname);
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
					*q++ = val;
					dname += 4; len -= 4;
				} else {
					*q++ = dname[1];
					dname += 2; len -= 2;
				}
			} else {
				*q++ = *dname++;
				len--;
			}
		}
		*pq = (q - pq) - 1;
		if (len) {
			// assert(*dname == '.');
			dname++; len--;
			if (len == 0)
				labels->l[++labels->n][0] = 0;
		}
	}
	return 1;
}

typedef struct zone_wf_iter {
	zone_iter   zi;

	size_t      rr_len;
	const char *rr;

	wf_labels   origin;
	wf_labels   owner;
	uint32_t    orig_ttl;
	uint32_t    ttl;
	rr_part    *rr_type_or_class_type;
} zone_wf_iter;

static inline uint32_t p_wf_parse_ttl(const char *str, size_t sz)
{
	char buf[11], *endptr;

	assert(sz < sizeof(buf));
	memcpy(buf, str, sz);
	buf[sz] = 0;

	return strtoul(buf, &endptr, 10);
}

zone_wf_iter *zone_wf_iter_next(zone_wf_iter *i);
static zone_wf_iter *p_zone_wf_iter_process_rr(zone_wf_iter *i)
{
	rr_part *part = i->zi.parts;
	ssize_t part_sz;
	int r;

	if (part->start > i->rr) {
		; /* pass: Owner is previous owner */

	} else if ((part_sz = (part->end - part->start)) <= 0)
		return zone_wf_iter_next(i); /* Empty line? */

	else if (part->start[0] == '@' && part_sz == 1) {
		/* Owner is origin */
		p_wf_labels_cpy(&i->owner, &i->origin);
		part++;

	} else if (part->start[0] != '$') {
		/* Regular owner name */

		r = p_dname2wf(part->start, part_sz, &i->owner);
		assert(r);
		if (!p_wf_labels_are_fqdn(&i->owner)) {
			r = p_wf_labels_cat(&i->owner, &i->origin);
			assert(r);
		}
		part++;

	} else if (part_sz == 7
	       && strncasecmp(part->start, "$ORIGIN", 7) == 0) {
		/* $ORIGIN */
		part++;
		r = p_dname2wf(part->start, part->end-part->start, &i->origin);
		assert(r);
		return zone_wf_iter_next(i);

	} else if (part_sz == 4 && strncasecmp(part->start, "$TTL", 4) == 0) {
		/* $TTL */
		part++;
		i->orig_ttl = p_wf_parse_ttl(part->start, part->end - part->start);
		return zone_wf_iter_next(i);
	} else {
		/* Other $ directive */
		return zone_wf_iter_next(i);
	}
	/* Skip class */
	if (part->start && part->start[0] >= '0' && part->start[0] <= '9') {
		/* TTL */
		i->ttl = p_wf_parse_ttl(part->start, part->end - part->start);
		part++;
	} else
		i->ttl = i->orig_ttl;
	i->rr_type_or_class_type = part;
	return i;
}

zone_wf_iter *zone_wf_iter_init(
    zone_wf_iter *i, const char *fn, const char *origin)
{
	if (zone_iter_init(&i->zi, fn) > 0)
		return NULL;

	if (!(i->rr = zone_iter_next(&i->zi, &i->rr_len)))
		return NULL;

	if (!p_dname2wf(origin, strlen(origin), &i->origin))
		return NULL;

	else if (!p_wf_labels_are_fqdn(&i->origin))
		i->origin.l[i->origin.n++][0] = 0;

	i->owner = i->origin;
	i->orig_ttl = 3600;
	return p_zone_wf_iter_process_rr(i);
}

zone_wf_iter *zone_wf_iter_next(zone_wf_iter *i)
{
	if (!(i->rr = zone_iter_next(&i->zi, &i->rr_len)))
		return NULL;
	return p_zone_wf_iter_process_rr(i);
}

typedef struct wf_dname_ref {
	uint32_t ttl;
	uint16_t txt_sz;
	uint8_t  origin_pos;
	uint8_t  dname_sz;
	uint8_t  dname[];
} wf_dname_ref;

static inline int p_wf_dname_cmp(const void *A, const void *B)
{
	const wf_dname_ref *a = *(wf_dname_ref * const *)A;
	const wf_dname_ref *b = *(wf_dname_ref * const *)B;
	const uint8_t *l, *r;
	uint8_t lsz, rsz;

	for (l = a->dname, r = b->dname; *l;) {
		if (!*r)
			return 0;
		for (lsz = *l++, rsz = *r++; lsz; l++, r++, lsz--, rsz--) {
			if (!rsz)
				return 0;
			if (*l != *r)
				return *l < *r ? 1 : 0;
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
static void p_qsort(wf_dname_ref **arr, int64_t left, int64_t right);
static void *p_qsort_start(void *args)
{
	p_qsort_args *a = (p_qsort_args *)args;
	p_qsort(a->arr, a->left, a->right);
	return NULL;
}
static inline void p_swap(wf_dname_ref **arr, uint64_t i, uint64_t j)
{
	wf_dname_ref **a = arr + i;
	wf_dname_ref **b = arr + j;
	wf_dname_ref *tmp;

	tmp = *a;
	*a = *b;
	*b = tmp;
}
static inline uint64_t p_average2(uint64_t a, uint64_t b)
{ return ((a ^ b) >> 1) + (a & b); }
static void p_qsort(wf_dname_ref **arr, int64_t left, int64_t right)
{
	int64_t i, last;
	pthread_t lt;
	p_qsort_args qa;

	if (left >= right)
		return;
	p_swap(arr, left, p_average2(left, right));
	last = left;
	for (i = left + 1; i <= right; i++) {
		if (p_wf_dname_cmp(arr + i, arr + left)) {
			last++;
			p_swap(arr, last, i);
		}
	}
	p_swap(arr, left, last);
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

typedef struct p_merger p_merger;
typedef void (*p_merger_nexter)(p_merger *m);
struct p_merger {
	wf_dname_ref   *cur;
	p_merger_nexter next;
};

typedef struct p_combine {
	p_merger  m;
	p_merger *a;
	p_merger *b;
} p_combine;

static void p_merger_next(p_merger *m)
{
	p_combine *c = (p_combine *)m;

	if (c->m.cur == c->a->cur)
		c->a->next(c->a);
	else {
		assert(c->m.cur == c->b->cur);
		c->b->next(c->b);
	}
	c->m.cur = c->a->cur == NULL ? (c->b->cur ? c->b->cur : NULL)
	         : c->b->cur == NULL ?  c->a->cur
	         : p_wf_dname_cmp(&c->a->cur, &c->b->cur) ? c->a->cur
	         : c->b->cur;
}

static p_merger *p_merger_new(p_merger *a, p_merger *b)
{
	p_combine *c = malloc(sizeof(p_combine));

	assert(c != NULL);
	c->a = a;
	c->b = b;
	c->m.cur = a->cur == NULL ? (b->cur ? b->cur : NULL)
	         : b->cur == NULL ? a->cur
	         : p_wf_dname_cmp(&a->cur, &b->cur) ? a->cur : b->cur;
	c->m.next = p_merger_next;
	return &c->m;
}

typedef struct p_partial p_partial;
struct p_partial {
	p_merger       m;
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
	p_partial     *prev;
};

static void p_partial_merger_next(p_merger *m)
{
	p_partial *p = (p_partial *)m;

	assert(m->cur == (wf_dname_ref *)p->cur);
	p->cur = m->cur->dname + m->cur->dname_sz + m->cur->txt_sz;
	if (p->cur >= p->end) {
		munmap(p->mem, p->end - p->mem);
		p->cur = p->mem = p->end = NULL;
		m->cur = NULL;
		close(p->tmpfd);
		unlink(p->tmpfn);
	}
	m->cur = (wf_dname_ref *)p->cur;
	if (p->cur - p->mem > pagesize) {
		size_t n = (p->cur - p->mem) /pagesize;

		munmap(p->mem, n * pagesize);
		p->mem += n * pagesize;
	}
}

static p_partial *p_partial_new()
{
	p_partial *p;

	if (!(p = malloc(sizeof(p_partial))))
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


static void p_partial_mktmpfn(p_partial *p, const char *fn)
{
	size_t   cnt = 0;
	p_partial *c = p->prev;
	const char *s = strrchr(fn, '/');

	if (!s)
		s = fn;
	while (c) {
		c = c->prev;
		cnt += 1;
	}
	snprintf( p->tmpfn, sizeof(p->tmpfn)
	        , "/tmp/sort-zone-%s-%.2zu-XXXXXX", s, cnt);
}

static void *p_partial_sort_save_(void *arg)
{
	p_partial *p = (p_partial *)arg;
	wf_dname_ref **ref;

	p->mem_sz = p->cur - p->mem;
	p->n_refs = p->ref - p->refs;
	fprintf(stderr, "Sorting %zu bytes in %zu names at %zd\n"
	              , p->mem_sz, p->n_refs, time(NULL) - start_t);
	p_qsort(p->refs, 0, (p->ref - p->refs) - 1);
	fprintf(stderr, "Saving  %zu bytes in %zu names at %zd\n"
	              , p->mem_sz, p->n_refs, time(NULL) - start_t);
	if ((p->tmpfd = mkstemp(p->tmpfn)) < 0)
		perror("Could not create temporary partial file");

	FILE *f = fdopen(p->tmpfd, "w");
	for ( ref = p->refs; ref < p->ref; ref++) {
		if (!fwrite(*ref, sizeof(wf_dname_ref) + (*ref)->dname_sz
		                                       + (*ref)->txt_sz, 1, f))
			perror("Error writing to temporary partial file");
	}
	fclose(f);
	p->tmpfd = -1;
	free(p->mem);
	free(p->refs);
	p->mem = p->cur = p->end = NULL;
	p->refs = p->ref = p->last_ref = NULL;
	fprintf(stderr, "Saved   %zu bytes in %zu names at %zd\n"
	              , p->mem_sz, p->n_refs, time(NULL) - start_t);
	return NULL;
}

static inline void p_partial_sort_save(p_partial *p, const char *fn)
{
	p_partial_mktmpfn(p, fn);
	p_partial_sort_save_(p);
}

static inline p_partial *p_partial_next(p_partial *p, const char *fn)
{
	p_partial *n;

	if ((n = p_partial_new(p)))
		n->prev = p;

	p_partial_mktmpfn(p, fn);
	if (pthread_create( &p->lt, PTHREAD_CREATE_JOINABLE
	                  , p_partial_sort_save_, (void *)p))
		p_partial_sort_save_(p);
	return n;
}

int main(int argc, char **argv)
{
	zone_wf_iter zi_spc, *zi = NULL;
	char         outfn[4096];
	int          s;
	p_partial   *p = NULL;
	size_t       n_ps;
	p_partial   *c;
	p_merger    *ms[64], *m;
	FILE        *f;

	/* Initialize globals */
	time(&start_t);
	pagesize = sysconf(_SC_PAGESIZE) * 64;

	if (argc < 2 || argc > 3) {
		printf("usage: %s <zonefile> [ <origin> ]\n", argv[0]);
		return 1;
	}
	if (!(zi = zone_wf_iter_init(&zi_spc, argv[1], argc==3?argv[2]:""))) {
		fprintf(stderr, "Could not open zone\n");
		return EXIT_FAILURE;
	}
	if (!(p = p_partial_new())) {
		fprintf(stderr, "Memory allocation error\n");
		return EXIT_FAILURE;
	}
	while (zi) {
		ssize_t n;
		uint8_t *dname;

		if (( p->ref >= p->last_ref
		    ||  p->cur + 1024 + zi->rr_len > p->end)
		&& (!(p = p_partial_next(p, argv[1])))) {
			fprintf(stderr, "Could not create next partial\n");
			return EXIT_FAILURE;
		}
		(*p->ref)         = (void *)p->cur;
		(*p->ref)->txt_sz = zi->rr_len;
		(*p->ref)->ttl    = zi->ttl;
		dname = (*p->ref)->dname;

		for (n = (ssize_t)zi->owner.n - 2; n >= 0; n--) {
			memcpy(dname, zi->owner.l[n], zi->owner.l[n][0] + 1);
			dname += zi->owner.l[n][0] + 1;
		}
		*dname++ = 0;
		(*p->ref)->dname_sz = dname - (*p->ref)->dname;
		p->cur = dname;
		memcpy(p->cur, zi->rr, (*p->ref)->txt_sz);
		p->cur += (*p->ref)->txt_sz;
		p->ref += 1;
		zi = zone_wf_iter_next(zi);
	}
	s = snprintf(outfn, sizeof(outfn), "%s.sorted", argv[1]);
	assert(s < sizeof(outfn));
	if (!p->prev) {
		wf_dname_ref **ref;

		/* Just one part, just sort and save this single part */
		p_qsort(p->refs, 0, (p->ref - p->refs) - 1);
		f = fopen(outfn, "w");
		for (ref = p->refs; ref < p->ref; ref++) {
			fwrite( (*ref)->dname + (*ref)->dname_sz
			      , (*ref)->txt_sz, 1, f);
			putc('\n', f);
		}
		fclose(f);
		return 0;
	}
	p_partial_sort_save(p, argv[1]);

	for (n_ps = 0, c = p; c; c = c->prev) {
		pthread_join(c->lt, NULL);
		c->tmpfd = open(c->tmpfn, O_RDONLY);
		assert(c->tmpfd >= 0);
		c->cur = c->mem = mmap(NULL, c->mem_sz, PROT_READ,
		    MAP_PRIVATE, c->tmpfd, 0);
		assert(c->mem != MAP_FAILED);
		c->end = c->mem + c->mem_sz;
		c->m.cur = (wf_dname_ref *)c->cur;
		c->m.next = p_partial_merger_next;
		ms[n_ps++] = &c->m;
	}
	while (n_ps > 1) {
		size_t i, j;
		for (i = 0, j = 0; i < n_ps; i += 2, j++) {
			if (i + 1 < n_ps)
				ms[j] = p_merger_new(ms[i], ms[i + 1]);

			else	ms[j] = ms[i];
		}
		n_ps = j;
	}
	for (f = fopen(outfn, "w"), m = ms[0]; m->cur; m->next(m)) {
		fwrite(m->cur->dname + m->cur->dname_sz, m->cur->txt_sz, 1, f);
		putc('\n', f);
	}
	fclose(f);
	return 0;
}
