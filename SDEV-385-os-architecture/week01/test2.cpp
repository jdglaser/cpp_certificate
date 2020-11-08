#include <iostream>
#include <string>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>

using namespace std;

const int Children = 4;
int iglobal = 1;

void f1(pid_t pID, int i, int *iExample) {
    string sLocation;

    if (pID == 0) {
        // Child process code
        sLocation = "In child process";
        (*iExample)++; // Think about the scope of these variables
        iglobal++;
    } else {
        sLocation = "In parent process";
    }

    cout << "Location:  " << sLocation << endl;
    cout << "       i:  " << i << endl;
    cout << " iglobal:  " << iglobal << endl;
    cout << "iExample:  " << *iExample << '\n' << endl;
}

int main () {
    int iExample = 10;
    int status[Children];
    int child_status;
    bool parent = true;

    for (int i = 0; i < Children; ++i) {
        pid_t pID;

        if (parent) {
            pID = fork(); // Create a child process
        } else {
            break;
        }

        if (pID < 0) {
            cerr << "Failed to spawn process" << endl;
            exit(1);
        } else if (pID == 0) { // In a child
            parent = false; // Prevent child from forking more children
            f1(pID, i, &iExample);
        } else { // In parent
            status[i] = pID; // Save child process ID
            if (i == 0) { // Only invoke function from parent once
                f1(pID, i, &iExample);
            }
        }
    }

    // Wait for children - good housekeeping:
    for (int i = 0; i < Children; ++i) {
        pid_t pID;
        // Ideally should check child status...
        pID = waitpid(status[i], &child_status, 0);
    }
} // end main()