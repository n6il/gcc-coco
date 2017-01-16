	.module exit.s
	.area _CODE
	.globl _exit	; void exit(int status)
_exit:
	leas	2,s	; eat saved PC
	jmp	___exit
