#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "cryptPolybe.h"
#include "utils_v1.h"

static char square[8][8] = {
  {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H'},
  {'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P'},
  {'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X'},
  {'Y', 'Z', '0', '1', '2', '3', '4', '5'},
  {'6', '7', '8', '9', ' ', '!', '"', '#'},
  {'$', '%', '&', '\'', '(', ')', '*', '+'},
  {',', '-', '.', '/', ':', ';', '<', '='},
  {'>', '?', '@', '[', '\\', ']', '^', '_'}
};

// ABC -> 11 12 13
char* encryptPolybe(char* msg) {
  int i, j, k;

  char* result = (char*)malloc((strlen(msg) * 2 + 1) * sizeof(char));
  if (result == NULL) {
    printf("malloc failed\n"); 
    exit(1);
  }

  for (i = 0; i < strlen(msg); i++) {
    for (j = 0; j < 8; j++) {
      for (k = 0; k < 8; k++) {
        if (msg[i] == square[j][k]) {
          result[i * 2] = j + '1';
          result[i * 2 + 1] = k + '1';
        }
      }
    }
  }
  result[i * 2] = '\0';
  return result;
}

// 111213 -> ABC
char* decryptPolybe(char* msg) {
  int i, j, k;

  char* result = (char*)malloc((strlen(msg) / 2 + 1) * sizeof(char));
  if (result == NULL) {
    printf("malloc failed\n"); 
    exit(1);
  }

  for (i = 0; i < strlen(msg); i += 2) {
    j = msg[i] - '1';
    k = msg[i + 1] - '1';
    result[i / 2] = square[j][k];
  }
  result[i / 2] = '\0';
  return result;
}

