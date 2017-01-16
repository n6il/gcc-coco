/* arlex.c */

/*
 * (C) Copyright 1989,1990
 * All Rights Reserved
 *
 * Alan R. Baldwin
 * 721 Berkeley St.
 * Kent, Ohio  44240
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "aslib.h"



void getid(char *id, int c)
{
   char *p;

   if (c < 0)
      c = getnb();

   p = id;

   do {
      if (p < &id[NCPS])
	  *p++ = c;
   } while (ctype[c=get()] & (LETTER|DIGIT));

   unget(c);

   while (p < &id[NCPS])
      *p++ = 0;
}



void getfid(char *fid, int c)
{
   char *p;

   if (c < 0)
      c = getnb();

   p = fid;

   while (ctype[c] & (LETTER|DIGIT) || c == FSEPX) {
      if (p < &fid[FILSPC-1])
         *p++ = c;

      c = get();
   }

   unget(c);

   while (p < &fid[FILSPC])
      *p++ = 0;
}



int getnb(void)
{
   int c;

   while (((c=get())==' ') || (c=='\t'))
      ;

   return c;
}



void skip(int c)
{
   if (c < 0)
      c = getnb();

   while (ctype[c=get()] & (LETTER|DIGIT))
      ;

   unget(c);
}



int get(void)
{
   int c;

   if ((c = *ip) != 0)
      ++ip;

   return c;
}



void unget(int c)
{
   if (c != 0)
      --ip;
}



int getline(void)
{
   static FILE *sfp = NULL;
   int ret, i;

   ret = 1;

loop:
   if (sfp == NULL || fgets(ib, sizeof(ib), sfp) == NULL) {
      /* close just finished file */
      if (sfp) {
	 fclose(sfp);
	 sfp = NULL;
      }

      /* advance current file */
      if (cfp == NULL)
         cfp = filep;
      else
	 cfp = cfp->f_flp;

      /* open new file */
      if (cfp) {
	 sfp = afile(cfp->f_idp, NULL, 0);
	 ret = 2;
	 goto loop;
      }
      else {
         return 0;
      }
   }

   i = strlen(ib) - 1;
   if (ib[i] == '\n')
      ib[i] = 0;

   return (ret);
}



int more(void)
{
   int c;

   c = getnb();
   unget(c);
   return((c == '\0') || (c == ';') ? 0 : 1);
}



int endline(void)
{
   int c;

   c = getnb();
   return((c == '\0') || (c == ';') ? 0 : c );
}

