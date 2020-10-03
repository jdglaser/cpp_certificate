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