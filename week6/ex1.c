#include <stdio.h>
#include <stdlib.h>


typedef struct ProcessInformation {
    int arrival;
    int burst;
    int completion;
    int turnAround;
    int waiting;
} ProcessInformation;


void sort(ProcessInformation* array, size_t size) {
    // selection sort

    int minIndex;
    ProcessInformation temp;

    for (int i = 0; i < size - 1; ++i) {
        minIndex = i;
        for (int j = i + 1; j < size; ++j) {
            if (array[j].arrival < array[minIndex].arrival)
                minIndex = j;
        }
        if (minIndex != i) {
            temp = array[minIndex];
            array[minIndex] = array[i];
            array[i] = temp;
        }
    }
}


int main() {
    int numberOfProcesses;
    scanf("%d", &numberOfProcesses);

    ProcessInformation* processes = (ProcessInformation*)malloc(numberOfProcesses * sizeof(ProcessInformation));

    for (int i = 0; i < numberOfProcesses; ++i)
        scanf("%d", &processes[i].arrival);

    for (int i = 0; i < numberOfProcesses; ++i)
        scanf("%d", &processes[i].burst);
    
    sort(processes, numberOfProcesses);

    int currentTime = 0;
    int turnAroundSum = 0;
    int waitingTimeSum = 0;
    ProcessInformation* process;

    for (int i = 0; i < numberOfProcesses; ++i) {
        process = processes + i;
        if (process->arrival > currentTime) 
            currentTime += process->arrival - currentTime;

        process->completion = currentTime + process->burst;
        process->turnAround = process->completion - process->arrival;
        process->waiting = process->turnAround - process->burst;

        currentTime += process->burst;
        turnAroundSum += process->turnAround;
        waitingTimeSum += process->waiting;
    }

    for (int i = 0; i < numberOfProcesses; ++i) {
        printf("arrival: %d\tburst: %d\t completion: %d\t turn_around: %d\t waiting: %d\n", processes[i].arrival,
                                                                                            processes[i].burst,
                                                                                            processes[i].completion,
                                                                                            processes[i].turnAround,
                                                                                            processes[i].waiting);
    }

    printf("average turnaround: %f, average waiting: %f\n", (float)turnAroundSum / (float)numberOfProcesses, (float)waitingTimeSum / (float)numberOfProcesses);

    return 0;
}
