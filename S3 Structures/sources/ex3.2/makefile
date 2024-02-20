CFLAGS=-std=c11 -pedantic -Wvla -Wall -Werror -D_DEFAULT_SOURCE -g

testplaylist: testplaylist.o playlist.o track.o
	gcc $(CFLAGS) -o testplaylist testplaylist.o playlist.o track.o

testplaylist.o: testplaylist.c playlist.h track.h
	gcc $(CFLAGS) -c testplaylist.c

playlist.o: playlist.h playlist.c track.h
	gcc $(CFLAGS) -c playlist.c

track.o: track.h track.c
	gcc $(CFLAGS) -c track.c

clean :
	rm *.o
	rm testplaylist