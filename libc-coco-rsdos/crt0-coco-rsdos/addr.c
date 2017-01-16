#include <stdio.h>
#include <stdlib.h>


extern unsigned int __crt0_stack;	/* saved stack                      */
extern unsigned char __crt0_dpage;	/* saved direct page                */

extern int __data_start;	/* start of DATA area               */
extern int __bss_start;		/* start of BSS area                */

extern int _etext;		/* end(+1) of CODE area             */
extern int _edata;		/* end(+1) of DATA area             */
extern int _end;		/* end(+1) of the fixed-sized areas */

int i;				/* un-initialized variable (BSS area) */
int j = 2;			/* initialized variable (DATA area)   */


int main(void)
{
   int k;

   printf("Address of function main       = %04lX\n", (unsigned long)main);
   printf("Address of symbol _etext       = %04lX\n", (unsigned long)&_etext);
   printf("Address of symbol __data_start = %04lX\n", (unsigned long)&__data_start);
   printf("Address of variable j          = %04lX\n", (unsigned long)&j);
   printf("Address of symbol _edata       = %04lX\n", (unsigned long)&_edata);
   printf("Address of symbol __bss_start  = %04lX\n", (unsigned long)&__bss_start);
   printf("Address of variable i          = %04lX\n", (unsigned long)&i);
   printf("Address of symbol _end         = %04lX\n", (unsigned long)&_end);

   printf("Saved value of register S      = %04X\n", __crt0_stack);
   printf("Saved value of register DP     = %02X\n", __crt0_dpage);
   printf("Address of variable k          = %04lX\n", (unsigned long)&k);

   return 0;
}
