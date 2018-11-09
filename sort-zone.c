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
	for (labels->n = 0; len; labels->n++) {
		uint8_t *pq = labels->l[labels->n], *q = pq + 1;

		while (len && (q - pq < 64)) {
			if (*dname == '.') {
				*pq = (q - pq) - 1;
				dname++; len--;
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
	}
	return 1;
}

typedef struct zone_wf_iter {
	zone_iter   zi;

	size_t      rr_len;
	const char *rr;

	wf_labels   origin;
	wf_labels   owner;
	uint32_t    ttl;
	size_t      nth;
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

static zone_wf_iter *p_zone_wf_iter_process_rr(zone_wf_iter *i)
{
	rr_part *part = i->zi.parts;
	ssize_t part_sz;
	size_t n;
	int r;

	if (part->start > i->rr) {
		/* Owner is previous owner */
		i->nth += 1;

	} else if ((part_sz = (part->end - part->start)) <= 0)
		return i; /* EOF? */

	else if (part->start[0] == '@' && part_sz == 1) {
		/* Owner is origin */
		i->nth = 0;
		p_wf_labels_cpy(&i->owner, &i->origin);
		part++;

	} else if (part->start[0] != '$') {
		/* Regular owner name */

		i->nth = 0;
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
		r = p_dname2wf(part->start, part->end-part->start, &i->owner);
		assert(r);
		return i;

	} else if (part_sz == 4 && strncasecmp(part->start, "$TTL", 4) == 0) {
		/* $TTL */
		part++;
		i->ttl = p_wf_parse_ttl(part->start, part->end - part->start);
		return i;
	} else {
		/* Other $ directive */
		return i;
	}
	/* Skip class */
	if (part->start && part->start[0] >= '0' && part->start[0] <= '9') {
		/* TTL */
		i->ttl = p_wf_parse_ttl(part->start, part->end - part->start);
		part++;
	}
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
	i->ttl = 3600;
	i->nth = 0;
	return p_zone_wf_iter_process_rr(i);
}

zone_wf_iter *zone_wf_iter_next(zone_wf_iter *i)
{
	if (!(i->rr = zone_iter_next(&i->zi, &i->rr_len)))
		return NULL;
	return p_zone_wf_iter_process_rr(i);
}

int main(int argc, char **argv)
{
	zone_wf_iter zi_spc, *zi;

	if (argc < 2 || argc > 3) {
		printf("usage: %s <zonefile> [ <origin> ]\n", argv[0]);
		return 1;
	}
	for ( zi = zone_wf_iter_init(&zi_spc, argv[1], argc == 3 ? argv[2] : "")
	    ; zi ; zi = zone_wf_iter_next(zi)) {
		; /* pass */
	}
	return 0;
}
