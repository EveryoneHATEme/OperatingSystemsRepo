#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

#define SLEEP_DURATION 5


int isNumber(char string[]) {
    for (int i = 0; i < strlen(string); ++i) {
        if (string[i] < '0' || string[i] > '9')
            return 0;
    }
    return 1;
}


int main(int argc, char* argv[]) {
    if (argc != 2) {
        printf("Wrong number of arguments\n");
        return 1;
    }
    
    if (!isNumber(argv[1])) {
        printf("Argument should be integer\n");
        return 1;
    }

    int n = atoi(argv[1]);

    for (int i = 0; i < n; ++i) {
        if (fork() == 0) {
            sleep(SLEEP_DURATION);
            exit(EXIT_SUCCESS);
        }
    }

    int status;
    wait(&status);

    return 0;
}