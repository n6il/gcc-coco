; umodhi3
; calling ( left % right )
; push right
; push left
; jsr _umodhi3

	.module umodhi3.s
	.area	_CODE
	.globl	_umodhi3
_umodhi3:
	ldd	2,s
	pshs	d
	ldd	6,s
	bne	do_umod		; check dividend
	swi
	.byte	2		; SIGFPE
do_umod:
	jsr	_euclid
	leas	2,s
	rts
