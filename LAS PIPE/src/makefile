CFLAGS =-std=c11 -pedantic -Wall -Wvla -Werror -D_DEFAULT_SOURCE
ALL = ex1 ex2

all: $(ALL)

ex1: utils_v1.o ex1.o
	cc $(CFLAGS) -o ex1 utils_v1.o ex1.o

ex1.o: utils_v1.h ex1.c
	cc $(CFLAGS) -c ex1.c

ex2: utils_v1.o ex2.o
	cc $(CFLAGS) -o ex2 utils_v1.o ex2.o

ex2.o: utils_v1.h ex2.c
	cc $(CFLAGS) -c ex2.c

utils_v1.o: utils_v1.c utils_v1.h
	cc $(CFLAGS) -c utils_v1.c 

clean:
	rm -f *.o
	rm -f $(ALL)

# for dev purpose
clear:
	clear
