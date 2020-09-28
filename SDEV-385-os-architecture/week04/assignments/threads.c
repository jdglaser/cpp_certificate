#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

/*

# SDEV 385 Homework Week 4

## Assignment
For this week's homework assignment, write a program that demonstrates what happens to running threads if their process ends before they are finished executing. Demonstrate whether they still run, or what else happens. HINT: You can use threads to write to multiple files to understand what is going on.

## Information
- SDEV 385 Homework Week 4
- Jarred Glaser
- OS: Ubuntu 20.04.1 LTS
- Compiler: gcc versoin 9.3.0 (Ubuntu 9.3.0-10ubuntu2)
- Last Updated: 2020-09-27

## Answer
If the program exits before all threads can complete their processes then the execution is terminated. We can see this in the thread_output.txt file. When the exit 
function is removed from the function, both threads are able to write to the file. However, when the function calls exit, only thread one can complete and the 
program then ends.

*/

void *thefunction(void *ptr);

pthread_mutex_t themutex = PTHREAD_MUTEX_INITIALIZER;
FILE *fp;

int main()

{

  int ithreadone, ithreadtwo;
  pthread_t firstthread, secondthread;

  if( (ithreadone=pthread_create( &firstthread, NULL, &thefunction, "Hello from thread 1!\n")) )

  {
     printf("Thread creation error: %d\n", ithreadone);

  }

  if( (ithreadtwo=pthread_create( &secondthread, NULL, &thefunction, "Hello from thread 2!\n")) )

  {
     printf("Thread creation error: %d\n", ithreadtwo);

  }

 
  pthread_join( firstthread, NULL);
  pthread_join( secondthread, NULL);
  exit(0);
}


void *thefunction(void *ptr)

{
  char *msg = (char *) ptr;
  pthread_mutex_lock( &themutex );

  
  fp = fopen("./thread_output.txt", "a");
  fprintf(fp, "%s", msg);
  fclose(fp);
  pthread_mutex_unlock( &themutex );

  // Calling exit(0) here will cause thread 1 (or whatever thread reaches this first) to exit the program which will end the execution for thread 2
  exit(0);

}