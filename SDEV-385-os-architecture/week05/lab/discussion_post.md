1. Give details of your program along with the source code. Tell us about any problems that you encountered along the way. Give some DETAIL about what you learned about scheduling.

My program implements a priority scheduling algorithm, to schedule 3 processes of varying priorities.

I followed along with a really helpful guide on tutorialspoint to learn about and impelement the algorithm. Priority scheduling, as the name implies, schedules processes by order of some assigned priority. In my implementation, the lower the priority number, the sooner the process will be scheduled.

Priority scheduling is used frequently in batch systems where many batch processes need to be executed on a schedule. The algorithm first sorts all jobs by priority and then executes each process. 

This algorithm works well because it is simple to impelement and also easily allows customization over what needs to be scheduled first. One downside of this algorithm is that a process with a high priority may get stuck or take too long, causing other processes, that may be quick to execute, sit in the queue. A problem could also arise if a process has a very low priority and is never scheduled as higher priority processes continue to enter the queue.

The source code for my algorithm can be seen below:
```c++
#include <iostream>
#include <bits/stdc++.h>

using namespace std;

// Define a struct for process
struct Process {
    int pid; // Process ID
    int bt; // Burst time
    int priority; // Priority
};

// Function to sort processes by priority
bool compare(Process a, Process b) {
    return (a.priority > b.priority);
}

// Function to calculate waiting time for each process
void waitingTime(Process pro[], int n, int wt[]) {
    // Start first process waiting time at 0
    wt[0] = 0;

    // Calculate wait time
    for (int i = 1; i < n; i++) {
        wt[i] = pro[i-1].bt + wt[i-1];
    }
}

// Function to calculate turn around time for each process
void turnaroundTime(Process pro[], int n, int wt[], int tat[]) {
    for (int i = 0; i < n; i++) {
        tat[i] = pro[i].bt + wt[i];
    }
}

// Function to calculate the average time
void avgtime(Process pro[], int n) {
    int wt[n], tat[n], total_wt = 0, total_tat = 0;

    // Get waiting times
    waitingTime(pro, n, wt);

    // Get turnaround times
    turnaroundTime(pro, n, wt, tat);

    // Output table headers
    cout << "\nProcesses "<< " Burst time " << " Waiting time " << " Turn around time\n";

    // Output waiting time and turn around time for each process
    for (int i=0; i<n; i++) {
        total_wt = total_wt + wt[i];
        total_tat = total_tat + tat[i];
        cout << " " << pro[i].pid << "\t\t" << pro[i].bt << "\t " << wt[i] << "\t\t " << tat[i] <<endl;
    }

    cout << "\nAverage waiting time = " << (float)total_wt / (float)n;
    cout << "\nAverage turn around time = " << (float)total_tat / (float)n;
}

// Function to simulate the actual scheduling
void scheduling(Process pro[], int n) {
    // Sort processes by priority
    sort(pro, pro+n, compare);
    cout << "Order that processes get executed \n";
    for (int i = 0; i < n; i++) {
        cout << pro[i].pid << "";
    }
    avgtime(pro, n);
}

// main driver function
int main() {
    Process pro[] = {
        {1, 12, 2},
        {2, 7, 0},
        {3, 5, 1}
    };

    int n = sizeof(pro) / sizeof(pro[0]);
    scheduling(pro, n);
    return 0;
}
```

2. Discuss Salzman’s program. Does it use the function calls that we discussed in the lecture? How is it different? How does it illustrate techniques for scheduling? Does it have limits?

Salzman's program doesn't use any functions from the lecture, as the processes are fake and used purely for testing. However it does imitate some of the functions from the lecture.

The program introduces some really nice ways to test scheduling algorithms. Using the technique of assigning fake burst times we can calculate turnaround times and avg turnaround time for the program without actually having to wait for real processes to execute. This allows us to test algorithms much more quickly and with a more efficient feedback loop.

The limitations of this kind of a program is that the processes are hard coded ahead of time. This means, in its current state, the program couldn't show us what would happen as more processes enter the queue. However, you could create a function that randomly generates processes to add to the queue as the program runs.

**Resources**

(2020). C++ Program for Priority Scheduling. https://www.tutorialspoint.com/cplusplus-program-for-priority-scheduling.