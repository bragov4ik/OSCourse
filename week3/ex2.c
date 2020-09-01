#include <stdio.h>

void swap(int* a, int* b){
    int t = *a;
    *a = *b;
    *b = t;
}

void bubble_sort(int * a, int size) {
    for (int i = 0; i < size; i++) {
        for (int j = i + 1; j < size; j++) {
            if (a[i] > a[j]) {
                swap(&a[i], &a[j]);
            }
        }
    }
}

int main() {
    int arr[8] = {5, 3, 5, 87, 12, 1, 9, 0};
    bubble_sort(arr, 8);
    for (int i = 0; i < 8; i++) {
        printf("%d", arr[i]);
        if (i < 7) {
            printf(", ");
        }
    }
    printf("\n");
    return 0;
}