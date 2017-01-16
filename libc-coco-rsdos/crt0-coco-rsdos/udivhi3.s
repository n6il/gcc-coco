; udivhi3
; calling ( left % right )
; push right
; push left
; jsr _udivhi3

	.module udivhi3.s
	.area	_CODE
	.globl	_udivhi3
_udivhi3:
	ldd	2,s
	pshs	d
	ldd	6,s
	bne	do_udiv		; check dividend
	swi
	.byte	2		; SIGFPE
do_udiv:
	jsr	_euclid
	puls	d
	rts
