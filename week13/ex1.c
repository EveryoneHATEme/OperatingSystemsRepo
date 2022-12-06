#include "stdio.h"
#define TYPES_AMOUNT 3
#define PROCESSES 5
#define bool int
#define true 1
#define false 0


void readVector(FILE* inputFile, int array[TYPES_AMOUNT]) {
    for (int i = 0; i < TYPES_AMOUNT; i++)
        fscanf(inputFile, "%d", array + i);
}

void readMatrix(FILE* inputFile, int matrix[PROCESSES][TYPES_AMOUNT]) {
    for (int i = 0; i < PROCESSES; i++)
        for (int j = 0; j < TYPES_AMOUNT; j++)
            fscanf(inputFile, "%d", matrix[i] + j);
}


int main() {
    char inputFilename[] = "input.txt";

    int existenceResourses[TYPES_AMOUNT];
    int avaiableResourses[TYPES_AMOUNT];
    int currentAllocation[PROCESSES][TYPES_AMOUNT];
    int requests[PROCESSES][TYPES_AMOUNT];

    bool deadlockMask[PROCESSES];
    for (int i = 0; i < PROCESSES; i++)
        deadlockMask[i] = false;

    FILE* inputFile = fopen(inputFilename, "r");
    readVector(inputFile, existenceResourses);
    readVector(inputFile, avaiableResourses);
    readMatrix(inputFile, currentAllocation);
    readMatrix(inputFile, requests);
    fclose(inputFile);

    bool run = true;
    while (run) {
        run = false;
        for (int i = 0; i < PROCESSES; i++) {
            bool canAllocate = true;
            if (!deadlockMask[i]) 
                for (int j = 0; j < TYPES_AMOUNT; j++) 
                    if (avaiableResourses[j] + currentAllocation[i][j] < requests[i][j]) {
                        canAllocate = false;
                        break;
                    }
            
            if (!deadlockMask[i] && canAllocate) {
                run = true;
                deadlockMask[i] = true;
                for (int j = 0; j < TYPES_AMOUNT; j++)
                    avaiableResourses[j] += currentAllocation[i][j];
            }
        }
    }

    for (int i = 0; i < PROCESSES; i++){
        if (!deadlockMask[i]){
            printf("Deadlock in %dth process\n", i);
            return 0;
        }
    }

    printf("No deadlock\n");

    return 0;
}