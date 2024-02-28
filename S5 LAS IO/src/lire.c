#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdbool.h>

#define MAX_IN 10

int main(int argc, char const *argv[]) {

    char* msg = "Enter text lines (Ctrl-D to terminate):\n";
    char buffer[MAX_IN+1];

    while (true) {
        printf("%s", msg);

        int charRead = read(0, buffer, MAX_IN);

        if (charRead == -1) {
            perror("Error reading stdin");
            exit(EXIT_FAILURE);
        }

        if (charRead == 0) {
            break;
        }

        buffer[charRead] = '\0';

        if (charRead == MAX_IN && buffer[MAX_IN-1] != '\n') {
            fprintf(stderr, "Error: line too long\n");
            while (getchar() != '\n');
        } else {
            printf("%s", buffer);
        }
    }
    

    return 0;
}
