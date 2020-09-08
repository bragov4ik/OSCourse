#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

int main() {
    for (int i = 0; i < 5; i++) {
        fork();
    }
    sleep(5);
    return 0;
}

/*
So 8 processes were created in total for 3 iterations. 
1 child was created on first iteration
2 - 2nd
4 - 3rd
Total number of children = 7; add 1 original process and we get 8.
The formula for # of them is 2^n, n - number of iterations.
It's true because we create (1+2+4+8+...+2^(n-1)) = 2^n - 1 children.
Adding 1 parent we get 2^n.
For 5 iterations it should produce 32 processes. It indeed happens
when we try to run it.
*/