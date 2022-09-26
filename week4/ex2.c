#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

#define VECTOR_SIZE 120


int dotProduct(int first[VECTOR_SIZE], int second[VECTOR_SIZE], int from, int to);


int main() {
    int uVector[VECTOR_SIZE];
    int vVector[VECTOR_SIZE];

    for (int i = 0; i < VECTOR_SIZE; ++i) {
        uVector[i] = rand() % 100;
        vVector[i] = rand() % 100;
    }

    int n;
    scanf("%d", &n);
    int valuesPerProcess = VECTOR_SIZE / n;

    int result = 0;

    FILE* tempFilePointer = fopen("temp.txt", "w");
    if (tempFilePointer == NULL) {
        printf("Couldn't open the file\n");
        return 1;
    }

    for (int i = 0; i < n; ++i) {
        if (fork() == 0) {
            result = dotProduct(uVector, vVector, i * valuesPerProcess, (i + 1) * valuesPerProcess);
            fprintf(tempFilePointer, "%d\n", result);
            exit(EXIT_SUCCESS);
        }
    }
    
    int status;
    wait(&status);

    fclose(tempFilePointer);
    tempFilePointer = fopen("temp.txt", "r");

    int buffer;
    for (int i = 0; i < n; ++i) {
        fscanf(tempFilePointer, "%d\n", &buffer);
        result += buffer;
    }

    fclose(tempFilePointer);

    printf("%d\n", result);

    return 0;
}


int dotProduct(int first[VECTOR_SIZE], int second[VECTOR_SIZE], int from, int to) {
    int result = 0;
    for (int i = from; i < to; ++i) {
        result += first[i] * second[i];
    }
    return result;
}