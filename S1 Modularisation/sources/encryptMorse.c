#include <stdio.h>
#include <stdlib.h>

#include "cryptMorse.h"
#include "utils_v1.h"

int main(int argc, char* argv[]) {
   char* msgEnClair = readLine();
   char* crypter = encryptMorse(msgEnClair);
   printf("%s\n", crypter);
   free(crypter);
   free(msgEnClair);
   exit(0);
}