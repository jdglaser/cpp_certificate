#include <stdio.h>
#include <string.h>

/*
int main( int argc, char *argv[]) 
{
    char myArr[40];
    char buffer[50];
    strcpy(buffer, argv[1]);
}*/

int main(int argc, char *argv[])
{
    char * myChar ="Testing 123";
    char myArray[10];
    for ( int i =0; i < 2000; i++) {
        myArray[i] = '$';
    }
    char test = myChar[0];
}