;	signed euclidean division
;	calling: (left / right)
;		push left
;		ldd right
;		jsr _seuclid
;	quotient on the stack (left)
;	modulus in d

	.module seuclid.s
	.area	_CODE
	.globl	_seuclid
	left=6
	right=2
	quot_sign=1
	mod_sign=0
_seuclid:
	leas	-4,s		; 3 local variables
	std	right,s
	clr	mod_sign,s
	clr	quot_sign,s
	ldd	left,s
	bge	mod_abs
	inc	mod_sign,s	; sign(mod) = sign(left)
	inc	quot_sign,s
	bsr	negd		; abs(left) -> D
mod_abs:
	pshs	b,a		; push abs(left)
	ldd	right+2,s	; all references shifted by 2
	bge	quot_abs
	dec	quot_sign+2,s	; sign(quot) = sign(left) XOR sign(right)
	bsr	negd		; abs(right) -> D
quot_abs:
	jsr	_euclid		; call (unsigned) euclidean division
	std	right+2,s
	puls	a,b		; quot -> D
	tst	quot_sign,s	; all references no longer shifted
	beq	quot_done
	bsr	negd
quot_done:
	std	left,s		; quot -> left
	ldd	right,s
	tst	mod_sign,s
	beq	mod_done
	bsr	negd
mod_done:
	leas	4,s		; destroy stack frame
	rts

negd:				; self-explanatory !
	nega
	negb
	sbca	#0
	rts
