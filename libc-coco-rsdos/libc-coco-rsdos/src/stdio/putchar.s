	.module putchar.s
	.area _CODE
	.globl _putchar	; int putchar(unsigned char c)
; Modified from the Thomson version to work on the CoCo
; with Tandy's Disk Extended Color Basic
_putchar:
	lda	2,s	; c -> A
put:
	jsr	[0xA002]	; call "CHROUT" BASIC routine
	cmpa	#10	; LF
	bne	end
	lda	#13	; CR
	bra	put
end:
	clra
	clrb
	rts
