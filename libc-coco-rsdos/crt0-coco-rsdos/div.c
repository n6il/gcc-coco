#include <stdio.h>


int main(void)
{
   int a = -2657;
   int b = 23;

   if ((a/b) != -115)
      puts("test 1: failed");

   if ((a%b) != -12)
      puts("test 2: failed");

   b = - b;

   if ((a/b) != 115)
      puts("test 3: failed");

   if ((a%b) != -12)
      puts("test 4: failed");

   a = -a;

   if ((a/b) != -115)
      puts("test 5: failed");

   if ((a%b) != 12)
      puts("test 6: failed");

   b = 0;
   b = a/b;

   return 0;
}
