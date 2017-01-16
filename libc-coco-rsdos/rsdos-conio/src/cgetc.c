/* File: cgetc.c                                                              */
/* CoCo RS-DOS conio implementation © 2003 James Dessart                      */

/* cgetc implementation - simply calls getch */

#include <conio.h>
#include "coco_conio.h"

char cgetc()
{
	return (char)getch();
}
