# Week 7 Discussion

*The stack is a crucial component in memory management. Discuss how the stack is affected when a memory leak or buffer overrun occurs. Some stack constructs that you may want to discuss may include the heap, memory mapping region, kernel space, frame pointer, function addresses. How does Linux (or Windows, if you choose) protect the stack from some of the problems that we discussed?*

In memory management, the stack is the collection of memory used in the function call stack. In C and C++, this usually means any regularly declared variables.  These variables are local to the function and the memory they use is automatically deallocated when the function goes out of scope. For instance, in the below example, memory is allocated for `num` in `main`, `new_num` in `main`, and `num` in the `addTwo` function parameter list. When addTwo is finished, `num` is deallocated. When `main` is finished (the program finishes), `num` and `new_num` are deallocated. 

```c++
#include <stdio.h>

int addTwo(int num) {
    return num+2;
}

int main (int argc, char *argv[])
{
  int num = 5;
  int new_num = addTwo(num);
}
```

The heap stores global variables that can be accessed outside the scope of a function. This memory is not always in adjacent blocks, and is not managed automatically. Many languages have garbage collection features to deallocate memory that was allocated to the heap, but is no longer being used. However, in lower level languages like, C, this usually has to be manually managed. In the below example we use `malloc` to allocate memory for a variable to the heap. Notice how we need to use `free` to ensure that we free the memory, since, unlike the stack, there is no guarentee this will be done for us.

```c++
#include <stdio.h>
#include <stdlib.h>

int main (int argc, char *argv[])
{
  int *num = malloc(sizeof(int));
  *num = 5;
  printf("%d",*num);
}
```

Different type of problems can occur with memory management when using the stack vs. the heap. With data in the heap, we could run into a memory leak, where we may forget to call `free()` on a variable, and thus have memory being held in the heap that serves no purpose. With data in the stack, we get the advantage of having our data managed for us, however size in the stack is more limited than in the heap. Therefore, it is possible to attempt to allocate too much data to the stack causing a stack overflow error.

A buffer overflow error is similar to a stack overflow error. A buffer is a block of memory used in I/O to hold data while it is being transferred. If data is input that is larger than the size of the buffer, then a buffer overflow error occurs. In the below example, we can see that the input from the user (the buffer) is expected to be no larger than 10 characters in length. If the user enters a name longer than 10 characters, they will get a buffer overflow error.

```c++
#include<stdio.h>
void get_name(){
  char buffer[10];
  gets(buffer);
}
int main() {
    printf("Please enter your name.");
    get_name();
    return 0;
}
```

A similar error occurs in one of the code snippets from our lab:

```c++
int main(int argc, char *argv[])
{
    char * myChar ="Testing 123";
    char myArray[10];
    for ( int i =0; i < 2000; i++) {
        myArray[i] = '$';
    }
    char test = myChar[0];
}
```

This time, we try to access memory that is outside the bounds of `myArray`.  In both cases, an error is raised with the message:

```
*** stack smashing detected ***: terminated
Aborted (core dumped)
```

This message comes from a security mechanism in the gcc compiler (default linux compiler) called a canary. A canary is a randomly generated value that the compiler looks for at the end of the stack or buffer. If a buffer or stack overflow error happens, then this value will be overwritten. The compiler will compare the canary to what it expects, see that it is different, and throw the exception. This helps to protect against stack overflow and buffer overflow issues.


**References**

(2020). 7. Memory: Stack vs Heap. Retreieved from https://gribblelab.org/CBootCamp/7_Memory_Stack_vs_Heap.html

(2020). Stack vs Heap: Know the Difference. Retreived from https://www.guru99.com/stack-vs-heap.html.

(2020). 7.9 - The stack and the heap. Retreived from https://www.learncpp.com/cpp-tutorial/79-the-stack-and-the-heap/

(2020). What is a buffer in C? Retreived from https://www.educative.io/edpresso/what-is-a-buffer-in-c.

(2020). What is the "stack smashing detected" error? Retreived from https://www.educative.io/edpresso/what-is-the-stack-smashing-detected-error.

