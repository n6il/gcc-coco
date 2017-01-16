	.module strcoll.s
	.area _CODE
	.globl _strcoll	; int strcoll(const char *s1, const char *s2)
_strcoll:
	jmp	_strcmp
