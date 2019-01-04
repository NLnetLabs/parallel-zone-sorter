CC=gcc
CFLAGS=-Ofast -Wall -Wpedantic -Werror -pg
#CFLAGS=-Wall -Wpedantic -Werror -pg
LDFLAGS=-pg
PROGRAMS=sort-zone read-zone
SORT_ZONE_OBJS=sort-zone.o
READ_ZONE_OBJS=read-zone.o presentation.o

default: all
all: $(PROGRAMS)

.SUFFIXES: .c .o .h
.c.o:
	$(CC) $(CFLAGS) -c $< -o $@

sort-zone: $(SORT_ZONE_OBJS)
	$(CC) $(LDFLAGS) -o $@ $(SORT_ZONE_OBJS) -lpthread

read-zone: $(READ_ZONE_OBJS)
	$(CC) $(LDFLAGS) -o $@ $(READ_ZONE_OBJS)

clean:
	rm -f $(PROGRAMS) $(SORT_ZONE_OBJS) $(READ_ZONE_OBJS)

presentation.o: presentation.c presentation.h
read-zone.o: read-zone.c presentation.c presentation.h
