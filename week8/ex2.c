#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <unistd.h>

#define ITERATIONS 10
#define TEN_MB 10 * 1024 * 1024


int main() {
    /*
        See ex2.txt for excerises 2 comments
        See ex3.txt for excerises 3 comments
    */

    char** allocatedArrays = (char**)malloc(sizeof(char*) * ITERATIONS);
    
    printf("pid: %d\n", getpid());      // print process id to understand which process from top command i should look at

    for (int i = 0; i < ITERATIONS; ++i) {
        allocatedArrays[i] = (char*)malloc(TEN_MB);
        memset(allocatedArrays[i], 0, TEN_MB);
        sleep(1);
    }

    for (int i = 0; i < ITERATIONS; ++i)
        free(allocatedArrays[i]);

    free(allocatedArrays);

    return 0;
}