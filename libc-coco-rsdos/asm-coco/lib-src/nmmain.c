/* nmmain.c */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "aslib.h"



/* afile:
 *  Helper for opening a file.
 */
FILE* afile(char *fn, char *ft, int wf)
{
   FILE *fp;
   char fb[FILSPC];

   strcpy(fb, fn);
   if (ft) {
      strcat(fb, ".");
      strcat(fb, ft);
   }

   if (!(fp = fopen(fb, wf ? "w":"r"))) {
      fprintf(stderr, "Error: cannot %s %s.\n", wf ? "create":"open", fb);
      exit(1);
   }

   return fp;
}



/* dump:
 *  Dumps the contents of the archive on stdin.
 */
static void dump(struct lfile *objp)
{
   char modname[32];
   char area[32];
   char label[32];
   char type, c, t;
   unsigned int val, val2;

   filep = objp;
   cfp = NULL;

   modname[0] = '\0';
   area[0] = '\0';
   label[0] = '\0';

   while (getline()) {
      ip = ib;
      c = getnb();
      switch (c) {
	 case 'S':
	    sscanf(ib, "S %s %cef%x", label, &type, &val);
	    if (type == 'D') {
	       if (!strcmp(area, "_CODE"))
		  t = 'T';
	       else if (!strcmp(area, "_DATA"))
		  t = 'D';
	       else if (!strcmp(area, "_BSS"))
		  t = 'B';
	       else
	          t = '?';
	    }
	    else {
	       t = 'U';
	    }

	    printf("%04x %c %s\n", val & 0x0ffff, t, label);
	    break;

	 case 'A':
	    sscanf(ib, "A %s size %x flags %x\n", area, &val, &val2);
	    break;

	 case 'H':
	    break;

	 case 'M':
	    break;

	 case 'L':
	    c = getnb();
	    if (c == '0') {
	       getid(modname, -1);
	       printf("\n%s:\n", modname);
	    }
	    break;
      }
   }
}


static char *usetxt[] = {
   "Usage: objfile...",
   NULL
};



static void usage(void)
{
   char **dp;

   fprintf(stderr, "ASxxxx Object file Lister %s\n\n", VERSION);
   for (dp = usetxt; *dp; dp++)
      fprintf(stderr, "%s\n", *dp);

   exit(1);
}



int main(int argc, char *argv[])
{
   struct lfile *lfp = NULL, *objp = NULL;
   char *p, c;
   int i;

   if (argc < 2)
      usage();

   for (i=1; i<argc; ++i) {
      p = argv[i];

      if (*p == '-') {
	 c = *++p;
	 switch (c) {
	    default:
	       usage();
         }
      }
      else {
	 if (!objp) {
	    objp = new_lfile(p);
	    lfp = objp;
         }
	 else {
	    lfp->f_flp = new_lfile(p);
	    lfp = lfp->f_flp;
	 }
      }
   }

   if (!objp)
      usage();

   dump(objp);

   return 0;
}
