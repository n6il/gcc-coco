	.module abort.s
	.area _CODE
	.globl _abort	; void abort(void)
_abort:
	swi
	.byte	1	; SIGABRT
	rts
