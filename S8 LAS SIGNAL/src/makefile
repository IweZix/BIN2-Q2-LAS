CFLAGS=-std=c11 -pedantic -Wall -Wvla -Werror -D_DEFAULT_SOURCE

ALL= ex1.a ex1.b ex1.c timer

all: $(ALL)

ex1.a: ex1.a.o utils_v1.o
	gcc $(CFLAGS) -o ex1.a ex1.a.o utils_v1.o

ex1.a.o: ex1.a.c utils_v1.h
	gcc $(CFLAGS) -c ex1.a.c

ex1.b: ex1.b.o utils_v1.o
	gcc $(CFLAGS) -o ex1.b ex1.b.o utils_v1.o

ex1.b.o: ex1.b.c utils_v1.h
	gcc $(CFLAGS) -c ex1.b.c

ex1.c: ex1.c.o utils_v1.o
	gcc $(CFLAGS) -o ex1.c ex1.c.o utils_v1.o

ex1.c.o: ex1.c.c utils_v1.h
	gcc $(CFLAGS) -c ex1.c.c

utils_v1.o: utils_v1.c utils_v1.h
	gcc $(CFLAGS) -c utils_v1.c

timer: timer.o utils_v1.o
	gcc $(CFLAGS) -o timer timer.o utils_v1.o

timer.o: timer.c utils_v1.h
	gcc $(CFLAGS) -c timer.c

clean:
	rm -f *.o
	rm -f $(ALL)