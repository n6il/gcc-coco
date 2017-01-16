; divhi3
; calling ( left % right )
; push right
; push left
; jsr _divhi3

	.module divhi3.s
	.area _CODE
	.globl	_divhi3
_divhi3:
	ldd	2,s
	pshs	d
	ldd	6,s
	bne	do_div		; check dividend
	swi
	.byte	2		; SIGFPE
do_div:
	jsr	_seuclid
	puls	d
	rts
