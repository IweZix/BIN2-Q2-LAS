#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>

#include "utils_v1.h"

#define MAX 100
#define shebang "#!/bin/bash\n"

int main(int argc, char const *argv[]) {

    // Saisir au clavier le nom du script à exécuter
    char script[MAX];
    int bytesRead;
    bytesRead = read(0, script, MAX);

    if (bytesRead == -1 || bytesRead == 0) {
        perror("read");
        exit(1);
    }

    script[bytesRead] = '\0';
    script[bytesRead - 1] = '\0';
    strcat(script, ".sh");

    // créer un fichier avec le nom du script
    int file = open(script, O_CREAT | O_WRONLY | O_TRUNC, 0700);
    
    if (file == -1) {
        perror("ERROR: open failed\n");
        exit(1);
    }

    pid_t pid = fork();
    if (pid == -1) {
        perror("ERROR: fork failed\n");
        return 1;
    }

    if (pid == 0) {
        // exécuter un ls -l sur le script
        printf("********** ls -l **********\n");
        int e1 = execl("/bin/ls", "ls", "-l", script, NULL);
        if (e1 == -1) {
            perror("exec");
            exit(1);
        }
    } else {
        waitpid(pid, NULL, 0);

        // écrire le shebang dans le fichier
        write(file, shebang, strlen(shebang));

        // écrire le script dans le fichier
        bytesRead = 0;
        char buffer[MAX];
        printf("Enter your script (type 'exit' to exit):\n");
        while ((bytesRead = read(0, buffer, MAX)) > 0) {
            if (bytesRead == -1 || bytesRead == 0) {
                perror("read");
                exit(1);
            }
            
            if (strncmp(buffer, "exit", 4) == 0) {
                break;
            }

            write(file, buffer, bytesRead);
        }

        // fermer le fichier
        close(file);

        // exécuter un cat sur le script && exécuter le script
        pid_t pid = fork();
        if (pid == -1) {
            perror("ERROR: fork failed\n");
            return 1;
        }

        // exécuter un cat sur le script
        if (pid == 0) {
            printf("********** cat **********\n");
            if (execlp("/bin/cat", "cat", script, NULL) == -1) {
                perror("ERROR: exec failed\n");
                return 1;
            }
        } else {
        // exécuter le script
            waitpid(pid, NULL, 0);
            
            printf("********** script **********\n");
            if (execl(script, script, NULL) == -1) {
                perror("ERROR: exec failed\n");
                return 1;
            }
        }
    }
    
    return 0;
}
