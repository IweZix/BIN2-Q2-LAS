# Gestion de bibliothèque

CFLAGS=-std=c11 -pedantic -Wvla -Wall -Werror -D_DEFAULT_SOURCE -g

main : main.o biblio.o utils_v1.o
	gcc $(CFLAGS) -o main main.o biblio.o utils_v1.o

main.o : biblio.h main.c
	gcc $(CFLAGS) -c main.c	

biblio.o : biblio.h biblio.c utils_v1.h
	gcc $(CFLAGS) -c biblio.c

utils_v1.o: utils_v1.c utils_v1.h
	gcc $(CFLAGS) -c utils_v1.c

clean :
	rm *.o
	rm main