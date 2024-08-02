CC=gcc
CFLAGS=-Wall -W -pedantic -ansi -std=gnu11

main: main.c
	$(CC) $(CFLAGS) -o builds/mm main.c

install: main.c
	$(CC) $(CFLAGS) -o builds/mm main.c
	cp builds/mm ~/bin/mm

clean:
	rm ~/builds/mm

