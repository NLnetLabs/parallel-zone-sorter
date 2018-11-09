#include <sys/mman.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <assert.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>

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

static int zone_iter_init(zone_iter *i, const char *fn)
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

static inline const char *zone_iter_next(zone_iter *i, size_t *olen)
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

int main(int argc, char **argv)
{
	zone_iter i;
	const char *ln;
	size_t len;
	size_t j = 0, k;

	const char *origin = "";
	int origin_sz = 0;
	const char *owner = "";
	int owner_sz = 0;
	unsigned int owner_fqdn = 0;
	const char *ttl = "";
	int ttl_sz = 0;

	if (argc < 2 || argc > 3) {
		printf("usage: %s <zonefile> [ <origin> ]\n", argv[0]);
		return 1;
	}
	if (argc == 3) {
		origin = argv[2];
		origin_sz = strlen(argv[2]);
	}
	if (zone_iter_init(&i, argv[1]))
		perror("Could not initialized zone iterator fpr \"com.zone\"");

	else while ((ln = zone_iter_next(&i, &len))) {
		rr_part *part = i.parts;
		ssize_t part_sz;

		/* Owner is previous owner? */
		if (part->start > ln) {
			if (owner_fqdn)
				print_rev(owner_sz, owner);
			else {
				print_rev(origin_sz, origin);
				if (origin_sz && owner_sz) printf(".");
				print_rev(owner_sz, owner);
			}

		} else if ((part_sz = (part->end - part->start)) <= 0)
			continue;

		else if (part->start[0] == '@' && part_sz == 1) {
			print_rev(origin_sz, origin);
			part++;

		} else if (part->start[0] != '$') {
			/* Owner name */
			owner = part->start;
			owner_sz = part_sz;
			owner_fqdn = owner_sz && part->end[-1] == '.';

			if (owner_fqdn)
				print_rev(owner_sz, owner);
			else {
				print_rev(origin_sz, origin);
				if (origin_sz && owner_sz) printf(".");
				print_rev(owner_sz, owner);
			}
			part++;

		} else if (part_sz == 7 && strncasecmp(part->start, "$ORIGIN", 7) == 0) {
			part++;
			origin = part->start;
			origin_sz = part->end - part->start;
			continue;
		} else if (part_sz == 4 && strncasecmp(part->start, "$TTL", 4) == 0) {
			part++;
			ttl = part->start;
			ttl_sz = part->end - part->start;
			continue;
		} else {
			continue;
		}
		if ( part->start &&
		    (part->start[0] > '9' || part->start[0] < '0') && ttl_sz)
			printf(" %.*s", ttl_sz, ttl);

		for (; part->start; part++) {
			if (part->start[0] == '@' && part->end - part->start == 1)
				printf(" %.*s", origin_sz, origin);
			else
				printf(" %.*s", (int)(part->end - part->start)
				              , part->start);
		}
		printf("\n");
		j++;
	}
	return 0;
}
