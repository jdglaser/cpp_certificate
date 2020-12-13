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