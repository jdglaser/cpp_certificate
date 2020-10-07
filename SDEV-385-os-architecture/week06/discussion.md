# Week 6 Discussion

## Lab Instructions

In this lab, you will write code that implements Peterson’s algorithm using multiple threads or processes.

Peterson's algorithm guarantees mutual exclusion between two or more processes, using shared memory to communicate between those processes. Using two processes as an example, process A may want to access the critical section of the algorithm. It sets a flag value to true to indicate its intentions. A second variable that is usually called turn is used to indicate which process has priority. If process A sets the flag variable to true, indicating it wants to enter the critical section AND the turn variable is set to 0, indicating that process B gives up priority to process A, then Process A can enter the critical section. Process A can also enter the critical section if process B does not indicate that it wants to enter the critical section in the flag variable.

You will need to do the following:

Write at least 3 processes or threads that do the same type of work. Example: The math problem listed in the lecture.
Create a timer that calls the processes randomly for a set number of iterations.
Implement Peterson’s code to keep them sorted out.

## Solution

1. *Upload your Lab 6 code and describe your solution with the class.*

For my approach, I wanted to find a way to test that Peterson's algorithm actually was working behind the scenese. I decided to simply add a variable called `COUNTER` and another variable called `CHECK`. The `work` function will loop 3 times through a critical section that will:
- Subtract 1 from `COUNTER` (making it 0)
- Multiply it by `CHECK` (initialized at 10)
- Add 1 back to `COUNTER`.

Building a simple unit test case off of the `work` function, we can say that, if the threads do not overlap each other during the critical portion, then we expect `COUNTER` to remain at 1 by then end of the program.

This example program can be seen below:

```c++
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
```

First let's test the program without Peterson's algorithm:

```
Run using Peterson Algorithm? (1 yes; 0 no): 0
Running without Peterson algorithm...
Thread 0 has worked on COUNTER - it is now: -99
Thread 1 has worked on COUNTER - it is now: -98
Thread 0 has worked on COUNTER - it is now: -989
Thread 1 has worked on COUNTER - it is now: -9899
Thread 0 has worked on COUNTER - it is now: -990099
Thread 1 has worked on COUNTER - it is now: -990098
Checking Counter Variable...
COUNTER == -990098; Expected 1 : TEST FAILED
```

We can see that the test failed. Without proper synchronization control, the threads kept overlapping each other during their critical sections. This ended in a vastly incorrect `COUNTER` variable.

Now let's try again with Peterson's algorithm turned on:

```
Run using Peterson Algorithm? (1 yes; 0 no): 1
Running with Peterson algorithm...
Thread 0 is waiting for lock to be free
Thread 0 has entered the CS
Thread 1 is waiting for lock to be free
Thread 0 has worked on COUNTER - it is now: 1
Thread 0 has left the CS
Thread 1 has entered the CS
Thread 1 has worked on COUNTER - it is now: 1
Thread 1 has left the CS
Thread 0 is waiting for lock to be free
Thread 0 has entered the CS
Thread 1 is waiting for lock to be free
Thread 0 has worked on COUNTER - it is now: 1
Thread 0 has left the CS
Thread 1 has entered the CS
Thread 1 has worked on COUNTER - it is now: 1
Thread 1 has left the CS
Thread 1 is waiting for lock to be free
Thread 1 has entered the CS
Thread 1 has worked on COUNTER - it is now: 1
Thread 1 has left the CS
Thread 0 is waiting for lock to be free
Thread 0 has entered the CS
Thread 0 has worked on COUNTER - it is now: 1
Thread 0 has left the CS
Checking Counter Variable...
COUNTER == 1 : TEST PASSED
```

We can see that the unit test passes this time. Peterson's algorithm does in fact keep proper synchronization between processes.

2. *Here are two attempts at concurrency algorithms. Critique each and suggest possible changes. Be specific in what works and does not work with each.*

    ```c++
     //Check to see if another process needs to enter it’s critical section
    shared int flag[2];
    void enterCritical(int theRequestingProcess){
          flag[theRequestingProcess]=1;
         while (flag[1-theRequestingProcess]);
    }
    void leaveCritical(int theRequestingProcess) {
      flag[theRequestingProcess]=0;
    }


    //let the processes take turns
    shared int myTurn =0;

    void enterCritical (int theRequestingProcess)
    {
                while(myTurn != theRequestingProcess);
    }
     void leaveCritical(int theRequestingProcess)
      {
            myTurn = 1 – theRequestingProcess;
    }
    ```

The first example above shows Peterson's algorithm, but only with the flag control, and the turn control left out.

