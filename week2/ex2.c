#include <stdio.h>
#include <string.h>

int main() {
    char a[100];
    fgets(a, 100, stdin);
    int length = strlen(a);
    for (int i = length-1; i >= 0; i--) {
        printf("%c", a[i]);
    }
    return 0;
}