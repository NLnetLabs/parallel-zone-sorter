CC=gcc

all: sort-zone rev-zone

rev-zone: rev-zone.o
	$(CC) -o $@ $<

rev-zone.o: rev-zone.c
	$(CC) -Ofast -c $<

sort-zone: sort-zone.o
	$(CC) -o $@ $< -lpthread

sort-zone.o: sort-zone.c
	#$(CC) -g -c $<
	$(CC) -Ofast -c $<

clean:
	rm -f sort-zone sort-zone.o rev-zone rev-zone.o
