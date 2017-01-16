	.module kbhit.s
	.area _CODE
	.globl _kbhit	; int kbhit(void);
_kbhit:
	pshs y
	jsr	[0xA000]  ; call POLCAT
	beq	no_key
	clra
	ldb	#1
	puls y,pc
no_key:
	clrb
	puls y,pc
