CFLAGS=-std=c11 -pedantic -Wvla -Wall -Werror -D_DEFAULT_SOURCE -g

all: encrypt decrypt encryptPolybe decryptPolybe encryptMorse decryptMorse secretAgent

# Edition de liens
encrypt: encrypt.o crypt.o utils_v1.o
	cc $(CFLAGS) -o encrypt encrypt.o crypt.o utils_v1.o

decrypt: decrypt.o crypt.o utils_v1.o
	cc $(CFLAGS) -o decrypt decrypt.o crypt.o utils_v1.o

encryptPolybe: encryptPolybe.o cryptPolybe.o utils_v1.o
	cc $(CFLAGS) -o encryptPolybe encryptPolybe.o cryptPolybe.o utils_v1.o

decryptPolybe: decryptPolybe.o cryptPolybe.o utils_v1.o
	cc $(CFLAGS) -o decryptPolybe decryptPolybe.o cryptPolybe.o utils_v1.o

encryptMorse: encryptMorse.o cryptMorse.o utils_v1.o
	cc $(CFLAGS) -o encryptMorse encryptMorse.o cryptMorse.o utils_v1.o

decryptMorse: decryptMorse.o cryptMorse.o utils_v1.o
	cc $(CFLAGS) -o decryptMorse decryptMorse.o cryptMorse.o utils_v1.o

secretAgent: secretAgent.o crypt.o cryptPolybe.o cryptMorse.o utils_v1.o
	cc $(CFLAGS) -o secretAgent secretAgent.o crypt.o cryptPolybe.o cryptMorse.o utils_v1.o 


# Compilation
encrypt.o: encrypt.c crypt.h utils_v1.h
	cc $(CFLAGS) -c encrypt.c

decrypt.o: decrypt.c crypt.h utils_v1.h
	cc $(CFLAGS) -c decrypt.c

crypt.o: crypt.c crypt.h 
	cc $(CFLAGS) -c crypt.c

encryptPolybe.o: encryptPolybe.c cryptPolybe.h utils_v1.h
	cc $(CFLAGS) -c encryptPolybe.c

decryptPolybe.o: decryptPolybe.c cryptPolybe.h utils_v1.h
	cc $(CFLAGS) -c decryptPolybe.c

cryptPolybe.o: cryptPolybe.c cryptPolybe.h 
	cc $(CFLAGS) -c cryptPolybe.c

utils_v1.o: utils_v1.c utils_v1.h
	cc $(CFLAGS) -c utils_v1.c

encryptMorse.o: encryptMorse.c cryptMorse.h utils_v1.h
	cc $(CFLAGS) -c encryptMorse.c

decryptMorse.o: decryptMorse.c cryptMorse.h utils_v1.h
	cc $(CFLAGS) -c decryptMorse.c

secretAgent.o: secretAgent.c crypt.h cryptPolybe.h cryptMorse.h utils_v1.h
	cc $(CFLAGS) -c secretAgent.c

# Nettoyage
clean: 
	rm -f *.o
	rm -f encrypt decrypt encryptPolybe decryptPolybe encryptMorse decryptMorse secretAgent
