#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <unistd.h>
#include <sys/resource.h>

#define ITERATIONS 10
#define TEN_MB 10 * 1024 * 1024


int main() {
    char** allocatedArrays = (char**)malloc(sizeof(char*) * ITERATIONS);
    struct rusage output;

    for (int i = 0; i < ITERATIONS; ++i) {
        allocatedArrays[i] = (char*)malloc(TEN_MB);
        memset(allocatedArrays[i], 0, TEN_MB);
        getrusage(RUSAGE_SELF, &output);
        printf("used %ld KB of memory\n", output.ru_maxrss);
        sleep(1);
    }

    for (int i = 0; i < ITERATIONS; ++i)
        free(allocatedArrays[i]);

    free(allocatedArrays);
    return 0;
}