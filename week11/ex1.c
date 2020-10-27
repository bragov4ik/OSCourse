#include <stdlib.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>

int main() {
    int file_descriptor = open("./ex1.txt", O_RDWR);
    struct stat* file_statistics = malloc(sizeof(struct stat));
    if(fstat(file_descriptor, file_statistics)) {
        printf("error in fstat");
        return -1;
    }
    void *mapped_area = mmap(NULL, file_statistics->st_size, PROT_READ | PROT_WRITE, MAP_SHARED, file_descriptor, 0);
    if(ftruncate(file_descriptor, sizeof(char)*18)) {
        printf("error in ftruncate");
        return -1;
    }
    char str[19]= "This is a nice day";
    memcpy(mapped_area, str, 18);
    munmap(mapped_area, sizeof(char)*18);
    close(file_descriptor);
    return 0;
}