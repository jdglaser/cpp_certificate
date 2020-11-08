#include <string>
#include <iostream>
#include <libgen.h>
#include <unistd.h>

using namespace std;

int main() {
    rename("./move","./tests/move");
}