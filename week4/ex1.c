#include <stdio.h>
#include <time.h>
#include <unistd.h>
#include <wait.h>


int main() {
    pid_t firstChild, secondChild;
    int status;

    firstChild = fork();
    time_t firstChildStartTime = time(NULL);

    if (firstChild == 0) {
        // first child process 
        printf("first child process id: %d\n", getpid());
        printf("first child execution time: %ld\n", time(NULL) - firstChildStartTime);
    } else {
        secondChild = fork();
        time_t secondChildStartTime = time(NULL);

        if (secondChild == 0) {
            // second child process
            printf("second child process id: %d\n", getpid());
            printf("second child execution time: %ld\n", time(NULL) - secondChildStartTime);
        } else {
            // parent process
            printf("parent process id: %d\n", getpid());
        }
    }

    wait(&status);
    printf("parent process execution time: %ld\n", time(NULL) - firstChildStartTime);

    return 0;
}