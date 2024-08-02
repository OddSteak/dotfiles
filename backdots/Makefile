CC=gcc
CFLAGS=-Wall -W -pedantic -std=gnu11 `pkg-config --cflags --libs glib-2.0 gtk+-2.0` -lnotify

install: main.c
	$(CC) $(CFLAGS) -o builds/main main.c
	cp builds/main ~/bin/backdots
	~/bin/backdots

main: main.c
	$(CC) $(CFLAGS) -o builds/main main.c

clean: builds/main
	rm builds/main

