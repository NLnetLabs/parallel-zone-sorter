CC=gcc
CFLAGS=-Wall -Wpedantic -Werror -pg -Ofast -DUSE_LDH_TRIE
#CFLAGS=-Wall -Wpedantic -Werror -pg -g -DUSE_LDH_TRIE
LDFLAGS=-pg
PROGRAMS=read-zone rrtypes2c
SORT_ZONE_OBJS=sort-zone.o
READ_ZONE_OBJS=read-zone.o presentation.o dnsextlang.o rrtypes.o
RRTYPES2C_OBJS=rrtypes2c.o dnsextlang.o

default: all
all: $(PROGRAMS)

.SUFFIXES: .c .o .h
.c.o:
	$(CC) $(CFLAGS) -c $< -o $@

sort-zone: $(SORT_ZONE_OBJS)
	$(CC) $(LDFLAGS) -o $@ $(SORT_ZONE_OBJS) -lpthread

read-zone: $(READ_ZONE_OBJS)
	$(CC) $(LDFLAGS) -o $@ $(READ_ZONE_OBJS) -lpthread

rrtypes2c: $(RRTYPES2C_OBJS)
	$(CC) $(LDFLAGS) -o $@ $(RRTYPES2C_OBJS)

clean:
	rm -f $(PROGRAMS) $(SORT_ZONE_OBJS) $(READ_ZONE_OBJS) $(RRTYPES2C_OBJS)

presentation.o: presentation.c presentation.h
read-zone.o: read-zone.c \
		presentation.c presentation.h \
		dnsextlang.c dnsextlang.h \
		return_status.h parser.h
rrtypes2c.o: rrtypes2c.c dnsextlang.h
