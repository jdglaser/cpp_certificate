#include <iostream>
#include <string>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>

using namespace std;

int iglobal =0;

void increment_values(pid_t pid, int &ilocal) {
    if (pid == 0) {
        iglobal ++;
        ilocal ++;
        cout << "calling from child: " << getpid() << " in parent " << getppid() << endl;
        cout << "  iglobal " << iglobal << endl;
        cout << "  ilocal " << ilocal << endl;
        exit(0);
    } else if (pid < 0) {
        exit(1); // fork failed
    } else {
        return; // do nothing if calling from parent
    }
}


int main ()
{
    int numchildren = 3;
    int ilocal =10;

    int parentId = (int) getpid();

    cout<<"Calling from parent " << parentId <<endl;
    cout<<"  iglobal " <<iglobal<<endl;
    cout<<"  ilocal "<<ilocal<<endl;; // in parent

    for (int i = 0; i < numchildren; i++) {
        pid_t pid = fork();
        increment_values(pid, ilocal);
    }

    for (int i = 0; i < numchildren; i++)
        wait(nullptr); // wait for each child process to finish - nullptr could accept status of each child

}//end main()