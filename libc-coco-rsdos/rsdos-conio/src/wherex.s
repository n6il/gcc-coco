	.module wherex.s
	.area _CODE
	.globl _wherex	; unsigned char wherex (void);
_wherex:
	ldb 0xFE02
	clra
	rts
