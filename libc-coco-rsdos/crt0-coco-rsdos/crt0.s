	.module crt0.s		; default startup module
	.area	_CODE
	.globl	start
start:
	sts	___crt0_stack	; save S (stack) register
	tfr	dp,a
	sta	___crt0_dpage	; save DP (direct page) register
	ldx	0x602F
	stx	___sig_vector	; save SWI default vector
	ldx	#sig_dispatcher
	stx	0x602F		; hook up SWI
	jsr _main		; call C main() entry point
	pshs	b,a		; save main() return value
	.globl ___exit
___exit:
	ldx	#___exit_func
	lda	___exit_count
	beq	end
loop_func:
	deca
	pshs	a
	asla			; array of pointers (2 bytes)
	jsr	[a,x]		; (*func[i])()
	puls	a
	tsta
	bne	loop_func
end:
	ldx	___sig_vector
	stx	0x602F		; restore SWI default vector
	lda	___crt0_dpage
	tfr	a,dp		; restore DP register
	puls	a,b		; restore main() return value
	lds	___crt0_stack	; restore S register
	rts
sig_dispatcher:			; signal dispatching function
	ldx	#___sig_vector
	ldb	[10,s]		; read signal index number
	aslb			; array of pointers (2 bytes)
	ldx	b,x
	cmpx	#0xFFFF		; SIG_IGN (signal ignored)
	beq	sig_end
	clra
	asrb
	pshs	b,a		; pass signal index number
	jsr	,x
	leas 2,s
sig_end:
	ldd	10,s
	addd	#1		; skip index number in code
	std	10,s
	rti
mesg:
	.asciz	"Shutting down due to signal #0"
	.globl	___sig_handler	; default signal handler
___sig_handler:
	lda	3,s		; read signal index number
	adda	#48		; A = A + '0'
	ldx	#mesg
	sta	29,x		; modify index number in message
	pshs	x
	jmp	end		; shut down program
	.globl	___main
___main:			; post main() prologue callback
	rts

	.area	_DATA
	.globl	___data_start
___data_start:
	.globl ___exit_count
___exit_count:			; num of registered exit functions
	.byte	0
	.globl	___sig_vector
___sig_vector:
	.word	0		; saved default vector
	.word	___sig_handler	; 6 ANSI C signal vectors
	.word	___sig_handler
	.word	___sig_handler
	.word	___sig_handler
	.word	___sig_handler
	.word	___sig_handler

	.area	_BSS
	.globl	___bss_start
___bss_start:
	.globl	___crt0_stack
___crt0_stack:			; saved stack register
	.blkb	2
	.globl	___crt0_dpage
___crt0_dpage:			; saved direct page register
	.blkb	1
	.globl	___exit_func
___exit_func:			; at most 16 registered exit functions
	.blkw	16		; (ANSI C requires at least 32)
