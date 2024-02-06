#include <stdio.h>
#include <stdlib.h>

#include "cryptMorse.h"
#include "utils_v1.h"

int main(int argc, char* argv[]) {
   char* msgCrypter = readLine();
   char* decrypter = decryptMorse(msgCrypter);
   printf("%s\n", decrypter);
   free(decrypter);
   free(msgCrypter);
   exit(0);
}