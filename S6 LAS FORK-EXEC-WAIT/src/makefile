CFLAGS=-std=c11 -pedantic -Wall -Wvla -Werror -D_DEFAULT_SOURCE

PROGS = ex1.a ex1.b ex1.c ex1.d ex2.a ex2.b ex2.c ex2.d ex3

all: $(PROGS)

ex1.a: ex1.a.o
	gcc $(CFLAGS) -o ex1.a ex1.a.o

ex1.a.o: ex1.a.c
	gcc $(CFLAGS) -c ex1.a.c

ex1.b: ex1.b.o
	gcc $(CFLAGS) -o ex1.b ex1.b.o

ex1.b.o: ex1.b.c
	gcc $(CFLAGS) -c ex1.b.c

ex1.c: ex1.c.o
	gcc $(CFLAGS) -o ex1.c ex1.c.o

ex1.c.o: ex1.c.c
	gcc $(CFLAGS) -c ex1.c.c

ex1.d: ex1.d.o
	gcc $(CFLAGS) -o ex1.d ex1.d.o

ex1.d.o: ex1.d.c
	gcc $(CFLAGS) -c ex1.d.c

ex2.a: ex2.a.o
	gcc $(CFLAGS) -o ex2.a ex2.a.o

ex2.a.o: ex2.a.c
	gcc $(CFLAGS) -c ex2.a.c

ex2.b: ex2.b.o
	gcc $(CFLAGS) -o ex2.b ex2.b.o

ex2.b.o: ex2.b.c
	gcc $(CFLAGS) -c ex2.b.c

ex2.c: ex2.c.o
	gcc $(CFLAGS) -o ex2.c ex2.c.o

ex2.c.o: ex2.c.c
	gcc $(CFLAGS) -c ex2.c.c

ex2.d: ex2.d.o utils_v1.o
	gcc $(CFLAGS) -o ex2.d ex2.d.o utils_v1.o

ex2.d.o: ex2.d.c utils_v1.h
	gcc $(CFLAGS) -c ex2.d.c

ex3.o: ex3.c
	gcc $(CFLAGS) -c ex3.c

ex3: ex3.o utils_v1.o
	gcc $(CFLAGS) -o ex3 ex3.o utils_v1.o

clean:
	rm -f *.o
	rm -f $(PROGS)
