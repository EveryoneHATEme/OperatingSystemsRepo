#include <stdio.h>
#include <stdlib.h>

#define false '\0'
#define true '\1'

typedef char bool;


typedef struct ProcessInformation {
    int arrival;
    int burst;
    int completion;
    int turnAround;
    int waiting;
    int timeLeft;
    bool addedToQueue;
} ProcessInformation;


struct QueueElementStruct {
    ProcessInformation* value;
    struct QueueElementStruct* nextElement;
};


typedef struct QueueElementStruct QueueElement;


typedef struct Queue {
    QueueElement* frontElement;
    QueueElement* rearElement;
    int size;
} Queue;


Queue* createQueue() {
    Queue* queue = (Queue*)malloc(sizeof(Queue));

    queue->frontElement = NULL;
    queue->rearElement = NULL;
    queue->size = 0;

    return queue;
}


void pushQueue(Queue* queue, ProcessInformation* value) {
    QueueElement* newElement = (QueueElement*)malloc(sizeof(QueueElement));
    newElement->value = value;
    newElement->nextElement = NULL;

    if (queue->rearElement == NULL) {
        queue->frontElement = newElement;
        queue->rearElement = newElement;
    } else {
        queue->rearElement->nextElement = newElement;
        queue->rearElement = newElement;
    }
    ++queue->size;
}


ProcessInformation* popQueue(Queue* queue) {
    ProcessInformation* result = queue->frontElement->value;
    QueueElement* elementToDelete = queue->frontElement;

    queue->frontElement = queue->frontElement->nextElement;
    if (queue->size == 1) {
        queue->frontElement = NULL;
        queue->rearElement = NULL;
    }

    free(elementToDelete);
    --queue->size;

    return result;
}


bool isEmptyQueue(Queue* queue) {
    return (bool) (queue->size == 0);
}


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
    int numberOfProcesses, timeQuantum;

    printf("Number of processes: ");
    scanf("%d", &numberOfProcesses);

    printf("Time quantum: ");
    scanf("%d", &timeQuantum);

    ProcessInformation* processesArray = (ProcessInformation*)malloc(numberOfProcesses * sizeof(ProcessInformation));

    for (int i = 0; i < numberOfProcesses; ++i)
        scanf("%d", &processesArray[i].arrival);

    for (int i = 0; i < numberOfProcesses; ++i)
        scanf("%d", &processesArray[i].burst);

    for (int i = 0; i < numberOfProcesses; ++i) {
        processesArray[i].timeLeft = processesArray[i].burst;
        processesArray[i].addedToQueue = false;
    }

    sort(processesArray, numberOfProcesses);

    Queue* queue = createQueue();

    int currentTime = 0;
    int turnAroundSum = 0;
    int waitingTimeSum = 0;
    int finishedAmount = 0;
    ProcessInformation* process;
    int timePassed;
    bool hasTasks;

    while (finishedAmount < numberOfProcesses) {
        if (isEmptyQueue(queue))
            for (int i = 0; i < numberOfProcesses; ++i) {
                if (!processesArray[i].timeLeft)
                    continue;
                pushQueue(queue, processesArray + i);
                processesArray[i].addedToQueue = true;
                break;
            }

        process = popQueue(queue);
        if (process->arrival > currentTime)
            currentTime = process->arrival;

        for (int i = 0; i < numberOfProcesses; ++i) {
            if (!processesArray[i].addedToQueue && processesArray[i].arrival <= currentTime) {
                pushQueue(queue, processesArray + i);
                processesArray[i].addedToQueue = true;
            }
        }

        timePassed = (process->timeLeft >= timeQuantum) ? timeQuantum : process->timeLeft;
        process->timeLeft -= timePassed;
        currentTime += timePassed;

        if (process->timeLeft == 0) {
            process->completion = currentTime;
            process->turnAround = process->completion - process->arrival;
            process->waiting = process->turnAround - process->burst;
            turnAroundSum += process->turnAround;
            waitingTimeSum += process->waiting;
        } else
            pushQueue(queue, process);

        finishedAmount = 0;
        for (int i = 0; i < numberOfProcesses; ++i)
            finishedAmount += !processesArray[i].timeLeft ? 1 : 0;
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