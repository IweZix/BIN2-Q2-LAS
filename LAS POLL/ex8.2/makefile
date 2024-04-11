CC=gcc
CCFLAGS=-D_DEFAULT_SOURCE -D_XOPEN_SOURCE -D_BSD_SOURCE -std=c11 -pedantic -Wvla -Wall -Werror

all: inscription

inscription : inscription.o utils_v1.o
	$(CC) $(CCFLAGS) -o inscription inscription.o utils_v1.o

inscription.o: inscription.c utils_v1.h
	$(CC) $(CCFLAGS) -c inscription.c 

utils_v1.o: utils_v1.c utils_v1.h
	$(CC) $(CCFLAGS) -c utils_v1.c 


clean : 
	rm -f inscription
	clear
