#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

#define MAX_IN 80

int main(int argc, char const *argv[]) {

    if (argc != 3) {
        fprintf(stderr, "Usage: %s <input> <output>\n", argv[0]);
        exit(1);
    }

    int file1 = open(argv[1], O_RDWR | O_CREAT | O_TRUNC, 0777);
    int file2 = open(argv[2], O_RDWR | O_CREAT | O_TRUNC, 0777);

    if (file1 == -1) {
        perror("Error opening file 1 ");
        exit(EXIT_FAILURE);
    }

    if (file2 == -1) {
        perror("Error opening file 2 ");
        exit(EXIT_FAILURE);
    }

    char line[MAX_IN + 1];
    ssize_t bytesRead;

    while ((bytesRead = read(STDIN_FILENO, line, MAX_IN)) > 0) {
        if (isalpha(line[0])) {
            if (isupper(line[0])) {
                write(file1, line, bytesRead);
            } else {
                write(file2, line, bytesRead);
            }
        }
    }

    close(file1);
    close(file2);

    return 0;
}
