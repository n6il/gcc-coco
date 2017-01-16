/* armem.c */

/*
 * (C) Copyright 1989,1990
 * All Rights Reserved
 *
 * Alan R. Baldwin
 * 721 Berkeley St.
 * Kent, Ohio  44240
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "aslib.h"



void *new(unsigned int n)
{
   char *p;

   p = (char *)calloc(n, sizeof(char));
   if (!p) {
      fprintf(stderr, "Error: out of space!\n");
      exit(1);
   }

   return p;
}



struct lfile *new_lfile(char *filename)
{
   struct lfile *lfilep;

   lfilep = (struct lfile *)new(sizeof(struct lfile));
   lfilep->f_idp = (char *)new(strlen(filename)+1);
   strcpy(lfilep->f_idp, filename);

   return lfilep;
}
