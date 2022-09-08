#include <stdio.h>
#include <string.h>
#include <stdlib.h>


void drawRightTriangle(int n);
void drawTriangle(int n);
void drawRectangle(int n);


int main(int argc, char **argv) {
    if (argc < 2)
        return 0;

    int side = atoi(argv[2]);

    if (!strcmp(argv[1], "rightTriangle"))
        drawRightTriangle(side);
    else if (!strcmp(argv[1], "triangle"))
        drawTriangle(side);
    else if (!strcmp(argv[1], "rectangle"))
        drawRectangle(side);

    return 0;
}


void drawRightTriangle(int n) {
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= i; ++j)
            putchar('*');
        putchar('\n');
    }
}


void drawTriangle(int n) {
    for (int i = 1; i <= n / 2 + (n % 2); ++i) {
        for (int j = 1; j <= i; ++j)
            putchar('*');
        putchar('\n');
    }

    for (int i = n / 2; i >= 1; --i) {
        for (int j = 1; j <= i; ++j)
            putchar('*');
        putchar('\n');
    }
}


void drawRectangle(int n) {
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j)
            putchar('*');
        putchar('\n');
    }
}