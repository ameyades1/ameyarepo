#include <stdio.h>

int main()
{
  const int i = 10;
  int *ptr;
  printf("i = %d\n", i);
  ptr = (int *)(&i);
  *ptr = 15;
  
  printf("i = %d\n", i);
  return 0;
}
