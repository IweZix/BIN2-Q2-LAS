#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "crypt.h"
#include "cryptPolybe.h"
#include "cryptMorse.h"

#include "utils_v1.h"

void cryptageMenu();

void decryptageMenu();


int main(int argc, char const *argv[]) {
    
    printf("1. Cryptage\n");
    printf("2. Décryptage\n");
    printf("Votre choix (Ctrl+D pour quitter) : ");
    int choice;
    scanf("%d", &choice);

    switch (choice) {
        case 1:
            cryptageMenu();
            break;
        case 2:
            decryptageMenu();
            break;
        default:
            break;
    }

    return 0;
}

void cryptageMenu() {
    printf("\n1. ROT13\n");
    printf("2. Polybe\n");
    printf("3. Morse\n");
    printf("Votre choix (Ctrl+D pour quitter) : ");
    int choice;
    scanf("%d", &choice);

    getchar();

    printf("Entrez la phrase à crypter : ");
    char* msgEnClair = readLine();
    char* msgCrypt;

    switch (choice) {
        case 1:
            msgCrypt = encrypt(msgEnClair);
            break;
        case 2:
            msgCrypt = encryptPolybe(msgEnClair);
            break;
        case 3:
            msgCrypt = encryptMorse(msgEnClair);
            break;
        default:
            break;
    }

    printColor("%s\n", msgCrypt, CYAN_TEXT);
}



void decryptageMenu() {
    printf("\n1. ROT13");
    printf("2. Polybe");
    printf("3. Morse");
    printf("Votre choix (Ctrl+D pour quitter) : ");
    int choice;
    scanf("%d", &choice);

    getchar();

    printf("Entrez la phrase à décrypter : ");
    char* MsgCrypter = readLine();
    char* msgEnClair;

    switch (choice) {
        case 1:
            msgEnClair = decrypt(MsgCrypter);
            break;
        case 2:
            msgEnClair = decryptPolybe(MsgCrypter);
            break;
        case 3:
            msgEnClair = decryptMorse(MsgCrypter);
            break;
        default:
            break;
    }

    printColor("%s\n", msgEnClair, CYAN_TEXT);
}

