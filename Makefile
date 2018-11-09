CC=gcc

all: read-com.zone

read-com.zone: read-com.zone.o
	$(CC) -o $@ $<
	strip $@

read-com.zone.o: read-com.zone.c
	$(CC) -Ofast -c $<

clean:
	rm -f read-com.zone read-com.zone.o
