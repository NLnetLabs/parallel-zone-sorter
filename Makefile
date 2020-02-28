CC=gcc
#CFLAGS=-Wall -Wpedantic -Werror -pg -Ofast -DUSE_LDH_TRIE
#CFLAGS=-Wall -Wpedantic -Werror -pg -g -DUSE_LDH_TRIE
CFLAGS=-Wall -Wpedantic -Werror -Ofast
#CFLAGS=-Wall -Wpedantic -Werror -pg -g
LDFLAGS=-pg
PROGRAMS=zc rrtypes2c
SORT_ZONE_OBJS=sort-zone.o
ZONE_COUNT_OBJS=zc.o presentation.o \
	       dnsextlang.o rrtypes.o zonefile_processor.o
RRTYPES2C_OBJS=rrtypes2c.o dnsextlang.o

default: all
all: $(PROGRAMS)

.SUFFIXES: .c .o .h
.c.o:
	$(CC) $(CFLAGS) -c $< -o $@

sort-zone: $(SORT_ZONE_OBJS)
	$(CC) $(LDFLAGS) -o $@ $(SORT_ZONE_OBJS) -lpthread

zc: $(ZONE_COUNT_OBJS)
	$(CC) $(LDFLAGS) -o $@ $(ZONE_COUNT_OBJS) -lpthread

rrtypes2c: $(RRTYPES2C_OBJS)
	$(CC) $(LDFLAGS) -o $@ $(RRTYPES2C_OBJS)

clean:
	rm -f $(PROGRAMS) $(SORT_ZONE_OBJS) $(ZONE_COUNT_OBJS) $(RRTYPES2C_OBJS)

presentation.o: presentation.c presentation.h
zc.o: zc.c \
	zonefile_processor.c zonefile_processor.h \
	presentation.c presentation.h \
	dnsextlang.c dnsextlang.h \
	return_status.h mem_parser.h
rrtypes2c.o: rrtypes2c.c dnsextlang.h
