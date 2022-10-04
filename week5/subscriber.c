#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <string.h>

#define BUFFER_SIZE 1024
#define MAX_NAME_LENGTH 256


int main(int argc, char* argv[]) {
    if (argc != 2) {
        perror("Please, pass the number of subscribes as argument");
        return 1;
    }

    char* name = (char*)malloc(MAX_NAME_LENGTH * sizeof(char));
    strcpy(name, argv[1]);

    printf("Subscriber %s is here..\n", name);

    int fd;

    char pipePath[] = "/tmp/ex1";

    char* buffer = (char*)malloc(sizeof(char) * BUFFER_SIZE);
    size_t messageLength;

    mkfifo(pipePath, 0666);

    while (1) {
        fd = open(pipePath, O_RDONLY);
        read(fd, buffer, BUFFER_SIZE);
        printf("%s", buffer);
        close(fd);
    }

    return 0;
}