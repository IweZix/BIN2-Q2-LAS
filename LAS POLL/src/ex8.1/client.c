#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <fcntl.h>

#include "messages.h"
#include "utils_v1.h"

int initSocketClient() {
    int socketfd = ssocket();
    sconnect(SERVER_IP, SERVER_PORT, socketfd);
    return socketfd;
}

int main(int argc, char const *argv[]) {
    
    int sockfd = initSocketClient();

    StructMessage msg;
    
    printf("Bievenue dans le jeux Pierre-Papier-Ciseaux - Entrez votre pseudo : \n");

    /**
     * PSEUDO
    */
    int ret = sread(0, msg.messageText, MESSAGE_SIZE);
    msg.messageText[ret - 1] = '\0';
    msg.code = INSCRIPTION_REQUEST;
    // envoie le pseudo
    swrite(sockfd, &msg, sizeof(msg));
    // attend la réponse du serveur
    sread(sockfd, &msg, sizeof(msg));

    if (msg.code == INSCRIPTION_OK) {
        printf("Inscription réussie\n");
    } else if (msg.code == INSCRIPTION_KO) {
        printf("Inscription échouée\n");
        sclose(sockfd);
        exit(1);
    }

    /**
     * JEU
    */
    printf("Entrez votre choix : pierre (R), papier (P) ou ciseaux (C) : \n");
    int retGame = sread(0, msg.messageText, MESSAGE_SIZE);
    msg.messageText[retGame - 1] = '\0';
    msg.code = GAME_REQUEST;
    // envoie le choix
    swrite(sockfd, &msg, sizeof(msg));
    // attend la réponse du serveur
    sread(sockfd, &msg, sizeof(msg));

    if (msg.code == GAME_WIN) {
        printf("Vous avez gagné\n");
    } else if (msg.code == GAME_LOOSE) {
        printf("Vous avez perdu\n");
    } else if (msg.code == GAME_EQUAL) {
        printf("Egalité\n");
    }

    sclose(sockfd);

    return 0;
}
