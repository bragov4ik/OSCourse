#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#define STRING_SIZE 20

int main() {
    char* buffer = malloc(sizeof(char)*STRING_SIZE);
    int random_fd = open("/dev/random", O_RDONLY);
    int ex1txt_fd = open("./ex1.txt", O_RDWR | O_CREAT, S_IRWXU | S_IRWXG | S_IRWXO);
    read(random_fd, buffer, STRING_SIZE);
    write(ex1txt_fd, buffer, STRING_SIZE);
    return 0;
}