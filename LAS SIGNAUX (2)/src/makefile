CFLAGS=-std=c11 -pedantic -Wall -Wvla -Werror -D_DEFAULT_SOURCE 

ALL= heartbeat pingpong

all: $(ALL)

heartbeat: heartbeat.c utils_v1.o
	gcc $(CFLAGS) -o heartbeat heartbeat.c utils_v1.o

utils_v1.o: utils_v1.c utils_v1.h
	gcc $(CFLAGS) -c utils_v1.c

pingpong: pingpong.c utils_v1.o
	gcc $(CFLAGS) -o pingpong pingpong.c utils_v1.o

clean:
	rm -f *.o
	rm -f $(ALL)