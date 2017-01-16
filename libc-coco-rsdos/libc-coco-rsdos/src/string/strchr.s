	.module strchr.s
	.area _CODE
	.globl _strchr	; char *strchr(const char *s, unsigned char c);
_strchr:
	pshs	x
	ldx	4,s	; s -> X
	lda	6,s	; c -> A
loop:
	cmpa	,x
	beq	found
	tst	,x+
	bne	loop
	clra
	clrb
	puls	x,pc
found:
	tfr	x,d
	puls	x,pc
