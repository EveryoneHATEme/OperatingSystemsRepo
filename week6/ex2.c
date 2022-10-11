#include <stdio.h>
#include <stdlib.h>

#define true '\1'
#define false '\0'

typedef char bool;


typedef struct ProcessInformation {
    int arrival;
    int burst;
    int completion;
    int turnAround;
    int waiting;
    bool finished;
} ProcessInformation;


int main() {
    int numberOfProcesses;
    scanf("%d", &numberOfProcesses);

    ProcessInformation* processesArray = (ProcessInformation*)malloc(numberOfProcesses * sizeof(ProcessInformation));

    for (int i = 0; i < numberOfProcesses; ++i)
        scanf("%d", &processesArray[i].arrival);

    for (int i = 0; i < numberOfProcesses; ++i)
        scanf("%d", &processesArray[i].burst);

    for (int i = 0; i < numberOfProcesses; ++i)
        processesArray[i].finished = false;

    int currentTime = 0;
    int turnAroundSum = 0;
    int waitingTimeSum = 0;
    ProcessInformation* process;

    for (int counter = 0; counter < numberOfProcesses; ++counter) {
        process = NULL;
        for (int i = 0; i < numberOfProcesses; ++i) {
            if (processesArray[i].finished)
                continue;

            if (processesArray[i].arrival <= currentTime)
                if (process == NULL || processesArray[i].burst < process->burst)
                    process = processesArray + i;
        }
        
        if (process == NULL) 
            for (int i = 0; i < numberOfProcesses; ++i) {
                if (processesArray[i].finished)
                    continue;
                
                if (process == NULL) 
                    process = processesArray + i;
                else if (processesArray[i].arrival < process->arrival)
                    process = processesArray + i;
                else if (processesArray[i].arrival == process->arrival && processesArray[i].burst < process->burst)
                    process = processesArray + i;
            }
              
        if (process->arrival > currentTime) 
            currentTime += process->arrival - currentTime;

        process->completion = currentTime + process->burst;
        process->turnAround = process->completion - process->arrival;
        process->waiting = process->turnAround - process->burst;
        process->finished = true;

        currentTime += process->burst;
        turnAroundSum += process->turnAround;
        waitingTimeSum += process->waiting;
    }

    for (int i = 0; i < numberOfProcesses; ++i) {
        printf("arrival: %d\tburst: %d\t completion: %d\t turn_around: %d\t waiting: %d\n", processesArray[i].arrival,
                                                                                            processesArray[i].burst,
                                                                                            processesArray[i].completion,
                                                                                            processesArray[i].turnAround,
                                                                                            processesArray[i].waiting);
    }

    printf("average turnaround: %f, average waiting: %f\n", (float)turnAroundSum / (float)numberOfProcesses, (float)waitingTimeSum / (float)numberOfProcesses);

    return 0;
}
