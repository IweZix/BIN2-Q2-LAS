CFLAGS=-std=c11 -pedantic -Wall -Wvla -Werror -D_DEFAULT_SOURCE 

ALL= ex1_dashboard ex1_radar famille1 famille2 distributeur ecran admin1 client serveur admin2

all: $(ALL)

ex1_dashboard: ex1_dashboard.c utils_v2.o ex1.h
	gcc $(CFLAGS) -o ex1_dashboard ex1_dashboard.c utils_v2.o

ex1_radar: ex1_radar.c utils_v2.o ex1.h
	gcc $(CFLAGS) -o ex1_radar ex1_radar.c utils_v2.o

famille1: famille1.c utils_v2.o
	gcc $(CFLAGS) -o famille1 famille1.c utils_v2.o

famille2: famille2.c utils_v2.o
	gcc $(CFLAGS) -o famille2 famille2.c utils_v2.o

distributeur: distributeur.c utils_v2.o ex3.h
	gcc $(CFLAGS) -o distributeur distributeur.c utils_v2.o

ecran: ecran.c utils_v2.o ex3.h
	gcc $(CFLAGS) -o ecran ecran.c utils_v2.o

admin1: admin1.c utils_v2.o ex3.h
	gcc $(CFLAGS) -o admin1 admin1.c utils_v2.o

client: client.c utils_v2.o ex4.h
	gcc $(CFLAGS) -o client client.c utils_v2.o

serveur: serveur.c utils_v2.o ex4.h
	gcc $(CFLAGS) -o serveur serveur.c utils_v2.o

admin2: admin2.c utils_v2.o ex4.h
	gcc $(CFLAGS) -o admin2 admin2.c utils_v2.o

utils_v2.o: utils_v2.c utils_v2.h
	gcc $(CFLAGS) -c utils_v2.c

clean:
	rm -f *.o
	rm -f $(ALL)