/* File: line.c                                                                */
/* CoCo RS-DOS conio implementation © 2003 James Dessart                      */

/* line output for coco conio */

#include "coco_conio.h"
#include "coco_conio_globals.h"

/* Output a horizontal line with the given length starting at the current
 * cursor position.
 */
void  chline (unsigned char length)
{
	int i;
	INIT_VARS();

	page_screen_in();

	for( i=0; i<length; i++ )
	{
		FAST_PUTC('-');
	}

	page_screen_out();
}

void  chlinexy (unsigned char x, unsigned char y, unsigned char length)
{
	gotoxy( x, y );
	chline( length );
}

/* Output a vertical line with the given length at the current cursor
 * position.
 */
void  cvline (unsigned char length)
{
	int i;
	INIT_VARS();
	
	for( i=0; i<length; i++ )
	{
		FAST_PUTC('|');
		gotoxy( --x, ++y );
	}
}

void  cvlinexy (unsigned char x, unsigned char y, unsigned char length)
{
	gotoxy( x, y );
	cvline( length );
}
