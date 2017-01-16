	.module puts.s
	.area _CODE
	.globl _puts	; void puts(const char *s)
; Modified from the Thomson version to work on the CoCo
; with Tandy's Disk Extended Color Basic
_puts:
	pshs	x
	ldx	4,s	; s -> X
loop:
	lda	,x+
	beq	end
	clrb
	stb 0x006F
put:
	jsr	[0xA002]	; call "CHROUT" BASIC routine
	cmpa	#10	; LF
	bne	loop
	lda	#13	; CR
	bra	put
end:
	clra
	clrb
	puls	x,pc
