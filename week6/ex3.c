#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

void custom_swap(int** a, int** b) {
    int* temp;
    temp = *a;
    *a = *b;
    *b = temp;
}

void custom_sort(int** arr, int size) {
    for (int i = 0; i < size; i++) {
        for (int j = i+1; j < size; j++) {
            if (arr[i][0] > arr[j][0]) {
                custom_swap(&(arr[i]), &(arr[j]));
            }
        }
    }
}

int main() {
    // input
    int proc_num;
    printf("Write the number of processes:\n");
    scanf("%d", &proc_num);

    int quantum;
    printf("Write the quantum value:\n");
    scanf("%d", &quantum);

    int ** processes = malloc(sizeof(int*) * proc_num);
    printf("For each process write its arrival time and burst time\n");
    for (int i = 0; i < proc_num; i++) {
        int arr, bur;
        scanf("%d %d", &arr, &bur);
        // 0,1 - arrival, burst; 2, 3, 4 - completion time, turnaround time, waiting time
        // respectively; 
        // 5 - flag whether the process has been executed or not (0 - FALSE, 
        // anything else - TRUE)
        // 6 - execution time left
        processes[i] = malloc(sizeof(int) * 7);
        processes[i][0] = arr;
        processes[i][1] = bur;
        processes[i][5] = 0;
        processes[i][6] = bur;
    }
    // sort processes array:
    custom_sort(processes, proc_num);

    // simulate FCFS

    int TAT_sum = 0;
    int WT_sum = 0;

    int current_time = 0;

    int not_finished = 1;
    while (not_finished) {
        // Scheduling logic
        int last_i = 0;

        int smthng_executed = 0;
        int* next_process = processes[0];
        for (int i = 0; i < proc_num && processes[i][0] <= current_time; i++) {
            next_process = processes[i];
            if (!next_process[5]) {
                smthng_executed = 1;
                // execute the process
                if (next_process[6] < quantum) {
                    current_time += next_process[6];
                    next_process[6] = 0;
                }
                else {
                    current_time += quantum;
                    next_process[6] -= quantum;
                }

                // terminate the process if needed
                if (next_process[6] <= 0) {
                    next_process[5] = 1;

                    // Metrics  

                    // CT
                    next_process[2] = current_time;
                    // TAT
                    next_process[3] = current_time - next_process[0];
                    // WT
                    next_process[4] = next_process[3] - next_process[1];
                }
            }
            last_i = i;
            if (!(i+1 < proc_num)) {
                // if we went through all processes and all of them are terminated, we're done
                not_finished = smthng_executed;
            }
        }
        
        // if nothing was executed and there are processes left, there are no processes 
        // pending at current time therefore, our CPU waits until he gets the next one
        if (!smthng_executed && last_i + 1 < proc_num) {
            current_time = processes[last_i + 1][0];
        }
    }

    // output
    printf("Result:\n");
    for (int i = 0; i < proc_num; i++) {
        int* next_process = processes[i];
        printf("Process %d (%d, %d):\t", i, next_process[0], next_process[1]);
        printf("    CT:%d\t", next_process[2]);
        printf("    TAT:%d\t", next_process[3]);
        printf("    WT:%d\n", next_process[4]);
        TAT_sum += next_process[3];
        WT_sum += next_process[4];
    }
    printf("Avg TAT:%f\n", TAT_sum/(double)proc_num);
    printf("Avg WT:%f\n", WT_sum/(double)proc_num);
    return 0;
}