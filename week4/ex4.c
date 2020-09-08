#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>

void create_args(char* input, char *** args) {
    char* inputcpy;

    // count arguments
    strcpy(inputcpy, input);
    char * temp = strtok(inputcpy, " ");
    int argc;
    for (argc = 2; temp != NULL; argc++) {
        temp = strtok(NULL, " ");
    }

    // make args array
    strcpy(inputcpy, input);
    temp = strtok(inputcpy, " ");
    *args = malloc(argc * sizeof(char*));
    int i;
    for (i = 0; temp != NULL; i++) {
        (*args)[i] = temp;
        temp = strtok(NULL, " ");
    }
    (*args)[i+1] = NULL;
}

int main(int argc, char const *argv[]) {
    size_t size = 1;
    char *input = malloc(size);
    getline(&input, &size, stdin);
    input[strlen(input)-1] = 0;

    char ** args = malloc(sizeof(char*));
    create_args(input, &args);

    char * enve[1] = {NULL};

    int parent_pid = getpid();
    fork();
    if (parent_pid != getpid()) {\
        strcpy(input, args[0]);
        execve(input, args, enve);
    }
    return 0;
}

// command to test:
// /bin/ls -l -a