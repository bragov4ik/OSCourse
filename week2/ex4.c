#include <stdio.h>

void swap(int *a, int *b) {
    int c = *a;
    *a = *b;
    *b = c;
}

int main(int argc, char *argv[]) {
    int a;
    int b;
    char c[100];
    printf("Write 2 integers:");
    fgets(c, 100, stdin);
    sscanf(c, "%d %d", &a, &b);

    swap(&a, &b);

    printf("%d %d", a, b);
    return 0;
}