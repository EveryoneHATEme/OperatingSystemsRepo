#include <stdio.h>
#include <string.h>

#define STRING_SIZE 256


int count(char *string, char sub);
char lowercase(char ch);
void countAll(char *string);


int main() {
    char string[STRING_SIZE];
    fgets(string, STRING_SIZE, stdin);

    countAll(string);

    return 0;
}


int count(char *string, char sub) {
    sub = lowercase(sub);
    int result = 0;

    for (int i = 0; i < strlen(string); ++i)
        if (lowercase(string[i]) == sub)
            ++result;
    
    return result;
}


char lowercase(char ch) {
    if (ch >= 'A' && ch <= 'Z')
        ch += 'a' - 'A';
    return ch;
}


void countAll(char *string) {
    for (int i = 0; i < strlen(string); ++i)
        printf("%c: %d\n", lowercase(string[i]), count(string, string[i]));
}