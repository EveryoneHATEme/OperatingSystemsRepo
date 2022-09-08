#include <stdio.h>
#include <limits.h>
#include <float.h>


int main() {
    int integer = INT_MAX;
    unsigned short unsinged_short = USHRT_MAX;
    long signed_long = LONG_MAX;
    float float_variable = FLT_MAX;
    double double_variable = DBL_MAX;

    printf("integer of size: %ld and a value: %d\n", sizeof(integer), integer);
    printf("unsigned short integer of size: %ld and a value: %d\n", sizeof(unsinged_short), unsinged_short);
    printf("signed long integer of size: %ld and a value: %ld\n", sizeof(signed_long), signed_long);
    printf("float of size: %ld and a value: %f\n", sizeof(float_variable), float_variable);
    printf("double of size: %ld and a value: %f\n", sizeof(double_variable), double_variable);
}