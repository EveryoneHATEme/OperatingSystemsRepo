#include <stdio.h>
#include <stdlib.h>


int main() {
    // Declare a pointer q to a constant integer x whose constant value is 10
    const int x = 10;
    const int *q = &x;

    // Create 5 contiguous memory cells of type constant integer and referred by a constant pointer p. Fill the cells with the value of x.
    int *nonConstPtr = (int*)malloc(sizeof(const int) * 5);
    for (int i = 0; i < 5; ++i)
        nonConstPtr[i] = x;
    const int *p = (const int*)nonConstPtr;

    // Print the memory addresses of these cells to stdout
    for (int i = 0; i < 5; ++i)
        printf("Element #%d with value %d and address %p\n", i, p[i], p + i);

    // Assume that these 5 cells hold the ages of 5 students in years. Read the ages from stdin, and store them in these cells.
    for (int i = 0; i < 5; ++i)
        scanf("%d", nonConstPtr + i);

    for (int i = 0; i < 5; ++i)
        nonConstPtr[i] = 2022 - nonConstPtr[i];

    for (int i = 0; i < 5; ++i)
        printf("Student's #%d birth year is %d\n", i + 1, p[i]);

    free(nonConstPtr);

    return 0;

}