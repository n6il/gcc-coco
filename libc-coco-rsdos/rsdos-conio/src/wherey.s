	.module wherey.s
	.area _CODE
	.globl _wherey	; unsigned char wherey (void);
_wherey:
	ldb 0xFE03
	clra
	rts
