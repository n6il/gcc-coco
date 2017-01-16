	.module srand.s
	.area _CODE
	.globl _srand	; void srand(int seed)
_srand:
	ldd	2,s	; seed -> D
	std	___random_seed
	rts
