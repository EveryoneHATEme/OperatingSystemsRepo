#include <stdio.h>
#include <time.h>
#include <unistd.h>
#include <wait.h>
#include <stdlib.h>


int main() {
    pid_t firstChild, secondChild;
    int status;

    clock_t parentStartTime = clock();

    firstChild = fork();
    clock_t firstChildStartTime = clock();

    if (firstChild == 0) {
        // first child process 
        printf("first child process id: %d\n", getpid());
        printf("first child execution time: %ld\n", clock() - firstChildStartTime);
        exit(EXIT_SUCCESS);
    } else {
        secondChild = fork();
        clock_t secondChildStartTime = clock();

        if (secondChild == 0) {
            // second child process
            printf("second child process id: %d\n", getpid());
            printf("second child execution time: %ld\n", clock() - secondChildStartTime);
            exit(EXIT_SUCCESS);
        } else {
            // parent process
            printf("parent process id: %d\n", getpid());
        }
    }

    wait(&status);
    printf("parent process execution time: %ld\n", clock() - parentStartTime);

    return 0;
}