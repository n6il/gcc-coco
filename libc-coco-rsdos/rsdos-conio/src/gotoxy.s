	.module setxy.s
	.area _CODE
	.globl _gotoxy	; void gotoxy( unsigned char x, unsigned char y )
_gotoxy:
	lda	2,s		; A = x
	ldb	4,s		; B = y
	sta 0xFE02
	stb 0xFE03
	lda #2		; A = 2
	mul			; D = y * 2
	lda 0xFE04	; A = cols, B = y * 2
	mul			; D = cols * y * 2
	tfr d,x		; X = cols * y * 2
	ldb 2,s		; B = x
	lda #2		; A = 2
	mul			; D = x * 2
	stx __current_screen_offset
	addd __current_screen_offset	; D = (x * 2) + (cols * y * 2)
	std __current_screen_offset
	clra
	clrb
	rts
	
	.area _DATA
	.globl __current_screen_offset
__current_screen_offset:
	.word 0
