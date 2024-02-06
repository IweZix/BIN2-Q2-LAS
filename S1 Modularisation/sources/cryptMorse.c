#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "cryptMorse.h"
#include "utils_v1.h"

#define MORSE_USAGE 65


char* morse[] = {
  "._", "_...", "_._","_..",".",".._.","__.","....","..",".___","_._","._..","__","_.","___",".__.","__._","._.","...","__",".._","..._",".__","_.._","_.__","__..",
};




// ABC -> ._ _... _._.
char* encryptMorse(char* msg) {

  char* result = (char*)malloc((strlen(msg) * 2 + 1) * sizeof(char));
  if (result == NULL) {
    printf("malloc failed\n"); 
    exit(1);
  }

  for (int i = 0; i < strlen(msg); i++) {
    // printf("%s\n", morse[(int) msg[i] - MORSE_USAGE]);
    result = (char*) realloc(result, (strlen(result) + strlen(morse[(int) msg[i] - MORSE_USAGE]) + 1) * sizeof(char));
    strcat(result, morse[(int) msg[i] - MORSE_USAGE]);
  }
  
  return result;
}

// ._ _... _._. -> ABC
char* decryptMorse(char* msg) {

  char* result = (char*)malloc((strlen(msg) / 2 + 1) * sizeof(char));
  if (result == NULL) {
    printf("malloc failed\n"); 
    exit(1);
  }

  int j = 0;
  for (int i = 0; i < strlen(msg); i++) {
    if (msg[i] == ' ') {
      result[j] = ' ';
      j++;
    } else {
      char* morseChar = (char*)malloc(5 * sizeof(char));
      if (morseChar == NULL) {
        printf("malloc failed\n"); 
        exit(1);
      }
      int k = 0;
      while (msg[i] != ' ' && i < strlen(msg)) {
        morseChar[k] = msg[i];
        k++;
        i++;
      }
      morseChar[k] = '\0';
      for (int l = 0; l < 26; l++) {
        if (strcmp(morseChar, morse[l]) == 0) {
          result[j] = l + MORSE_USAGE;
          j++;
          break;
        }
      }
      free(morseChar);
    }
  }



  return result;
}

