#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

#define BUFFER_SIZE 1024


int main(int argc, char* argv[]) {
    int fd[2];
    pid_t childId;
    char* buffer = (char*)malloc(sizeof(char) * BUFFER_SIZE);
    char* writeBuffer = (char*)malloc(sizeof(char) * BUFFER_SIZE);
    size_t messageLength;
    
    pipe(fd);

    childId = fork();

    if (childId == 0) {
        close(fd[0]);

        while (getline(&buffer, &messageLength, stdin)) {
            write(fd[1], buffer, messageLength);
        }

        close(fd[1]);
        exit(EXIT_SUCCESS);
    } else {
        close(fd[1]);

        while (read(fd[0], buffer, BUFFER_SIZE))
            printf("Received text: %s", buffer);

        close(fd[0]);
        wait(NULL);
    }

    return 0;
}