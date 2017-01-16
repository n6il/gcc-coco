/* armain.c */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "aslib.h"


static int creation_flag = 0;
static int verbose_level = 0;



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



/* basename:
 *  Strips path from the filename for the linker.
 */
static char *basename(char *filename)
{
   char *p = filename + strlen(filename) - 1;

   while ((p >= filename) && (*p != '/'))
      p--;

   return p+1;
}



/* create_archive:
 *  Creates an empty archive.
 */
static void create_archive(char *filename)
{
   FILE *libf;

   libf = fopen(filename, "w");
   if (!libf) {
      printf("Error: cannot create %s.\n", filename);
      exit(1);
   }

   if (!creation_flag)
      printf("Warning: %s did not exist.\n", filename);

   fprintf(libf, "Lib %s\n", filename);
   fprintf(libf, "End %s\n", filename);
   fclose(libf);
}



/* append:
 *  Appends members to an archive.
 */
static void append(char *arname, struct lfile *memberp)
{
   FILE *libf;
   char line[256];
   char modname[32];
   int ret;

   libf = fopen(arname, "r+");
   if (!libf) {
      create_archive(arname);
      libf = fopen(arname, "r+");
   }

   /* seek 'End' marker */
   while (getc(libf) != 'E')
      fgets(line, 256, libf);

   fseek(libf, -1, SEEK_CUR);

   modname[0] = '\0';
   filep = memberp;
   cfp = NULL;

   while ((ret = getline())) {
      if (ret == 2) {
	 if (*modname)
	    fprintf(libf, "L1 %s\n", modname);

	 strcpy(modname, basename(cfp->f_idp));
	 fprintf(libf, "L0 %s\n", modname);
      }

      fprintf(libf, "%s\n", ib);
   }

   fprintf(libf, "L1 %s\n", modname);
   fprintf(libf, "End %s\n", arname);
   fclose(libf);
}


#define TEMP_FILENAME  "00tmp.a"

/* replace:
 *  Adds members to an archive with replacement or deletes them.
 */
static void replace(char *arname, struct lfile *memberp, int delete)
{
   FILE * libf, *newf = NULL;
   char modname[NCPS];
   char newb[NINPUT];
   char c;
   int i, replaced;

   /* check that the archive exists */
   if ((libf = fopen(arname, "r"))) {
      fclose(libf);
   }
   else {
      if (delete) {
	 printf("Error: cannot open %s.\n", arname);
	 exit(1);
      }
      create_archive(arname);
   }

   filep = new_lfile(arname);

   while (memberp) {
      if (!delete) {
	 newf = fopen(memberp->f_idp, "r");
	 if (!newf) {
	    printf("Error: cannot open %s.\n", memberp->f_idp);
	    exit(1);
	 }
      }

      libf = fopen(TEMP_FILENAME, "w");
      if (!libf) {
	  printf("Error: cannot create temporary file.\n");
	  exit(1);
      }

      replaced = 0;
      cfp = NULL;

      while (getline()) {
	 ip = ib;
	 c = getnb();
	 switch(c) {
	    case 'L':
	       c = getnb();
	       if (c == '0') {
		  getid(modname, -1);

		  /* test whether the module name is the requested one */
		  if (!strcmp(modname, memberp->f_idp)) {
		     if (!delete) {
			fprintf(libf, "%s\n", ib);  /* L0 .. */

			/* copy the contents */
			while (fgets(newb, NINPUT-1, newf)) {
			   i = strlen(newb) - 1;
			   if (newb[i] == '\n')
			      newb[i] = 0;
			   fprintf(libf, "%s\n", newb);
			}

			replaced = 1;
		     }

		     while (getline()) {
			if (ib[1] == '1')
			   break;
		     }

		     if (!delete)
			fprintf(libf, "%s\n", ib);   /* L1 .. */

		     continue;
	          }
	       }

	       fprintf(libf, "%s\n", ib);
	       break;

	    case 'E':
	       if (!delete && !replaced) {
		  strcpy(modname, basename(memberp->f_idp));

		  fprintf(libf, "L0 %s\n", modname);

		  /* copy the contents */
		  while (fgets(newb, NINPUT-1, newf)) {
		     i = strlen(newb) - 1;
		     if (newb[i] == '\n')
		        newb[i] = 0;
		     fprintf(libf, "%s\n", newb);
		  }

		  fprintf(libf, "L1 %s\n", modname);
		  fprintf(libf, "End %s\n", arname);

		  continue;
	      }
	      /* fall through ... */

	    default:
	       fprintf(libf, "%s\n", ib);
	       break;
	 }
      }

      fclose(libf);
      if (!delete)
	 fclose(newf);

      /* replace existing archive by new one */
      remove(arname);
      rename(TEMP_FILENAME, arname);

      memberp = memberp->f_flp;
   }
}



