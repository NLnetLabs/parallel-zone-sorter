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

typedef struct rr_part {
	const char *start;
	const char *end;
	size_t line_nr;
	size_t col_nr;
	const char *fn;
} rr_part;

typedef struct zone_iter {
	long        pagesize;
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
	i->pagesize = sysconf(_SC_PAGESIZE);
	i->line = i->cur = i->text = i->to_free;
	i->end = i->text + statbuf.st_size;
	i->count = 0;
	i->parts = i->parts_spc;
	i->parts_sz = sizeof(*i->parts_spc);
	i->free = 0;
	return 0;
}

static const char *p_zone_iter_get_part(zone_iter *i, size_t *olen);
static inline const char *p_zone_iter_return(zone_iter *i, size_t *olen)
{
	const char *r = i->line;

	*olen = i->cur - r;
	i->count += 1;
	i->line = ++i->cur;
	if (i->free && (r - i->to_free) > i->pagesize) {
		size_t n = (r - i->to_free) / i->pagesize;

		munmap(i->to_free, n * i->pagesize);
		i->to_free += n * i->pagesize;
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

static inline void print_rev(size_t sz, const char *name)
{
	size_t o_sz;
	const char *o_name;

	if (sz == 0)
		return;

	o_sz   = sz;
	o_name = name;

	for (;;) {
		if (*name == '.') {
			if (sz > 1) {
				print_rev(sz - 1, name + 1);
				printf(".%.*s", (int)(o_sz - sz), o_name);
			} else {
				printf("%.*s", (int)(o_sz - sz), o_name);
			}
			return;

		} else if (*name == '\\') {
			if (--sz == 0) break;
			name++;
			if (*name >= '0' || *name < '9') {
				if (--sz == 0) break;
				name++;
				if (*name >= '0' || *name < '9') {
					if (--sz == 0) break;
					name++;
					if (*name >= '0' || *name < '9') {
						if (--sz == 0) break;
						name++;
					}
				}
			}
		} else {
			if (--sz == 0) break;
			name++;
		}
	}
	printf("%.*s", (int)o_sz, o_name);
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

void debug_wf_iter(zone_wf_iter *zi)
{
	size_t i;
	char dname[1024], *d = dname, *dend = dname + sizeof(dname);

	for (i = 0; i < zi->owner.n; i++) {
		size_t j;

		for (j = 0; j < zi->owner.l[i][0]; j++) {
			unsigned char c = zi->owner.l[i][j+1];

			if (c == '.' || c == ';'
			||  c == '(' ||  c == ')' || c == '\\') {
				*d++ = '\\';
				*d++ = c;
			} else if (!(isascii(c) && isgraph(c))) {
				*d++ = '\\';
				*d++ = '0' + (c / 100);
				*d++ = '0' + (c % 100 / 10);
				*d++ = '0' + (c % 10);
			} else
				*d++ = c;
		}
		if (j)
			*d++ = '.';
	}
	*d++ = 0;
	printf( "%6d %s[-%d:]\t%.*s\n", (int)zi->ttl, dname
	      , (int)zi->origin.n
	      , (int)( zi->rr_type_or_class_type->end
	             - zi->rr_type_or_class_type->start)
	      , zi->rr_type_or_class_type->start);
}

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
	size_t n;
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

#if 0
# define DEBUG_WF_ITER(zi) debug_wf_iter(zi)
#else
# define DEBUG_WF_ITER(zi)
#endif

typedef struct wf_dname_ref {
	const char *start;
	uint32_t ttl;
	uint16_t sz;
	uint8_t orig;
	uint8_t dname[];
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
			if (*l != *r) {
				if (*l < *r)
					return 1;
				return 0;
			}
		}
		if (rsz)
			return 1;
	}
	if (*r)
		return 1;
	/* Equal names */
	return a->start < b->start ? 1 : /* a->start > b->start ? 1 : 0 */ 0;
}

typedef struct p_qsort_args {
	wf_dname_ref **arr;
	uint64_t left;
	uint64_t right;
} p_qsort_args;
static void p_qsort(wf_dname_ref **arr, uint64_t left, uint64_t right);
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
static void p_qsort(wf_dname_ref **arr, uint64_t left, uint64_t right)
{
	uint64_t i, last;
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

int main(int argc, char **argv)
{
	zone_wf_iter zi_spc, *zi;
	uint8_t        *mem = NULL;
	uint8_t        *end = NULL;
	uint8_t        *cur = NULL;
	wf_dname_ref **refs = NULL, **ref, **r;
	uint8_t    *ref_mem = NULL;
	uint8_t    *ref_end = NULL;
	uint8_t    *ref_cur = NULL;
	time_t          now = time(NULL);
	size_t     pagesize = 0;
	char          outfn[4096];
	int           s, fd;
	uint8_t        *out = NULL;
	uint8_t    *out_end = NULL;

	if (argc < 2 || argc > 3) {
		printf("usage: %s <zonefile> [ <origin> ]\n", argv[0]);
		return 1;
	}
	if ((zi = zone_wf_iter_init(&zi_spc, argv[1], argc == 3 ? argv[2] : ""))) {
		cur = mem = mmap( NULL, (zi->zi.end - zi->zi.text) * 2 
		                , (PROT_READ|PROT_WRITE)
			        , (MAP_PRIVATE|MAP_ANONYMOUS), -1, 0);
		end = mem + (zi->zi.end - zi->zi.text) * 2;
		assert(mem != MAP_FAILED);
		ref = refs = mmap( NULL, (zi->zi.end - zi->zi.text) / 4
		                 , (PROT_READ|PROT_WRITE)
		                 , (MAP_PRIVATE|MAP_ANONYMOUS), -1, 0);
		ref_mem = (void *)refs;
		ref_end = ref_mem + ((zi->zi.end - zi->zi.text) / 4);
		assert(refs != MAP_FAILED);
		pagesize = zi->zi.pagesize;
	} else
		return 1;
	while (zi) {
		ssize_t n;
		uint8_t *dname;

		DEBUG_WF_ITER(zi);

		(*ref)        = (void *)cur;
		/*
		(*ref)->start =  zi->rr_type_or_class_type->start;
		(*ref)->sz    =  zi->rr_len
		              - (zi->rr_type_or_class_type->start - zi->rr);
		*/
		(*ref)->start =  zi->rr;
		(*ref)->sz    =  zi->rr_len;
		(*ref)->ttl   =  zi->ttl;
		dname = (*ref)->dname;

		for (n = (ssize_t)zi->owner.n - 2; n >= 0; n--) {
			memcpy(dname, zi->owner.l[n], zi->owner.l[n][0] + 1);
			dname += zi->owner.l[n][0] + 1;
		}
		*dname++ = 0;
		cur = dname;
		ref += 1;
		zi = zone_wf_iter_next(zi);
	}
	uint8_t *to_free = mem + (cur - mem) / pagesize * pagesize;
	if (to_free < cur) to_free += pagesize;
	assert(to_free > cur);
	if (to_free < end) {
		fprintf(stderr, "Freeing %zu/%zu bytes from wf_dname_ref mem\n"
		              , (size_t)(end - to_free), (size_t)(end - mem));
		munmap(to_free, end - to_free);
	}
	ref_cur = (void *)ref;
	to_free = ref_mem + (ref_cur - ref_mem) / pagesize * pagesize;
	if (to_free < ref_cur) to_free += pagesize;
	assert(to_free > ref_cur);
	if (to_free < ref_end) {
		fprintf(stderr, "Freeing %zu/%zu bytes from wf_dname_ref refs\n"
		              , (size_t)(ref_end - to_free)
			      , (size_t)(ref_end - ref_mem));
		munmap(to_free, ref_end - to_free);
	}
#if 0
	fprintf(stderr, "Freeing original zone at %d\n"
	       , (int)(time(NULL) - now));
	munmap(zi_spc.zi.to_free, (zi_spc.zi.end - zi_spc.zi.to_free));
	fprintf(stderr, "Start sorting %zu RRs at %d\n", (size_t)(ref - refs)
	       , (int)(time(NULL) - now));
	p_qsort(refs, 0, (ref - refs) - 1);
#else
	fprintf(stderr, "Start sorting %zu RRs at %d\n", (size_t)(ref - refs)
	       , (int)(time(NULL) - now));
	p_qsort(refs, 0, (ref - refs) - 1);
	fprintf(stderr, "Saving zone at %d\n", (int)(time(NULL) - now));

	s = snprintf(outfn, sizeof(outfn), "%s.sorted", argv[1]);
	assert(s < sizeof(outfn));
	if ((fd = open(outfn, O_CREAT|O_RDWR|O_TRUNC|O_LARGEFILE, 0644)) < 0)
		perror("Could not open sorted output file");
	if (ftruncate64(fd, (zi_spc.zi.end - zi_spc.zi.text)) < 0)
		perror("Growing output file");
	fprintf(stderr, "Truncating done at %d\n", (int)(time(NULL) - now));
/*
	lseek64(fd, (zi_spc.zi.end - zi_spc.zi.text), SEEK_SET);
	if (write(fd, "", 1) < 0)
		perror("Writing to output file");
	lseek64(fd, 0, SEEK_SET);
	*/
	to_free = cur = out = mmap(NULL, (zi_spc.zi.end - zi_spc.zi.text)
	                               , PROT_WRITE
	                               , MAP_SHARED, fd, 0);
	assert(out != NULL && out != MAP_FAILED);
	out_end = out + (zi_spc.zi.end - zi_spc.zi.text);
	s = 0;
	for (r = refs; r < ref; r++) {
		memcpy(cur, (*r)->start, (*r)->sz);
		cur += (*r)->sz;
		*cur++ = '\n';
		if ((cur - to_free) > pagesize) {
			size_t n = (cur - to_free) / pagesize;

			munmap(to_free, n * pagesize);
			to_free += n * pagesize;
		}
		if ((to_free - out) * 100 / (out_end - out) > s) {
			s = (to_free - out) * 100 / (out_end - out);
			fprintf(stderr, "Savine %d%% done at %d\n", s, (int)(time(NULL) - now));
		}
	}
	if (ftruncate64(fd, cur - out))
		perror("Truncating output file");
	close(fd);
	/*
	for (r = refs; r < ref; r++) {
		printf("%.*s\n", (int)(*r)->sz, (*r)->start);
	}
	*/
#endif
	fprintf(stderr, "Done at %d\n", (int)(time(NULL) - now));
	return 0;
}
