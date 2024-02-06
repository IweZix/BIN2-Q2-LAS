#include <stdio.h>
#include <stdlib.h>

#include "cryptPolybe.h"
#include "utils_v1.h"

int main(int argc, char* argv[]) {
   char* msgEnClair = readLine();
   char* msgCrypt = decryptPolybe(msgEnClair);
   printColor("%s\n", msgCrypt, CYAN_TEXT);
   
   free(msgCrypt);
   free(msgEnClair);
   exit(0);
}