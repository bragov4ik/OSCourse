#include <stdio.h>
#include <stdlib.h>

int main() {
    size_t size = 1;
    char *input = malloc(size);
    getline(&input, &size, stdin);
    system(input);
}