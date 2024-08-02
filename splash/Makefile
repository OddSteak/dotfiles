CC=gcc
CFLAGS=-Wall -W -Werror -pedantic -ansi -std=c11

install: splash.c
	$(CC) $(CFLAGS) -o builds/splash splash.c
	cp builds/splash ~/bin/splash
	~/bin/splash

splash: splash.c
	$(CC) $(CFLAGS) -o builds/splash splash.c

clean: splash.c
	rm builds/splash

