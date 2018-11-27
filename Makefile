CC=gcc

sort-zone: sort-zone.c
	$(CC) -o $@ -Ofast -Wall -Wpedantic $< -lpthread

clean:
	rm -f sort-zone
