#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main(int argc, char *argv[]) {
    // get input from stdio
    char* input = malloc(sizeof(char) * 33);
    {
        int buffer_size = 32;
        char buf;
        for (int i = 0; read(STDIN_FILENO, &buf, 1) > 0; i++) {
            input[i] = buf;
            if (i >= buffer_size) {
                input = realloc(input, buffer_size * 2 + 1);
                buffer_size *= 2;
            }        
        }   
    }
    input = realloc(input, strlen(input)+1);
    input[strlen(input)] = '\0';
    // at this point input contains all the input from stdio
    write(STDOUT_FILENO, input, strlen(input));

    int append_mode = 0;
    // from which argument file names start
    int arg_startfiles = 1;
    if (argc >= 2 && strcmp(argv[1], "-a") == 0) {
        append_mode = O_APPEND;
        arg_startfiles++;
    }
    for (int i = arg_startfiles; i < argc; i++) {
        int file_d = open(argv[i], O_WRONLY | O_CREAT | append_mode, S_IRWXU | S_IRWXG | S_IRWXO);
        write(file_d, input, strlen(input));
        close(file_d);
    }
    return 0;
}