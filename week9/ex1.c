#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define ERR_STR "Wrong number of arguments: expected 2 or 3.\nUse format\nex1 page_frames_count file_name (optional)clock_interrupt_period\n\nExample of use:\nex1 3 ex1.txt\n"
#define PAGE_TABLE_SIZE 1024

// example of command to run:
// ./ex1 100 ./ex1.txt 10

struct page_entry{
    unsigned int R : 1;
    unsigned int V : 1;
    unsigned int age;
};

// set the leftmost bit to be = 1
void set_leftmost_bit(unsigned int* number) {
    *number += pow(2, sizeof(unsigned int)-1);
    return;
}

// shift all ages right by 1 bit, set R bit to the leftmost one for each entry
void update_age(struct page_entry page_table[PAGE_TABLE_SIZE]) {
    for (int i = 0; i < PAGE_TABLE_SIZE; i++) {
        if (page_table[i].R) {
            page_table[i].R = 0;
            page_table[i].age >>= 1;
            set_leftmost_bit(&(page_table[i].age));
        }
        else {
            page_table[i].age >>= 1;
        }
    }
}

// finds the oldest valid entry, removes it from set of valid pages (from physical memory)
void swap_worst_entry(struct page_entry page_table[PAGE_TABLE_SIZE]) {
    int worst_entry_number = -1;
    int worst_entry_age = 0;
    for (int i = 0; i < PAGE_TABLE_SIZE; i++) {
        if (page_table[i].V && page_table[i].age >= worst_entry_age) {
            worst_entry_age = page_table[i].age;
            worst_entry_number = i;
        }
    }
    if (worst_entry_number != -1) {
        page_table[worst_entry_number].V = 0;
    }
    return;
}

int main(int argc, char** argv) {
    int page_frames_count;
    char* file_name;
    
    // Update age every 10 references by default
    int clock_interrupt_period = 10;
    
    // Parse command line arguments
    if (argc == 3 || argc == 4) {
        sscanf(argv[1], "%d", &page_frames_count);
        file_name = malloc(strlen(argv[2])*sizeof(char));
        strcpy(file_name, argv[2]);
        printf("%s\n", file_name);
        if (argc == 4) {
            sscanf(argv[3], "%d", &clock_interrupt_period);
        }
    }
    else {
        printf(ERR_STR);
        return 0;
    }
    FILE *input_file = fopen(file_name, "r");
    
    // create page table
    struct page_entry page_table[PAGE_TABLE_SIZE];
    for (int i = 0; i < PAGE_TABLE_SIZE; i++) {
        page_table[i].age = 0;
        page_table[i].R = 0;
        page_table[i].V = 0;
    }

    int valid_pages_count = 0;

    int hit_count = 0;
    int miss_count = 0;

    int next_page;
    int fscanf_return_value = fscanf(input_file, "%d", &next_page);
    for (int clock_count = 0; fscanf_return_value != EOF; clock_count++) {
        if (clock_count >= clock_interrupt_period) {
            update_age(page_table);
            clock_count = 0;
        }
        if (page_table[next_page].V) {
            // page is in memory (hit)
            page_table[next_page].R = 1;

            hit_count++;
        }
        else {
            // page fault (miss)
            if (valid_pages_count == page_frames_count) {
                update_age(page_table);
                swap_worst_entry(page_table);
                valid_pages_count--;
            }
            page_table[next_page].V = 1;
            page_table[next_page].R = 1;
            valid_pages_count++;

            miss_count++;
        }
        fscanf_return_value = fscanf(input_file, "%d", &next_page);
    }
    printf("Hit/miss ratio is: %lf\n", ((double)hit_count)/miss_count);
    printf("Hits: %d\n", hit_count);
    printf("Misses: %d\n", miss_count);
}

// Tests with data from moodle:

/* 10 page frames, 10 clock interrupt period
Hit/miss ratio is: 0.009082
Hits: 9
Misses: 991
*/

/* 50 page frames, 10 clock interrupt period
Hit/miss ratio is: 0.050420
Hits: 48
Misses: 952
*/

/* 100 page frames, 10 clock interrupt period
Hit/miss ratio is: 0.103753
Hits: 94
Misses: 906
*/