/* name_in_list:
 *  Helper for finding whether a name is present in the list.
 */
static inline int name_in_list(char *name, struct lfile *list)
{
   while (list) {
      if (!strcmp(name, list->f_idp))
	 return 1;

      list = list->f_flp;
   }

   return 0;
}



/* extract:
 *  Extracts members from an archive.
 */
static void extract(char *arname, struct lfile *memberp, int create)
{
   FILE *newf;
   char modname[NCPS];
   char c;

   filep = new_lfile(arname);
   cfp = NULL;

   while (getline()) {
      ip = ib;
      c = getnb();
      switch(c) {
	 case 'L':
	    c = getnb();
	    if (c == '0') {
	       getid(modname, -1);

	       if (!memberp || name_in_list(modname, memberp)) {
		  if (create) {
		     newf = fopen(modname, "w");
		     if (!newf) {
			printf("Error: cannot create %s.\n", modname);
			exit(1);
		     }
		  }
		  else {
		     newf = stdout;
		  }

		  while (getline()) {
		     if (ib[1] == '1')
			break;
		     fprintf(newf, "%s\n", ib);
		  }

		  if (create)
		     fclose(newf);
	       }
	    }
	    break;
      }
   }
}



static char *usetxt[] = {
   "Usage: [-]p[mod [count]...] archive [member...]",
   "  where p must be one of:",
   "    d   delete file(s)",
   "    p   print contents of archive",
   "    q   quick append file(s)",
   "    r   insert file(s) with replacement",
   "    x   extract file(s)",
   "  and mod must be one of:",
   "    c   create new lib",
   "    v   request verbose level",
   NULL
};



static void usage(void)
{
   char **dp;

   fprintf(stderr, "ASxxxx Library Manager %s\n\n", VERSION);
   for (dp = usetxt; *dp; dp++)
      fprintf(stderr, "%s\n", *dp);

   exit(1);
}



int main(int argc, char *argv[])
{
   char *p, *arname = NULL, c;
   struct lfile *lfp = NULL, *memberp = NULL;
   int i, action = 0;

   if (argc < 3)
      usage();

   p = argv[1];
   if (*p == '-')
      p++;

   c = *p++;
   switch (c) {
      case 'd': /* delete */
      case 'p': /* print contents */
      case 'q': /* append */
      case 'r': /* insert and replace */
      case 'x': /* extract */
	 action = c;
	 break;

      default:
	 usage();
   }

   c = *p;
   switch (c) {
      case 'c': /* create */
	 creation_flag = 1;
	 break;

      case 'v':
	 verbose_level = 1;
	 if (*p) {
	    verbose_level = (int)(*p - '0');
	    verbose_level = (verbose_level > 3 ? 3 : verbose_level);
	    verbose_level = (verbose_level < 0 ? 0 : verbose_level);
	 }
	 break;
   }

   for (i=2; i<argc; ++i) {
      p = argv[i];

      if (!arname) {
	 arname = new(strlen(p)+1);
	 strcpy(arname, p);
      }
      else {
	 if (!memberp) {
	    memberp = new_lfile(p);
	    lfp = memberp;
         }
	 else {
	    lfp->f_flp = new_lfile(p);
	    lfp = lfp->f_flp;
	 }
      }
   }

   if (!arname)
      usage();

   if (verbose_level > 0) {
      printf("outputfile: %s \nprocessing files ", arname);
      lfp = memberp;
      while (lfp) {
	 printf("%s ", lfp->f_idp);
	 lfp = lfp->f_flp;
      }

      printf("\nverbosity level %d\n", verbose_level);
   }

   if (action == 'd')
      replace(arname, memberp, 1);
   else if (action == 'p')
      extract(arname, memberp, 0);
   else if (action == 'q')
      append(arname, memberp);
   else if (action == 'r')
      replace(arname, memberp, 0);
   else if (action == 'x')
      extract(arname, memberp, 1);

   return 0;
}
