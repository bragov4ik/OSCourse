#include <stdio.h>
#include <stdlib.h>

int main() {
    int N;
    printf("Type size of the array: ");
    scanf("%d", &N);
    int* arr = malloc(N*sizeof(int));
    printf("The array:\n");
    for(int i = 0; i < N; i++) {
        arr[i] = i;
        printf("%d ", arr[i]);
    }
    printf("\n");
    free(arr);
}