	.module memset.s
	.area _CODE
	.globl _memset	; void *memset(void *s, unsigned char c, size_t n)
_memset:
	pshs	u,x
	ldx	6,s	; s -> X
	lda	8,s	; c -> A
	ldu	9,s	; n -> U
loop:
	cmpu	#0	; leau does not modify cc
	beq	end
	leau	-1,u
	sta	,x+
	bra	loop
end:
	ldd	6,s
	puls	x,u,pc
