/* File: coco_conio_globals.h                                                 */
/* CoCo RS-DOS conio implementation © 2003 James Dessart                      */

/* global variables for coco conio */

extern unsigned char	is_reversed;
extern unsigned char	show_cursor;

extern unsigned char	current_text_colour;
extern unsigned char	current_background_colour;
extern unsigned char	border_colour;

extern unsigned char	screen_mode;

extern unsigned char *current_screen_offset asm("__current_screen_offset");

extern unsigned char translation_table[];

#define	COLOR_MASK(x) (x & 0x7)
#define FG_COLOR_SHIFT(x) (COLOR_MASK(x) << 3)

#define TEXT_PAGE_ADDRESS	0xC000

#define INIT_VARS() unsigned char x, y; \
	unsigned char *attr_loc; \
	x = wherex(); y = wherey();

#define FAST_PUTC(c) \
	attr_loc = TEXT_PAGE_ADDRESS + current_screen_offset + 1; \
	if( c != '\n' && c != '\r' ) { \
		*(TEXT_PAGE_ADDRESS+current_screen_offset)=translation_table[c]; \
		if( is_reversed ) *attr_loc = FG_COLOR_SHIFT(current_background_colour) \
				   + COLOR_MASK(current_text_colour); \
		else *attr_loc = FG_COLOR_SHIFT(current_text_colour) \
				   + COLOR_MASK(current_background_colour); \
		gotox(++x); } \
	else { gotoxy( 0, ++y ); }

#define FAST_PUTC_NO_ATTR(c) \
	attr_loc = TEXT_PAGE_ADDRESS + current_screen_offset + 1; \
	if( c != '\n' && c != '\r' ) { \
		*(TEXT_PAGE_ADDRESS+current_screen_offset)=translation_table[c]; \
		*attr_loc = 0; gotox(++x); } \
	else { gotoxy( 0, ++y ); }

void page_screen_in();
void page_screen_out();
