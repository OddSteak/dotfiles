CC=gcc
CFLAGS=-Wall -W -pedantic -std=gnu11 `pkg-config --cflags --libs glib-2.0 gtk+-2.0` -lnotify


main: ./main.c
	$(CC) $(CFLAGS) -o /home/dell/bin/backdots main.c
	/home/dell/bin/backdots

