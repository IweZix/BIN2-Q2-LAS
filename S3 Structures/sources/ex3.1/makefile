CFLAGS=-std=c11 -pedantic -Wvla -Wall -Werror -D_DEFAULT_SOURCE -g

npi: npi.o utils_v1.o pile.o
	gcc $(CFLAGS) -o npi npi.o utils_v1.o pile.o

npi.o: pile.h npi.c
	gcc $(CFLAGS) -c npi.c

pile.o: pile.h pile.c
	gcc $(CFLAGS) -c pile.c

utils_v1.o: utils_v1.c utils_v1.h
	gcc $(CFLAGS) -c utils_v1.c

clean :
	rm *.o
	rm npi