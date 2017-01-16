/* File: coco_conio_state.c                                                 */
/* CoCo RS-DOS conio implementation © 2003 James Dessart                      */

/* global variable manipulation for coco conio */

#include <coco_conio.h>
#include "coco_conio_globals.h"
#include "coco3.h"

void  screensize (unsigned char* x, unsigned char* y)
{
	*y = 24;

	switch(screen_mode)
	{
		case CONIO_80_x_24_SCREEN:
			*x = 80;
			break;

		case CONIO_40_x_24_SCREEN:
			*x = 40;
			break;
	}
}

/* If onoff is 1, a cursor is display when waiting for keyboard input. If
 * onoff is 0, the cursor is hidden when waiting for keyboard input. The
 * function returns the old cursor setting.
 */
unsigned char  cursor (unsigned char onoff)
{
	/* does nothing for now... */
	unsigned char temp = show_cursor;
	show_cursor = onoff;
	return temp;
}

/* Enable/disable reverse character display. This may not be supported by
 * the output device. Return the old setting.
 */
unsigned char  revers (unsigned char onoff)
{
	unsigned char temp = is_reversed;
	
	is_reversed = onoff;
	
	return temp;
}

/* Set the color for text output. The old color setting is returned. */
unsigned char  textcolor (unsigned char color)
{
	unsigned char temp = current_text_colour;
	
	current_text_colour = color;
	
	return temp;
}

/* Set the color for the background. The old color setting is returned. */
unsigned char  bgcolor (unsigned char color)
{
	unsigned char temp = current_background_colour;
	
	current_background_colour = color;
	
	return temp;
}

/* Set the color for the border. The old color setting is returned. */
unsigned char  bordercolor (unsigned char color)
{
	unsigned char temp = *BORDER_LOCATION;
	
	*BORDER_LOCATION = color;

	return temp;
}
