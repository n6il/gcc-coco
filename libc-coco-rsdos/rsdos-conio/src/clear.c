/* File: clear.c                                                              */
/* CoCo RS-DOS conio implementation © 2003 James Dessart                      */

/* screen clearing functions */

#include "coco_conio.h"
#include "coco_conio_globals.h"

#define DEFAULT_ROWS		24

void clrscr (void)
{
	unsigned int screen_width;
	unsigned int i;

	INIT_VARS();

	page_screen_in();
	
	switch( screen_mode )
	{
		case CONIO_40_x_24_SCREEN:
			screen_width = 40;
			break;

		case CONIO_80_x_24_SCREEN:
			screen_width = 80;
			break;
	}
	
	for( i=0; i<(screen_width*DEFAULT_ROWS); i++ )
	{
		FAST_PUTC_NO_ATTR(' ');
	}
	
	gotoxy( 0, 0 );
	
	page_screen_out();
}

void  cclear (unsigned char length)
{
	int i;

	INIT_VARS();

	page_screen_in();
	
	for( i=0; i<length; i++ )
	{
		FAST_PUTC_NO_ATTR(' ');
	}
	
	page_screen_out();
}

void  cclearxy (unsigned char x, unsigned char y, unsigned char length)
{
	gotoxy( x, y );
	
	cclear( length );
}
