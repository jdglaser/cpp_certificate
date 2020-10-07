#include<stdio.h>
#include<unistd.h>
#include<pthread.h>

/*======================================*/
// SDEV 385 Lab Week 6 
/*======================================*/

// Set globals
int flag[2]; // control
int turn;

int COUNTER = 1;
int CHECK = 10;

int TEST_WITH_LOCK;

// Locks thread using peterson algorithm
void lock(int self) {
    // set flag for thread to 1
    flag[self] = 1;
    // set turn
    turn = 1-self;

    printf("Thread %d is waiting for lock to be free\n", self);
    while (flag[1-self] == 1 && turn==1-self);
    printf("Thread %d has entered the CS\n", self);
}

// Unlocks thread - use after leaving critical section
void unlock(int self) {
    printf("Thread %d has left the CS\n", self);
    flag[self] = 0;
}

void* work(void *process) {
    int processId = (int *)process;
    int wait_time;

    for (int i=0; i<3; i++) {

        if (TEST_WITH_LOCK == 1) {
            lock(processId);
        }

        // Start operations
        COUNTER -= 1;
        usleep(5);
        COUNTER *= CHECK;
        usleep(5);
        COUNTER += 1;
        printf("Thread %d has worked on COUNTER - it is now: %d\n", processId, COUNTER);

        if (TEST_WITH_LOCK == 1) {
            unlock(processId);
        }

        usleep(rand() % 100 + 1);
        
        wait_time = rand() % 3 + 1;
        sleep(wait_time);
    }
}

int main() {
    pthread_t p1, p2;
    turn = 0;
    flag[0] = 0;
    flag[1] = 0;

    // Get user input for testing
    printf("Run using Peterson Algorithm? (1 yes; 0 no): ");
    scanf("%d", &TEST_WITH_LOCK);

    if (TEST_WITH_LOCK == 1) {
        printf("Running with Peterson algorithm...\n");
    } else {
        printf("Running without Peterson algorithm...\n");
    }

    // Create Threads
    pthread_create(&p1, NULL, work, (void*) 0);
    pthread_create(&p2, NULL, work, (void*) 1);

    // Wait for the threads to end. 
    pthread_join(p1, NULL); 
    pthread_join(p2, NULL); 

    printf("Checking Counter Variable...\n");
    if (COUNTER == 1) {
        printf("COUNTER == 1 : TEST PASSED\n");
    } else {
        printf("COUNTER == %d; Expected 1 : TEST FAILED\n", COUNTER);
    }
}