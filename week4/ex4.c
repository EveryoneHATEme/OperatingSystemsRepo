#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define MAX_COMMAND_SIZE 2048


int main() {
    char* command = NULL;
    size_t length;
    int status;

    while (1) {
        printf("Print your command: ");
        getline(&command, &length, stdin);
        if (fork() == 0) {
            status = system(command);
            printf("\nCommand executed with code %d\n\n", status);
            exit(EXIT_SUCCESS);
        }
    }

    free(command);

    return 0;
}