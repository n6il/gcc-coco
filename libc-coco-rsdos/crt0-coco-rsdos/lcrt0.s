	.module lcrt0.s		; light startup module
	.area	_CODE
	.globl	start
start:
	jmp _main
	.globl	___main
___main:			; post main() prologue callback
	rts

	.area	_DATA
	.globl	___data_start
___data_start:

	.area	_BSS
	.globl	___bss_start
___bss_start:
