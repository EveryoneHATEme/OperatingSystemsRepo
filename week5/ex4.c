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


int getNumberToCheck(int targetNumber) {
    static int nextNumberToCheck = 1;
    if (nextNumberToCheck > targetNumber) {
        return -1;
    } else {
        return nextNumberToCheck++;
    }
}


int incrementPrimes() {
    static int primesFound = 0;
    return primesFound++;
}


typedef struct primeCounterRequest {
    int targetNumber;
    pthread_mutex_t* lock;
} primeCounterRequest;


void* checkPrimes(void* arg) {
    primeCounterRequest* request = (primeCounterRequest*)arg;

    int currentNumber;
    while (1) {
        pthread_mutex_lock(request->lock);
        currentNumber = getNumberToCheck(request->targetNumber);
        pthread_mutex_unlock(request->lock);

        if (currentNumber == -1)
            break;

        if (isPrime(currentNumber)) {
            pthread_mutex_lock(request->lock);
            incrementPrimes();
            pthread_mutex_unlock(request->lock);
        }
    }
}


int main(int argc, char* argv[]) {
    int targetNumber = atoi(argv[1]);
    int threadsAmount = atoi(argv[2]);

    pthread_t* threadArray = (pthread_t*)malloc(threadsAmount * sizeof(pthread_t));
    primeCounterRequest* requestArray = (primeCounterRequest*)malloc(threadsAmount * sizeof(primeCounterRequest));
    pthread_mutex_t mutex;
    pthread_mutex_init(&mutex, NULL);

    for (int i = 0; i < threadsAmount; i++) {
        requestArray[i].targetNumber = targetNumber;
        requestArray[i].lock = &mutex;

        pthread_create(threadArray + i, NULL, checkPrimes, requestArray + i);
    }

    for (int i = 0; i < threadsAmount; i++) {
        pthread_join(threadArray[i], NULL);
    }

    free(threadArray);
    free(requestArray);

    printf("%d\n", incrementPrimes());

    return 0;
}