#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_FILES_LENGTH 256
#define MAX_DIRECTORIES_LENGTH 8
#define MAX_NAME_LENGTH 64
#define MAX_PATH_LENGTH 2048
#define MAX_DATA_LENGTH 1024


struct File {
    unsigned long id;
    char name[MAX_NAME_LENGTH];
    unsigned long size;
    char data[MAX_DATA_LENGTH];
    struct Directory* directory;
};


struct Directory
{
    struct File* files[MAX_FILES_LENGTH];
    struct Directory* directories[MAX_DIRECTORIES_LENGTH];
    unsigned int nf;
    unsigned int nd;
    char path[MAX_PATH_LENGTH]; 
};


struct File* createFile(const char* name, const char* data) {
    static unsigned long count = 0lu;

    struct File* newFile = (struct File*)malloc(sizeof(struct File));
    newFile->id = count++;
    strcpy(newFile->name, name);
    strcpy(newFile->data, data);
    newFile->size = (unsigned long)(strlen(data) + 1);

    return newFile;
}


void add_to_file(struct File* file, const char* str) {
    strcpy(file->data, str);
}


void append_to_file(struct File* file, const char* str) {
    strcat(file->data, str);
}


void pwd_file(struct File* file) {
    printf("%s%s\n", file->directory->path, file->name);
}


struct Directory* createDirectory(const char* path) {
    struct Directory* newDirectory = (struct Directory*)malloc(sizeof(struct Directory));
    
    newDirectory->nf = 0;
    newDirectory->nd = 0;
    strcpy(newDirectory->path, path);
}


void add_file(struct Directory* directory, struct File* file) {
    directory->files[directory->nf] = file;
    ++directory->nf;

    file->directory = directory;
}


void add_directory(struct Directory* parentDirectory, struct Directory* childDirectory) {
    parentDirectory->directories[parentDirectory->nd] = childDirectory;
    ++parentDirectory->nd;
}


int main() {
    struct Directory* rootDirectory = createDirectory("/");
    struct Directory* homeDirectory = createDirectory("/home/");
    struct Directory* binDirectory = createDirectory("/bin/");
    add_directory(rootDirectory, homeDirectory);
    add_directory(rootDirectory, binDirectory);

    struct File* bashFile = createFile("bash", "");
    add_file(binDirectory, bashFile);

    struct File* ex3_1File = createFile("ex3_1.c", "int printf(const char * format, ...);");
    struct File* ex3_2File = createFile("ex3_2.c", "//This is a comment in C language");
    
    add_file(homeDirectory, ex3_1File);
    add_file(homeDirectory, ex3_2File);

    append_to_file(bashFile, "Bourne Again Shell!!");

    append_to_file(ex3_1File, "int main(){printf(\"Hello World!\")}");

    pwd_file(bashFile);
    pwd_file(ex3_1File);
    pwd_file(ex3_2File);

    return 0;
}