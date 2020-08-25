#include <stdio.h>

int main(int argc, char *argv[]) {
    int n = 0;
    if (argc > 1) {
        sscanf(argv[1], "%d", &n);
    }
    else {
        printf("There are no arguments!\n");
        return 0;
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            printf(" ");
        }
        int width = 2*(i+1) - 1;
        for (int j = 0; j < width; j++) {
            printf("*");
        }
        printf("\n");
    }
}