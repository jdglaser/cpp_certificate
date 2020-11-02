#include <stdio.h>

int main () {
    int res = rename("./test.txt", "./hello/test2.txt");
    printf("%d",res);
}