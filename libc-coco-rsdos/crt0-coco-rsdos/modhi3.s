; modhi3
; calling ( left % right )
; push right
; push left
; jsr _modhi3

	.module modhi3.s
	.area	_CODE
	.globl	_modhi3
_modhi3:
	ldd	2,s
	pshs	d
	ldd	6,s
	bne	do_mod		; check dividend
	swi
	.byte	2		; SIGFPE
do_mod:
	jsr	_seuclid
	leas	2,s
	rts
