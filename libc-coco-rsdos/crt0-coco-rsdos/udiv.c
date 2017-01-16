#include <stdio.h>


int main(void)
{
   unsigned int a = 55147U;
   unsigned int b = 17U;

   if ((a/b) != 3243U)
      puts("test 1: failed");

   if ((a%b) != 16U)
      puts("test 2: failed");

   b = 0;
   b = a%b;

   return 0;
}
