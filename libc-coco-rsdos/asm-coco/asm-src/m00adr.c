/* m00adr.c */

/*
 * (C) Copyright 1989,1990
 * All Rights Reserved
 *
 * Alan R. Baldwin
 * 721 Berkeley St.
 * Kent, Ohio  44240
 */

#include <stdio.h>
#include <setjmp.h>
#include "asm.h"
#include "m6800.h"

int
addr(esp)
register struct expr *esp;
{
	register c;

	if ((c = getnb()) == '#') {
		expr(esp, 0);
		esp->e_mode = S_IMMED;
	} else if (c == ',') {
		esp->e_mode = S_INDX;
		esp->e_flag = 0;
		esp->e_addr = 0;
		esp->e_base.e_ap = NULL;
		if (admode(abx) != S_X)
			aerr();
	} else if (c == '*') {
		expr(esp, 0);
		esp->e_mode = S_DIR;
		if (esp->e_addr & ~0xFF)
			err('d');
		if (more()) {
			comma();
			esp->e_mode = S_INDX;
			if (admode(abx) != S_X)
				aerr();
		}
	} else {
		unget(c);
		if ((esp->e_mode = admode(abx)) != 0) {
			;
		} else {
			expr(esp, 0);
			if (more()) {
				comma();
				esp->e_mode = S_INDX;
				if (admode(abx) != S_X)
					aerr();
				if ((!esp->e_flag)
					&& (esp->e_base.e_ap==NULL)
					&& (esp->e_addr & ~0xFF))
					aerr();
			} else {
				if ((!esp->e_flag)
					&& (esp->e_base.e_ap==NULL)
					&& !(esp->e_addr & ~0xFF)) {
					esp->e_mode = S_DIR;
				} else {
					esp->e_mode = S_EXT;
				}
			}
		}
	}
	return (esp->e_mode);
}
	
/*
 * Enter admode() to search a specific addressing mode table
 * for a match. Return the addressing value on a match or
 * zero for no match.
 */
int
admode(sp)
register struct adsym *sp;
{
	register char *ptr;
	register int i;
	unget(getnb());
	i = 0;
	while ( *(ptr = (char *) &sp[i]) ) {
		if (srch(ptr)) {
			return(sp[i].a_val);
		}
		i++;
	}
	return(0);
}

/*
 *      srch --- does string match ?
 */
int
srch(str)
register char *str;
{
	register char *ptr;
	ptr = ip;

#if	CASE_SENSITIVE
	while (*ptr && *str) {
		if(*ptr != *str)
			break;
		ptr++;
		str++;
	}
	if (*ptr == *str) {
		ip = ptr;
		return(1);
	}
#else
	while (*ptr && *str) {
		if(ccase[*ptr] != ccase[*str])
			break;
		ptr++;
		str++;
	}
	if (ccase[*ptr] == ccase[*str]) {
		ip = ptr;
		return(1);
	}
#endif

	if (!*str)
		if (any(*ptr," \t\n,];")) {
			ip = ptr;
			return(1);
		}
	return(0);
}

/*
 *      any --- does str contain c?
 */
int
any(c,str)
char    c, *str;
{
	while (*str)
		if(*str++ == c)
			return(1);
	return(0);
}

struct adsym	abx[] = {	/* a, b, or x registers */
	"a",	S_A,
	"b",	S_B,
	"x",	S_X,
	"",	0x00
};
