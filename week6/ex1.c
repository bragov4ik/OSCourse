#include <stdio.h>
#include <stdlib.h>

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
    int ** processes = malloc(sizeof(int*) * proc_num);
    printf("For each process write its arrival time and burst time\n");
    for (int i = 0; i < proc_num; i++) {
        int arr, bur;
        scanf("%d %d", &arr, &bur);
        // 0,1 - arrival, burst; 2, 3, 4 - completion time, turnaround time, waiting time
        // respectively
        processes[i] = malloc(sizeof(int) * 5);
        processes[i][0] = arr;
        processes[i][1] = bur;
    }
    // sort processes array:
    custom_sort(processes, proc_num);

    // simulate FCFS

    int TAT_sum = 0;
    int WT_sum = 0;

    int current_time = 0;
    for (int i = 0; i < proc_num; i++) {
        int* next_process = processes[i];
        if (current_time < next_process[0]) {
            current_time = next_process[0];
        }
        current_time += next_process[1];
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