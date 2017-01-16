/* File: init.c                                                               */
/* CoCo RS-DOS conio implementation © 2003 James Dessart                      */

/* screen initialization functions */

#include "coco_conio.h"
#include "coco_conio_globals.h"
#include "coco3.h"

#define HIRES_TEXT_PAGE		54
#define PAGE_REGISTER_MASK	0x3F
#define VALUE_80_X_24_RES	0x15
#define VALUE_40_X_24_RES	0x05

static unsigned char previous_page;
static unsigned char previous_init;

void init_screen( unsigned char width )
{
	unsigned char vid_mode_value;

	/* setup palette*/
	
	
	/* enable MMU and put machine into CoCo 3 mode */
	/* and turn off interrupts */
	*INIT_REGISTER = 0x4C;
	
	vid_mode_value = *VID_MODE_REGISTER;
	*VID_MODE_REGISTER = 0x03;
	
	screen_mode = width;
	
	/* locate hires text screen*/
	/* it's in page 54... so the address is 0x6C000 */
	/* so we divide 0x6C000 by 8... we get 0xD800 */
	*VERTICAL_OFFSET_REGISTER_1 = 0xD8;
	*VERTICAL_OFFSET_REGISTER_2 = 0x00;
	
	switch( screen_mode )
	{
		case CONIO_40_x_24_SCREEN:
			*VID_RES_REGISTER = VALUE_40_X_24_RES;
			break;

		case CONIO_80_x_24_SCREEN:
			*VID_RES_REGISTER = VALUE_80_X_24_RES;
			break;
	}
	
	/* clear screen */
	clrscr();
}

void page_screen_in()
{
	previous_page = (*TEXT_PAGE_REGISTER) & PAGE_REGISTER_MASK;
	(*TEXT_PAGE_REGISTER) = HIRES_TEXT_PAGE;
}

void page_screen_out()
{
	(*TEXT_PAGE_REGISTER) = previous_page;
}

