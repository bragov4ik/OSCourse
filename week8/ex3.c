#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define TEN_MB (2*512*1024*1024)

int main() {
    int* ptr;
    for (int i = 0; i < 10; i++) {
        ptr = malloc(TEN_MB);
        memset(ptr, 0, TEN_MB);
        sleep(1);
    }
    return 0;
}

/*
I reduced allocation size to 1 GB to avoid freezing of my PC c:
What happend now is the process ex2 started to consume more and more memory
and after it has finished it disappeared from the list and freed all the memory
*/