#include <stdio.h>
#include <string.h>


void convert(long long number, int source, int target);


int main() {
    convert(1234, 8, 2);

    return 0;
}


void convert(long long number, int source, int target) {
    if (source < 2 || source > 10 || target < 2 || source > 10) {
        printf("cannot convert\n");
        return;
    }

    char string_number[1024];
    sprintf(string_number, "%lld", number);
    int length = strlen(string_number);

    for (int i = 0; i < length; ++i) {
        if ((int)(string_number[i] - '0') >= source) {
            printf("cannot convert\n");
            return;
        }
    }

    long long decimal = 0;
    for (int i = length - 1, multiplier = 1; i >= 0; --i, multiplier *= source)
        decimal += ((long long)(string_number[i] - '0')) * multiplier;

    char result[1024];
    int current_position = 0;
    long long remainder;

    while (decimal != 0) {
        remainder = decimal % target;
        result[current_position++] = (char)remainder + '0';
        decimal /= target;
    }

    for (int i = current_position - 1; i >= 0; --i)
        putchar(result[i]);
    putchar('\n');
}
