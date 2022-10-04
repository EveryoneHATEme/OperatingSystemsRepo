#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define THREAD_AMOUNT 10


struct Thread {
    pthread_t id;
    int i;
    char message[256];
};


void* printThreadMessage(void* arg) {
    struct Thread* thread = (struct Thread*)arg;
    printf("Thread with id: %ld, and message: \"%s\"\n", thread->id, thread->message);
}


struct Thread* createThread() {
    static int i = 0;

    struct Thread* newThread = (struct Thread*)malloc(sizeof(struct Thread));
    newThread->i = i++;
    sprintf(newThread->message, "Hello from thread %d", newThread->i);
    
    pthread_create(&newThread->id, NULL, printThreadMessage, newThread);
    printf("Thread %d is created\n", newThread->i);

    return newThread; 
}


struct Thread* createAndJoinThread() {
    struct Thread* thread = createThread();
    pthread_join(thread->id, NULL);

    return thread;
}


int main() {
    printf("Executing without strict ordering...\n");

    struct Thread* threadArray[THREAD_AMOUNT];

    for (int i = 0; i < THREAD_AMOUNT; ++i)
        threadArray[i] = createThread();

    for (int i = 0; i < THREAD_AMOUNT; ++i)
        pthread_join(threadArray[i]->id, NULL);

    for (int i = 0; i < THREAD_AMOUNT; ++i)
        free(threadArray[i]);

    printf("\nExecuting with strict ordering...\n");

    for (int i = 0; i < THREAD_AMOUNT; ++i)
        threadArray[i] = createAndJoinThread();

    for (int i = 0; i < THREAD_AMOUNT; ++i)
        free(threadArray[i]);

    return 0;
}
