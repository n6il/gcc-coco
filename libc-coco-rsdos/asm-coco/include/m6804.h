/* m6804.h */

/*
 * (C) Copyright 1989,1990
 * All Rights Reserved
 *
 * Alan R. Baldwin
 * 721 Berkeley St.
 * Kent, Ohio  44240
 */

/*)BUILD
	$(PROGRAM) =	AS6804
	$(INCLUDE) = {
		ASM.H
		M6804.H
	}
	$(FILES) = {
		M04EXT.C
		M04MCH.C
		M04ADR.C
		M04PST.C
		ASMAIN.C
		ASLEX.C
		ASSYM.C
		ASSUBR.C
		ASEXPR.C
		ASDATA.C
		ASLIST.C
		ASOUT.C
	}
	$(STACK) = 2000
*/

struct adsym
{
	char	a_str[2];	/* addressing string */
	int	a_val;		/* addressing mode value */
};

/*
 * Addressing types
 */
#define	S_IMMED	30
#define	S_DIR	31
#define	S_IX	32
#define	S_IY	33

/*
 * Instruction types
 */
#define	S_INH	60
#define	S_BRA	61
#define	S_TYP1	62
#define	S_TYP2	63
#define	S_TYP3	64
#define	S_CLR	65
#define	S_LD	66
#define	S_MVI	67
#define	S_APOST	68
#define	S_BPM	69
#define	S_BXPM	70
#define	S_BYPM	71
#define	S_BTB	72
#define	S_BSC	73

/*
 * Set Direct Pointer
 */
#define	S_SDP	80


	/* machine dependent functions */

	/* m04adr.c */
extern	struct	adsym	xy[];
extern	int		addr();
extern	int		admode();
extern	int		any();
extern	int		srch();

	/* m04mch.c */
extern	VOID		machin();
extern	VOID		minit();
extern	VOID		comma();
