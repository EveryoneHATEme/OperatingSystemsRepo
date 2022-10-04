#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <string.h>

#define BUFFER_SIZE 1024


int isNumber(char string[]);


int main(int argc, char* argv[]) {
    if (argc != 2) {
        perror("Please, pass the number of subscribes as argument");
        return 1;
    }

    if (!isNumber(argv[1])) {
        perror("Argument should be an integer");
        return 1;
    }

    int numberOfSubscribers = atoi(argv[1]);

    if (numberOfSubscribers <= 0 || numberOfSubscribers >= 4) {
        perror("Number of subscribes should be between 0 and 4 (exclusively)");
        return 1;
    }

    printf("Publisher is here...\n");

    int fd;
    char pipePath[] = "/tmp/ex1";

    char* buffer = (char*)malloc(sizeof(char) * BUFFER_SIZE);
    size_t messageLength;

    mkfifo(pipePath, 0666);

    while (getline(&buffer, &messageLength, stdin)) {
        fd = open(pipePath, O_WRONLY);
        for (int i = 0; i < numberOfSubscribers; ++i) {
            write(fd, buffer, messageLength);
        }
        close(fd);
    }

    return 0;
}


int isNumber(char string[]) {
    for (int i = 0; i < strlen(string); ++i) {
        if (string[i] < '0' || string[i] > '9')
            return 0;
    }
    return 1;
}
