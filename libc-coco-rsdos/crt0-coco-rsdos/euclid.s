;	unsigned euclidean division
;	calling: (left / right)
;		push left
;		ldd right
;		jsr _euclid
;	quotient on the stack (left)
;	modulus in d

	.module euclid.s
	.area	_CODE
	.globl	_euclid
	left=5
	right=1			; word
	count=0			; byte
	CARRY=1			; alias
_euclid:
	leas	-3,s		; 2 local variables
	clr	count,s		; prescale divisor
	inc	count,s
	tsta
presc:
	bmi	presc_done
	inc	count,s
	aslb
	rola
	bra	presc
presc_done:
	std	right,s
	ldd	left,s
	clr	left,s		; quotient = 0
	clr	left+1,s
mod1:
	subd	right,s		; check subtract
	bcc	mod2
	addd	right,s
	andcc	#~CARRY
	bra	mod3
mod2:
	orcc	#CARRY
mod3:
	rol	left+1,s	; roll in carry
	rol	left,s
	lsr	right,s
	ror	right+1,s
	dec	count,s
	bne	mod1
	leas	3,s
	rts
