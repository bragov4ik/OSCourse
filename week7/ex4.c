#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>

void *my_realloc(void *ptr, size_t size);

int main() {
    int n1, n2;
    scanf("%d", &n1);
    scanf("%d", &n2);
    printf("\n");
    int* a = malloc(sizeof(int)*n1);
    for (int i = 0; i < n1; i++) {
        a[i] = i;
        printf("%d ", a[i]);
    }
    printf("\n");
    a = my_realloc(a, sizeof(int)*n2);
    for (int i = 0; i < n2; i++) {
        printf("%d ", a[i]);
    }
    printf("\n");
}

void *my_realloc(void *ptr, size_t size) {
    size_t old_size = malloc_usable_size(ptr);
    size_t new_size = size;
    if(!ptr) {
        return malloc(new_size);
    }
    else if (new_size == 0) {
        free(ptr);
        return NULL;
    }
    else {
        void *new_ptr = malloc(new_size);
        if(new_ptr) {
            // copy only min(old_size, new_size) bytes
            memcpy(new_ptr, ptr, (new_size > old_size ? old_size : new_size));
            free(ptr);
            return new_ptr;
        }
    }
}

/* implementation with a different interface (doesn't use malloc_usable_size)

void *my_realloc(void *ptr, size_t old_size, size_t new_size) {
    if(!ptr) {
        return malloc(new_size);
    }
    else if (new_size == 0) {
        free(ptr);
        return NULL;
    }
    else {
        void *new_ptr = malloc(new_size);
        if(new_ptr) {
            // copy only min(old_size, new_size) bytes
            memcpy(new_ptr, ptr, (new_size > old_size ? old_size : new_size));
            free(ptr);
            return new_ptr;
        }
    }
}
*/