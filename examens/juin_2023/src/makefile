CC=gcc

CCFLAGS=-D_DEFAULT_SOURCE -D_XOPEN_SOURCE -D_BSD_SOURCE -std=c11 -pedantic -Wvla -Wall -Werror

ALL= pipes countingsort

all: $(ALL)

pipes: pipes.o utils_v2.o
	$(CC) $(CCFLAGS) -o pipes pipes.o utils_v2.o
pipes.o: pipes.c
	$(CC) $(CCFLAGS) -c pipes.c

countingsort: countingsort.o utils_v2.o
	$(CC) $(CCFLAGS) -o countingsort countingsort.o utils_v2.o
countingsort.o: countingsort.c
	$(CC) $(CCFLAGS) -c countingsort.c

utils_v2.o: utils_v2.c utils_v2.h
	$(CC) $(CCFLAGS) -c utils_v2.c

clean:
	rm -f *.o
	rm -f $(ALL)	
	clear