CFLAGS=-std=c11 -pedantic -Wall -Wvla -Werror -D_DEFAULT_SOURCE

make: ex1.1 ex1.2 lireEtEcrire lire ex4

ex1.1: ex1.1.o 
	gcc $(CFLAGS) -o ex1.1 ex1.1.o

ex1.1.o: ex1.1.c
	gcc $(CFLAGS) -c ex1.1.c

ex1.2: ex1.2.o 
	gcc $(CFLAGS) -o ex1.2 ex1.2.o

ex1.2.o: ex1.2.c
	gcc $(CFLAGS) -c ex1.2.c

lireEtEcrire: lireEtEcrire.o 
	gcc $(CFLAGS) -o lireEtEcrire lireEtEcrire.o

lireEtEcrire.o: lireEtEcrire.c
	gcc $(CFLAGS) -c lireEtEcrire.c

lire: lire.o
	gcc $(CFLAGS) -o lire lire.o

lire.o: lire.c
	gcc $(CFLAGS) -c lire.c

ex4: ex4.o
	gcc $(CFLAGS) -o ex4 ex4.o

ex4.o: ex4.c
	gcc $(CFLAGS) -c ex4.c

clean:
	rm -f *.o
	rm -f ex1.1 ex1.2 lireEtEcrire lire ex4
