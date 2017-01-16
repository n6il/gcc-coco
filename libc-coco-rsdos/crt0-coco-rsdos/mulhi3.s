;	signed/unsigned multiply
;	calling (left * right)
;	push left
;	push right
;	jsr _mulhi3
;	result in d, stack not popped
	.module mulhi3.s
	.area _CODE
	.globl _mulhi3

_mulhi3:
	pshs	x
	ldx	#0
	ldb	6,s	; left msb * right lsb * 256
	lda	5,s
	mul
	tfr	b,a
	clrb
	leax	d,x
	ldb	7,s	; left lsb * right msb * 256
	lda	4,s
	mul
	tfr	b,a
	clrb
	leax	d,x
	ldb	7,s	; left lsb * right lsb
	lda	5,s
	mul
	leax	d,x
	tfr	x,d
	puls	x
	rts
