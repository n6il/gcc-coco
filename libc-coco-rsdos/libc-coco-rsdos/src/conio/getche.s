	.module getche.s
	.area _CODE
	.globl _getche	; int getche(void);
_getche:
	ldb	___ungetched_char
	beq	read_key
	clra
	sta	___ungetched_char
	rts
read_key:
	pshs	y
loop:	
	jsr	[0xA000]  ; call POLCAT
	beq	loop
	pshs	a
	jsr	_putchar
	puls	a
	tfr	a,b
	clra
	puls	y,pc
