#include <stdio.h>
#include <dirent.h>


int main() {
    struct dirent *entry;
    DIR *directory = opendir("/");
    FILE* file = fopen("ex2.txt", "a");

    fprintf(file, "Content of the root:\n");

    while ((entry = readdir(directory)))
        fprintf(file, "%s\n", entry->d_name);

    return 0;
}