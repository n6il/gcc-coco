/* aslib.h */
#include <stdio.h>

#define VERSION "v0.2"

#define FSEPX '.'

/*
 * Case Sensitivity Flag
 */
#define CASE_SENSITIVE 1

/*
 * This file defines the format of the
 * relocatable binary file.
 */
#define NCPS    32    /* characters per symbol */
#define NINPUT  128   /* Input buffer size */
#define FILSPC  255   /* File spec length */

struct lfile
{
   int f_type;   /* File type */
   char *f_idp;  /* Pointer to file spec */
   struct lfile *f_flp;  /* lfile link */
};

extern char *ip;
extern char ib[NINPUT];
extern char ctype[];

#ifndef	CASE_SENSITIVE
extern char ccase[];
#endif

#define	SPACE	0000
#define ETC	0000
#define	LETTER	0001
#define	DIGIT	0002
#define	BINOP	0004
#define	RAD2	0010
#define	RAD8	0020
#define	RAD10	0040
#define	RAD16	0100
#define	ILL	0200

#define	DGT2	DIGIT|RAD16|RAD10|RAD8|RAD2
#define	DGT8	DIGIT|RAD16|RAD10|RAD8
#define	DGT10	DIGIT|RAD16|RAD10
#define	LTR16	LETTER|RAD16

extern struct lfile *filep;
extern struct lfile *cfp;

extern int get();
extern void getfid();
extern void getid();
extern int getline();
extern int getnb();
extern int more();
extern void skip();
extern void unget();
extern FILE *afile(char *fn, char *ft, int wf);
extern int getline();
extern int endline();

extern void *new(unsigned int);
extern struct lfile *new_lfile(char *filename);
