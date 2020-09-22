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

// finds the next job to be executed (SJF)
int* find_next_proc(int** arr, int size, int current_time){
    // the next process considering current time
    int* next_process = NULL;
    // the next process without taking time into account (i.e. )
    int* next_process_wo_time = NULL;

    int burst_min = INT_MAX;
    int burst_min2 = INT_MAX;
    int next_arrival_min = INT_MAX;
    int is_found = 0;
    for (int j = 0; j < size; j++) {
        if (arr[j][5] == 0) {
            if (arr[j][0] < next_arrival_min) {
                next_arrival_min = arr[j][0];
                next_process_wo_time = arr[j];
                int burst_min2 = INT_MAX;
            }
            else if (arr[j][0] == next_arrival_min && arr[j][1] < burst_min2) {
                next_process_wo_time = arr[j];
                burst_min2 = next_process_wo_time[1];
            }
            if (arr[j][0] <= current_time && arr[j][1] < burst_min) {
                next_process = arr[j];
                burst_min = arr[j][1];
                is_found = 1;
            }
        }
    }
    if (is_found) {
        return next_process;
    }
    else {
        return next_process_wo_time;
    }
}

int main() {
    // input
    int proc_num;
    printf("Write the number of processes:\n");
    scanf("%d", &proc_num);
    int ** processes = malloc(sizeof(int*) * proc_num);
    printf("For each process write its arrival time and burst time\n");
    for (int i = 0; i < proc_num; i++) {
        int arr, bur;
        scanf("%d %d", &arr, &bur);
        // 0,1 - arrival, burst; 2, 3, 4 - completion time, turnaround time, waiting time
        // respectively; 
        // 5 - flag whether the process has been executed or not (0 - FALSE, 
        // anything else - TRUE)
        processes[i] = malloc(sizeof(int) * 6);
        processes[i][0] = arr;
        processes[i][1] = bur;
        processes[i][5] = 0;
    }
    // sort processes array:
    custom_sort(processes, proc_num);

    // simulate FCFS

    int TAT_sum = 0;
    int WT_sum = 0;

    int current_time = 0;
    for (int i = 0; i < proc_num; i++) {
        // Scheduling logic
        
        // Find the shortest job
        int* next_process = find_next_proc(processes, proc_num, current_time);

        // Let it "run"
        if (current_time < next_process[0]) {
            current_time = next_process[0];
        }
        current_time += next_process[1];
        next_process[5] = 1;

        // Metrics
        int CT, TAT, WT;
        CT = current_time;
        TAT = CT - next_process[0]; // TAT = CT - AT
        WT = TAT - next_process[1]; // WT = TAT - BT
        TAT_sum += TAT;
        WT_sum += WT;
        next_process[2] = CT;
        next_process[3] = TAT;
        next_process[4] = WT;
    }

    // output
    printf("Result:\n");
    for (int i = 0; i < proc_num; i++) {
        int* next_process = processes[i];
        printf("Process %d (%d, %d):\t", i, next_process[0], next_process[1]);
        printf("    CT:%d\t", next_process[2]);
        printf("    TAT:%d\t", next_process[3]);
        printf("    WT:%d\n", next_process[4]);
    }
    printf("Avg TAT:%f\n", TAT_sum/(double)proc_num);
    printf("Avg WT:%f\n", WT_sum/(double)proc_num);
    return 0;
}