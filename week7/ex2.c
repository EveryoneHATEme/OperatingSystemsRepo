#include <stdio.h>
#include <stdlib.h>


int main() {
    int sizeOfArray;

    // prompting the user to enter N 
    printf("Enter N: ");
    scanf("%d", &sizeOfArray);

    // allocating memory for an array of N integers
    int* array = (int*)malloc(sizeof(int) * sizeOfArray); 

    // filling the array with incremental values
    for (int i = 0; i < sizeOfArray; ++i)
        array[i] = i;

    // printing the array
    // i have no idea what does mean "printing the array", so the program will print the address of the array and its values

    printf("Address of the first value in the array: %p\n", array);

    printf("Values of the array: ");
    for (int i = 0; i < sizeOfArray; ++i) {
        if (i != sizeOfArray - 1)
            printf("%d ", array[i]);
        else
            printf("%d\n", array[i]);
    }

    // Deallocating the memory
    free(array);

    // it was not specified how we should name the file and should we write shell script for executing it

    return 0;
}