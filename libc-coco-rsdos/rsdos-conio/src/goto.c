/* File: goto.c                                                               */
/* CoCo RS-DOS conio implementation © 2003 James Dessart                      */

/* gotox and gotoy */

#include "coco_conio.h"

void  gotox (unsigned char x)
{
	unsigned char y = wherey();
	
	gotoxy( x, y );
}

void  gotoy (unsigned char y)
{
	unsigned char x = wherex();
	
	gotoxy( x, y );
}
