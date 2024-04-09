#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <fcntl.h>
#include <unistd.h>

#include "messages.h"
#include "utils_v1.h"

#define BACKLOG 5

typedef struct Player {
    char pseudo[100];
    int sockfd;
} Player;

/**
 * Inscription après 15 secondes annulée
*/
void sigalarm_handler() {
    printf("Inscription non complétée");
    exit(1);
}

int initSocketServer() {
    int socketfd = ssocket();
    sbind(SERVER_PORT, socketfd);
    slisten(socketfd, BACKLOG);
    return socketfd;
}

/**
 * Programme de jeux pierre-papier-ciseaux
*/
int main(int argc, char const *argv[]) {
    ssigaction(SIGALRM, sigalarm_handler);

    StructMessage msg;
    Player tabPlayer[2];
    int nbPlayer = 0;

    struct pollfd fds[2];

    int sockfd = initSocketServer();
    printf("Le serveur tourne sur le port %d\n", SERVER_PORT);

    /**
     * PSEUDO TRT
    */
    alarm(15);
    while (nbPlayer < 2) {

       int newsockfd = saccept(sockfd);

       // lecture du pseudo
       sread(newsockfd, &msg, sizeof(msg));

       printf("Inscription demandée par le joueur : %s\n", msg.messageText);

       // remplissage de la réponse pour le renvoie 
       msg.code = INSCRIPTION_OK;

       // encodage du joueur
       if (nbPlayer < 2) {
        strcpy(tabPlayer[nbPlayer].pseudo, msg.messageText);
        tabPlayer[nbPlayer].sockfd = newsockfd;

        fds[nbPlayer].fd = newsockfd;
        fds[nbPlayer].events = POLLIN;

        nbPlayer++;
        swrite(newsockfd, &msg, sizeof(msg));
        printf("Nb Inscription : %d\n", nbPlayer);
       } else {
           msg.code = INSCRIPTION_KO;
       }
    }
    alarm(0);

    /**
     * JEU TRT
    */
    bool end = false;
    char joueur1;
    char joueur2;

    while (!end) {
        spoll(fds, nbPlayer, 0);

        for (int i = 0; i < nbPlayer; i++) {
            if (fds[i].revents & POLLIN) {
                sread(fds[i].fd, &msg, sizeof(msg));
                printf("Joueur %s a joué %s\n", tabPlayer[i].pseudo, msg.messageText);

                if (i == 0) {
                    joueur1 = msg.messageText[0];
                } else {
                    joueur2 = msg.messageText[0];
                }
            }

            if (joueur1 != '\0' && joueur2 != '\0') {
                if (joueur1 == joueur2) {
                    msg.code = GAME_EQUAL;
                    swrite(tabPlayer[0].sockfd, &msg, sizeof(msg));
                    swrite(tabPlayer[1].sockfd, &msg, sizeof(msg));
                } else if ((joueur1 == 'R' && joueur2 == 'C') || (joueur1 == 'P' && joueur2 == 'R') || (joueur1 == 'C' && joueur2 == 'P')) {
                    msg.code = GAME_WIN;
                    swrite(tabPlayer[0].sockfd, &msg, sizeof(msg));
                    msg.code = GAME_LOOSE;
                    swrite(tabPlayer[1].sockfd, &msg, sizeof(msg));
                } else {
                    msg.code = GAME_LOOSE;
                    swrite(tabPlayer[0].sockfd, &msg, sizeof(msg));
                    msg.code = GAME_WIN;
                    swrite(tabPlayer[1].sockfd, &msg, sizeof(msg));
                }

                end = true;
            }
        }
    }

    
    
    sclose(sockfd);
    return 0;
}
