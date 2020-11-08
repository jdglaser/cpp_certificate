#include <stdio.h>
#include <stdlib.h>

int main (int argc, char *argv[])
{
  int *num = malloc(sizeof(int));
  *num = 5;
  printf("%d",*num);
  free(num);
}