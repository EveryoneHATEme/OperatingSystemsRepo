#include <stdio.h>
#include <stdlib.h>
#include <string.h>


void* handmadeRealloc(void* ptr, size_t originalSize, size_t newSize) {
    if (newSize == 0) {
        free(ptr);
        return NULL;
    }

    char* newAllocation = (void*)malloc(sizeof(void) * newSize);
    
    if (ptr == NULL) {
        free(ptr);
        return newAllocation;
    }

    memcpy(newAllocation, ptr, originalSize <= newSize ? originalSize : newSize);
    
    free(ptr);

    return newAllocation;
}


int main() {
    int size;
    scanf("%d", &size);

    int* array = (int*)malloc(sizeof(int) * size);
    for (int i = 0; i < size; ++i)
        array[i] = 1001;
    
    for (int i = 0; i < size; ++i)
        printf("%d ", array[i]);
    printf("\n");

    int newSize;
    scanf("%d", &newSize);

    array = (int*)handmadeRealloc(array, size, newSize);
    for (int i = 0; i < newSize; ++i)
        printf("%d ", array[i]);
    printf("\n");

    free(array);

    return 0;
}