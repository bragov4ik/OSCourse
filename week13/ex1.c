#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char* argv[]) {
    // get file names
    char* input_file_name;
    char* output_file_name;
    if (argc == 3) {
        input_file_name = malloc(sizeof(char)*strlen(argv[1]));
        input_file_name = strcpy(input_file_name, argv[1]);
        output_file_name = malloc(sizeof(char)*strlen(argv[2]));
        output_file_name = strcpy(output_file_name, argv[2]);
    }
    else {
        printf("Please, specify input and output file names. Example of usage:\n");
        printf("./ex1 input.txt output.txt\n");
        return 0;
    }

    // input (I changed the input format so now we have # of processes and resources on the first line)
    FILE* input_file = fopen(input_file_name, "r");
    
    int p, r;
    fscanf(input_file, "%d", &p);
    fscanf(input_file, "%d", &r);
    // allocate memory
    int* E = malloc(sizeof(int) * r);
    int* A = malloc(sizeof(int) * r);
    int** C = malloc(sizeof(int*) * p);
    for (int i = 0; i < p; i++) {
        C[i] = malloc(sizeof(int) * r);
    }
    int** R = malloc(sizeof(int*) * p);
    for (int i = 0; i < p; i++) {
        R[i] = malloc(sizeof(int) * r);
    }

    int* process_done = malloc(sizeof(int) * p);
    // input
    // E
    for (int i = 0; i < r; i++) {
        fscanf(input_file, "%d", &E[i]);
    }
    // A
    for (int i = 0; i < r; i++) {
        fscanf(input_file, "%d", &A[i]);
    }
    // C
    for (int i = 0; i < p; i++) {
        for (int j = 0; j < r; j++) {
            fscanf(input_file, "%d", &C[i][j]);
        }
    }
    // R
    for (int i = 0; i < p; i++) {
        for (int j = 0; j < r; j++) {
            fscanf(input_file, "%d", &R[i][j]);
        }
    }
    // process_done
    for (int i = 0; i < p; i++) {
        process_done[i] = 0;
    }
    
    int new_process_found = 1;
    while (new_process_found) {
        new_process_found = 0;
        // look for processes whose request we can satisfy
        for (int i = 0; i < p; i++) {
            // if the process was completed and terminated, skip it.
            // we don't need to consider it anymore
            if (process_done[i]) {
                continue;
            }

            int can_satisfy = 1;
            for (int j = 0; j < r; j++) {
                if (R[i][j]> A[j]) {
                    can_satisfy = 0;
                    break;
                }
            }
            if (can_satisfy) {
                // we found such process
                new_process_found = 1;
                for (int j = 0; j < r; j++) {
                    // return the resources of the process after its execution
                    A[j] += C[i][j];
                    C[i][j] = 0;
                    // clear his requests
                    R[i][j] = 0;
                    // mark is as finished
                    process_done[i] = 1;
                }
            }
        }
    }
    // count processes that were unable to finish
    int unfinished_processes = 0;
    for (int i = 0; i < p; i++) {
        unfinished_processes += process_done[i];
    }
    unfinished_processes = p - unfinished_processes;
    FILE* output_file = fopen(output_file_name, "w");
    if (unfinished_processes) {
        fprintf(output_file, "%d processes were deadlocked", unfinished_processes);
    }
    else {
        fprintf(output_file, "No deadlock\n");
    }
    return 0;
}