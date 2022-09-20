#include <stdio.h>
#include <stdlib.h>


void* addInt(const void* a, const void* b) {
    int* result = (int*)malloc(sizeof(int));
    int aInt = *(int*)a;
    int bInt = *(int*)b;

    *result = aInt + bInt;

    return result;
}

void* addDouble(const void* a, const void* b) {
    double* result = (double*)malloc(sizeof(double));
    double aDouble = *(double*)a;
    double bDouble = *(double*)b;

    *result = aDouble + bDouble;

    return result;
}


void* multiplyInt(const void* a, const void* b) {
    int* result = (int*)malloc(sizeof(int));
    int aInt = *(int*)a;
    int bInt = *(int*)b;

    *result = aInt * bInt;

    return result;
}

void* multiplyDouble(const void* a, const void* b) {
    double* result = (double*)malloc(sizeof(double));
    double aDouble = *(double*)a;
    double bDouble = *(double*)b;

    *result = aDouble * bDouble;

    return result;
}


void* meanInt(const void* a, const void* b) {
    int* result = (int*)malloc(sizeof(int));
    int aInt = *(int*)a;
    int bInt = *(int*)b;

    *result = aInt / bInt;

    return result;
}


void* meanDouble(const void* a, const void* b) {
    double* result = (double*)malloc(sizeof(double));
    double aDouble = *(double*)a;
    double bDouble = *(double*)b;

    *result = aDouble / bDouble;

    return result;
}


void* aggregate(void* base, size_t size, int n, void* initial_value, void* (*opr)(const void*, const void*)) {
    void* output;
    char countMean = 0;

    if (size == sizeof(int)) {
        int* baseInt = (int*)base;
        int* curerntValue = (int*)malloc(sizeof(int));
        *curerntValue = *(int*)initial_value;
        int* newValue;

        if (*opr == meanInt) {
            opr = &addInt;
            countMean = 1;
        }

        for (int i = 0; i < n; ++i) {
            newValue = (int*)opr(curerntValue, baseInt + i);
            free(curerntValue);
            curerntValue = newValue;
        }

        if (countMean) 
            *curerntValue /= n;

        output = (void*)curerntValue;
    } else {
        double* baseInt = (double*)base;
        double* curerntValue = (double*)malloc(sizeof(double));
        *curerntValue = *(double*)initial_value;
        double* newValue;

        if (*opr == meanDouble) {
            opr = &addDouble;
            countMean = 1;
        }

        for (int i = 0; i < n; ++i) {
            newValue = (double*)opr(curerntValue, baseInt + i);
            free(curerntValue);
            curerntValue = newValue;
        }

        if (countMean) 
            *curerntValue /= (double)n;

        output = (void*)curerntValue;
    }

    return output;
}


int main() {
    // arrays initialization
    int* integers = (int*)malloc(sizeof(int)*5);
    double* doubles = (double*)malloc(sizeof(double) * 5);

    for (int i = 1; i <= 5; ++i)
        integers[i - 1] = i;

    for (int i = 1; i <= 5; ++i)
        doubles[i - 1] = (double)i;

    int initInteger = 0;
    double initDouble = 0.0;

    // tests for addition operations
    int* resultInt = aggregate(integers, sizeof(int), 5, &initInteger, addInt);
    double* resultDouble = aggregate(doubles, sizeof(double), 5, &initDouble, addDouble);
    printf("The result of integer addition for numbers from 1 to 5: %d\n", *resultInt);
    printf("The result of double addition for numbers from 1.0 to 5.0: %.1f\n\n", *resultDouble);

    // tests for multiplication operations
    initInteger = 1;
    initDouble = 1.0;

    resultInt = aggregate(integers, sizeof(int), 5, &initInteger, multiplyInt);
    resultDouble = aggregate(doubles, sizeof(double), 5, &initDouble, multiplyDouble);
    printf("The result of integer multiplication for numbers from 1 to 5: %d\n", *resultInt);
    printf("The result of double multiplication for numbers from 1.0 to 5.0: %.1f\n\n", *resultDouble);

    // tests for mean operations
    initInteger = 0;
    initDouble = 0.0;
    
    resultInt = aggregate(integers, sizeof(int), 5, &initInteger, meanInt);
    resultDouble = aggregate(doubles, sizeof(double), 5, &initDouble, meanDouble);
    printf("The result of integer mean for numbers from 1 to 5: %d\n", *resultInt);
    printf("The result of double mean for numbers from 1.0 to 5.0: %.1f\n", *resultDouble);

    return 0;
}