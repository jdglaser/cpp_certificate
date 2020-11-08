#include<stdio.h>
#include<unistd.h>
#include<pthread.h>

/*============================================================*/
// SDEV 385 Homework Week 6
// Jarred Glaser
//
// Information
//  - SDEV 385 Homework Week 6
//  - Jarred Glaser
//  - OS: Ubuntu 20.04.1 LTS
//  - Compiler: gcc version 9.3.0 (Ubuntu 9.3.0-10ubuntu2)
//  - Last Updated: 2020-10-11
/*===========================================================*/

// Globals
int key = 0;
int lock = 0;
int waiting[3]; // 3 processes
int n_processes = sizeof(waiting)/sizeof(waiting[0]);

// Set a test num that should end up the same as it started (1)
// if mutual exclusion is properly handled
int test_num = 1;

// Create a swap function - assume function is atomic
// normally this would be an architecture specific hardware
// instruction
void swap(int *valA, int *valB) {
    int temp = *valA;
    *valA = *valB;
    *valB = temp;

    return;
}

// Create a function that does some work on shared
// variables in a critial section. waiting array 
// and key are used to provide mutual exclusion 
// and satisfy the bounded waiting requirement
void *work(int process) {
    waiting[process] = 1;
    key = 1;

    while (waiting[process] == 1 && key == 1) {
        // The swap function changes the key and lock values
        // if the lock has not been released and the waiting
        // flag for the process has not been flipped, then
        // this while loop will repeat
        swap(&key, &lock);
    }

    waiting[process] = 0;

    // Critical section //
    // sleep for a short time in between calculations to allow processes to catch up to each other
    // If mutual exclusion is not provided, the calulcaiton will be wrong
    test_num -= 1;
    usleep(50);
    test_num *= 10;
    usleep(50);
    test_num += 1;
    printf("Thread %d did work on test_num. It is now: %d\n", process, test_num);
    

    // Exit critical section - loop through processes //
    // j set to next process
    int j = (process + 1) % n_processes;
    // if j process != current process and j process is not waiting
    // move to next process.
    while((j != process) && waiting[j] != 1) {
        j = (j + 1) % n_processes;
    }

    // if we are back at the current process, unlock - solves mutual exclusion
    // if j is a waiting process let the process enter the critical section - solves boundless waiting
    if (j == process) {
        lock = 0;
    } else {
        waiting[j] = 0;
    }
    
}

// Main driver function
int main() {
    printf("Starting...\n");
    pthread_t threads[n_processes];
    
    // Create threads
    for (int i=0; i < n_processes; i++) {
        waiting[i] = 0;
        pthread_create(&threads[i], NULL, work, (void*) i);
    }

    // join threads
    for (int i = 0; i < n_processes; i++) {
        pthread_join(threads[i], NULL);
    }

    // Final check of test_num
    printf("Final value of test_num should be 1. It is: %d\n", test_num);

    return 0;
}