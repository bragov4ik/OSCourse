#include <pthread.h>
#include <sys/types.h>
#include <stdio.h>

#define N 4

void * threaded_func(const char * some_text) {
    printf("Hello, I am a thread number %d! \"%s\"! \n", pthread_self(), some_text);
    pthread_exit(NULL);
    return NULL;
}

int main() {
    pthread_t thread_identifiers[N];
    int return_value;
    const char* some_text = "some text";
    for (int i = 0; i < N; i++) {
        return_value = pthread_create(&thread_identifiers[i], NULL, &threaded_func, some_text);
        if (return_value != 0) {
            printf("error %d \n", return_value);
        }
        else {
            printf("Main here! %d was just created! \n", thread_identifiers[i]);
        }
    }

    for (int i = 0; i < N; i++) {
        pthread_join(thread_identifiers[i], NULL);
    }
}

/* Output:
Main here! 1414002432 was just created! 
Hello, I am a thread number 1414002432! "some text"! 
Main here! 1405609728 was just created! 
Main here! 1397217024 was just created! 
Main here! 1388824320 was just created! 
Hello, I am a thread number 1405609728! "some text"! 
Hello, I am a thread number 1388824320! "some text"! 
Hello, I am a thread number 1397217024! "some text"! 

So here the threads were created, then they are performed in some order
that is decided by the scheduler. They are not necessary executed one by one
as demonstrated in the output: they wrote the text in order 1 2 4 3.
*/