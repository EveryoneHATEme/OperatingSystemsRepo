#include <stdio.h>
#include <stdlib.h>


int argmin(int array[], int length);
int indexOf(int array[], int arrayLength, int element);


int main(int argc, char** argv) {
    if (argc < 2) {
        perror("Please, provide integer number of page frames as command line argument\n");
        return 1;
    }

    const int numberOfFrames = atoi(argv[1]);

    int pageFrames[numberOfFrames];
    int counters[numberOfFrames];

    for (int i = 0; i < numberOfFrames; ++i)
        counters[i] = 0;

    FILE* file = fopen("ex2_input2.txt", "r");

    int frameIndex;

    for (int i = 0; i < numberOfFrames && (fscanf(file, "%d", &frameIndex) != EOF); ++i)
        pageFrames[i] = frameIndex;

    int neededFrameIndex;
    int hitsCounter = 0, missCounter = 0;

    while (fscanf(file, "%d", &frameIndex) != EOF) {
        for (int i = 0; i < numberOfFrames; ++i)
            counters[i] >>= 1;

        neededFrameIndex = indexOf(pageFrames, numberOfFrames, frameIndex);
        if (neededFrameIndex != -1) {
            counters[neededFrameIndex] |= 0b10000000;
            ++hitsCounter;
        } else {
            neededFrameIndex = argmin(counters, numberOfFrames);
            pageFrames[neededFrameIndex] = frameIndex;
            counters[neededFrameIndex] = 0b10000000;
            ++missCounter;
        }
    }
    fclose(file);
    
    printf("Hit/Miss ratio: %f\n", (float)hitsCounter / (float)missCounter);
    
    return 0;
}


int argmin(int array[], int length) {
    int min = 0;

    for (int i = 1; i < length; ++i) 
        if (array[i] < array[min])
            min = i;
    
    return min;
}


int indexOf(int array[], int arrayLength, int element) {
    for (int i = 0; i < arrayLength; ++i)
        if (array[i] == element)
            return i;

    return -1;
}
