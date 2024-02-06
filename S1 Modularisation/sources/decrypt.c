#include <stdio.h>
#include <stdlib.h>

#include "crypt.h"
#include "utils_v1.h"

int main(int argc, char* argv[]) {
   char* msgCrypt = readLine();
   char* msgEnClair = decrypt(msgCrypt);
   printColor("%s\n", msgEnClair, YELLOW_TEXT);
   
   free(msgCrypt);
   free(msgEnClair);
   exit(0);
}
