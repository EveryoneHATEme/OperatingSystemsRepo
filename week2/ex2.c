#include <stdio.h>

#define STRING_SIZE 256


int readString(char *string);


int main() {
    char buffer[STRING_SIZE];

    printf("Please, enter a string:\n");
    int length = readString(buffer);

    putchar('"');
    
    for (int i = length - 1; i >= 0; --i)
        putchar(buffer[i]);
    
    putchar('"');
    putchar('\n');

    return 0;
}


int readString(char *string) {
    char current_char = getchar();
    int current_position = 0;

    while (current_char != '.' && current_char != '\n' && current_char != '\0') {
        string[current_position++] = current_char;
        current_char = getchar();
    }

    string[current_position] = '\0';

    return current_position;
}