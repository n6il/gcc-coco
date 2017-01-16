	.module movedata.s
	.area _CODE
	.globl _movedata
_movedata:
	cmpu	#0	; leau does not modify cc
	beq	end
	leau	-1,u
	lda	,y+
	sta	,x+
	bra	_movedata
end:
	rts
