#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

int isPrime(int n) {
    if (n <= 1)
        return 0;
    for (int d = 2; d * d <= n; d++)
        if (n % d == 0)
            return 0;
    return 1;
}

int primesCountInInterval(int start, int finish) {
    int count = 0;
    for (int i = start; i < finish; i++)
        if (isPrime(i) != 0)
            count++;
    return count;
}

// The structure that will be passed to the threads, corresponding to an interval to count the number of primes in.
typedef struct primeCounterRequest {
    int start;
    int finish;
    int response;
} primeCounterRequest;

void* primeCounter(void* arg) {
    primeCounterRequest* request = (primeCounterRequest*)arg;

    request->response = primesCountInInterval(request->start, request->finish);
}


int main(int argc, char* argv[]) {
    int n = atoi(argv[1]);
    int threadsAmount = atoi(argv[2]);

    int segmentSize = n / threadsAmount + (n % threadsAmount == 0 ? 0 : 1);

    pthread_t* threads = malloc(threadsAmount * sizeof(pthread_t));

    primeCounterRequest* requests = malloc(threadsAmount * sizeof(primeCounterRequest));

    for (int i = 0; i < threadsAmount; ++i) {
        requests[i].start = i * segmentSize + 1;
        if (i == threadsAmount - 1)
            requests[i].finish = n - 1;
        else 
            requests[i].finish = (i + 1) * segmentSize + 1;

        pthread_create(threads + i, NULL, primeCounter, requests + i);
        // printf("%d thread created\n", i);
    }

    for (int i = 0; i < threadsAmount; ++i) {
        pthread_join(threads[i], NULL);
        // printf("%d thread finished\n", i);
    }

    int totalResult = 0;
    for (int i = 0; i < threadsAmount; ++i)
        totalResult += requests[i].response;

    free(threads);
    free(requests);

    printf("result: %d\n", totalResult);

    return 0;
}