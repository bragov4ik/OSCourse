#include <stdlib.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>

int main() {
    // obtain contents of ex1.txt
    int source_file = open("./ex1.txt", O_RDONLY);
    struct stat* source_file_statistics = malloc(sizeof(struct stat));
    if(fstat(source_file, source_file_statistics)) {
        printf("error in fstat\n");
        return -1;
    }
    char* source_text = malloc(sizeof(char) * source_file_statistics->st_size);
    read(source_file, source_text, source_file_statistics->st_size);

    // write it to ex1.memcpy.txt
    int file_descriptor = open("./ex1.memcpy.txt", O_RDWR);
    struct stat* file_statistics = malloc(sizeof(struct stat));
    if(fstat(file_descriptor, file_statistics)) {
        printf("error in fstat\n");
        return -1;
    }
    if(ftruncate(file_descriptor, sizeof(char) * source_file_statistics->st_size)) {
        printf("error in ftruncate\n");
        return -1;
    }
    void *mapped_area = mmap(NULL, file_statistics->st_size, PROT_READ | PROT_WRITE, MAP_SHARED, file_descriptor, 0);
    memcpy(mapped_area, source_text, source_file_statistics->st_size);
    munmap(mapped_area, sizeof(char) * source_file_statistics->st_size);

    close(source_file);
    close(file_descriptor);
    return 0;
}