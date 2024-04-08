#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <fcntl.h>

#include "utils_v1.h"

#define PORT 80
#define DOMAINE_NAME "ochoquet.be"

int initSocketClient(char * serverIP) {
  // socket creation
  int sockfd = ssocket();
  // prepare socket to connect
  sconnect(serverIP, PORT, sockfd);
  // return socket file descriptor
  return sockfd;
}

int main(int argc, char const *argv[]) {
    int fd = sopen("sitemap.txt", O_RDWR, 777);
    char **tab = readFileToTable(fd);
    for (int i = 0; tab[i] != NULL; i++) {
        char* ligne = tab[i];
        char* pageName = strrchr(ligne, '/') + 1;
        
        printf("Ligne : %s Page name : %s\n", ligne, pageName);

        char *ip = (char *)malloc(17 * sizeof(char));
        if (ip == NULL) {
            perror("Error malloc\n");
            exit(1);
        }
        
        hostname_to_ip(DOMAINE_NAME, ip);
        printf("IP: %s\n", ip);
        int scoket = initSocketClient(ip);

        // printf("IP: %s\n", ip);
        printf("Socket: %d\n", scoket);
        
        char *requete = (char *)malloc(1000 * sizeof(char));
        if (requete == NULL) {
            perror("Error malloc\n");
            exit(1);
        }
        sprintf(requete, "GET %s HTTP/1.0\r\nHost: %s\r\n\r\n", ligne, DOMAINE_NAME);
        
        swrite(scoket, requete, strlen(requete));

        char *response = (char *)malloc(1000 * sizeof(char));
        if (response == NULL) {
            perror("Error malloc\n");
            exit(1);
        }

        sread(scoket, response, 1000);

        int fd = sopen(pageName, O_RDWR | O_CREAT, 777);
        swrite(fd, response, strlen(response));
        sclose(fd);

        sclose(scoket);

        free(ip);

        free(requete);

        free(response);
    }

    close(fd);

    return 0;
}
