# Week 14: Assignment - Identical C/C++ Programs in Linux and Windows

Jarred Glaser
2020-12-13

For this assignment I am using the g++ compiler for Windows and the g++ compiler for Ubuntu to compile identical C++ programs and compare their execution time.

The compiler for Windows: `g++ (i686-posix-dwarf-rev0, Built by MinGW-W64 project) 8.1.0`
The compiler for Ubuntu: `g++ (Ubuntu 9.3.0-17ubuntu1~20.04) 9.3.0`

The test C++ program I compiled and ran is called `test_program.cpp` and it calculates the first 200,000 prime numbers.  The program code can be seen below.

```c++
#include <bits/stdc++.h>
#include <iostream>
#include <string>

using namespace std;

bool check_prime(int n) {
    int i;

    // 0 and 1 are not prime numbers
    if (n == 0 || n == 1) {
        return false;
    }
    else {
        for (i = 2; i <= n / 2; ++i) {
            if (n % i == 0) {
                return false;
            }
        }
    }
    
    return true;
}

int main() {
    cout << "Starting..." << endl;
    clock_t start, end; 

    start = clock();
    int LOOP_SIZE = 250000;

    for (int i = 0; i < LOOP_SIZE; i++) {
        bool is_prime = check_prime(i);
    }

    end = clock();
    cout << "Done." << endl;

    double time_taken = double(end - start) / double(CLOCKS_PER_SEC); 
    cout << "Time taken by program is : " << fixed  
         << time_taken << setprecision(5); 
    cout << " sec " << endl;
    return 0;
}
```

The output for Windows:

```
Starting...
Done.
Time taken by program is : 3.493000 sec
```

The output for Ubuntu:

```
Starting...
Done.
Time taken by program is : 3.486613 sec 
```

Both systems had similar runtimes, with Linux being around 0.006387 seconds faster than Windows.