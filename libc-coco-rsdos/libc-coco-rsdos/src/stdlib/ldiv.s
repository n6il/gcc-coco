	.module ldiv.s
	.area _CODE
	.globl _ldiv	; ldiv_t ldiv(long numer, long denom);
_ldiv:
	jmp	_div
