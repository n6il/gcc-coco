/* m6805.h */

/*
 * (C) Copyright 1989,1990
 * All Rights Reserved
 *
 * Alan R. Baldwin
 * 721 Berkeley St.
 * Kent, Ohio  44240
 */

/*)BUILD
	$(PROGRAM) =	AS6805
	$(INCLUDE) = {
		ASM.H
		M6805.H
	}
	$(FILES) = {
		M05EXT.C
		M05MCH.C
		M05ADR.C
		M05PST.C
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
#define	S_EXT	32
#define	S_IX	33
#define	S_I8X	34
#define	S_INDX	35
#define	S_A	36
#define	S_X	37

/*
 * Instruction types
 */
#define	S_INH	60
#define	S_BRA	61
#define	S_TYP1	62
#define	S_TYP2	63
#define	S_TYP3	64
#define	S_TYP4	65

/*
 * Set Direct Pointer
 */
#define	S_SDP	80


	/* machine dependent functions */

	/* m05adr.c */
extern	struct	adsym	ax[];
extern	int		addr();
extern	int		admode();
extern	int		any();
extern	int		srch();

	/* m05mch.c */
extern	VOID		machin();
extern	VOID		minit();
extern	VOID		comma();
