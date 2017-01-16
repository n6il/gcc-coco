	.module getch.s
	.area _CODE
	.globl _getch	; int getch(void);
_getch:
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
	tfr	a,b
	clra
	puls	y,pc
