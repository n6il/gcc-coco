	.module remove.s
	.area _CODE
	.globl _remove	; int remove(const char *filename);
_remove:
	jmp	_unlink
