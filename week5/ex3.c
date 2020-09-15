#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define BUF_SIZE 10

int producer_awake;
int consumer_awake;
int buf_count;

time_t last_producer_print_time;

void * producer(int* arg) {
    srandom(pthread_self());
    while (1) {
        if (producer_awake) {
            // produce something
            if (buf_count >= BUF_SIZE) {
                producer_awake = 0;
            }
            else {
                int next_int = random();
                arg[buf_count] = next_int;
                buf_count++;
            }
            // if there are some items in the buffer, wake up the consumer
            if (buf_count == 1) {
                consumer_awake = 1;
            }
            // once in a minute output
            time_t current_time = time(NULL);
            if (difftime(current_time, last_producer_print_time) > 60) {
                printf("I am the producer! I'm still working!!\n");
                last_producer_print_time = time(NULL);
            }
        }
        else {
            // if there was no output for >2 minutes, write that something is wrong
            time_t current_time = time(NULL);
            if (difftime(current_time, last_producer_print_time) > 120) {
                printf("The producer is not working for > 2 minutes...\n");
                last_producer_print_time = time(NULL);
            }
        }
    }
    
    pthread_exit(NULL);
    return NULL;
}

void * consumer(int* arg) {
    srandom(pthread_self());
    while (1) {
        if (consumer_awake) {
            // consume somehow
            if (buf_count <= 0) {
                consumer_awake = 0;
            }
            else {
                int next_int = arg[buf_count-1];
                next_int += random();
                arg[buf_count-1] = 0;
                buf_count--;
            }
            // if there are some items in the buffer, wake up the consumer
            if (buf_count == BUF_SIZE-1) {
                producer_awake = 1;
            }
        }
    }

    pthread_exit(NULL);
    return NULL;
}

int main() {
    buf_count = 0;
    producer_awake = 1;
    consumer_awake = 0;
    last_producer_print_time = 0;
    int *buffer = malloc(sizeof(int) * BUF_SIZE);

    
    pthread_t producer_identifier, consumer_identifier;

    // start producer
    int return_value = pthread_create(&producer_identifier, NULL, &producer, buffer);
    if (return_value != 0) {
        printf("error on creating thread: %d \n", return_value);
    }

    // start consumer
    return_value = pthread_create(&consumer_identifier, NULL, &consumer, buffer);
    if (return_value != 0) {
        printf("error on creating thread: %d \n", return_value);
    }

    pthread_join(producer_identifier, NULL);
    pthread_join(consumer_identifier, NULL);

    return 0;
}