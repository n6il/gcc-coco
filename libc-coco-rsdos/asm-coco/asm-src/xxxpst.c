/* xxxpst.c */

/*
 * (C) Copyright 1989,1990
 * All Rights Reserved
 *
 * Alan R. Baldwin
 * 721 Berkeley St.
 * Kent, Ohio  44240
 */

#include <stdio.h>
#include <setjmp.h>
#include "asm.h"
#include "yyyy.h"

struct	mne	mne[] = {

	/* machine */

	/* system */

	NULL,	"CON",		S_ATYP,		0,	A_CON,
	NULL,	"OVR",		S_ATYP,		0,	A_OVR,
	NULL,	"REL",		S_ATYP,		0,	A_REL,
	NULL,	"ABS",		S_ATYP,		0,  A_ABS|A_OVR,
	NULL,	"NOPAG",	S_ATYP,		0,	A_NOPAG,
	NULL,	"PAG",		S_ATYP,		0,	A_PAG,

	NULL,	".byte",	S_BYTE,		0,	0,
	NULL,	".db",		S_BYTE,		0,	0,
	NULL,	".word",	S_WORD,		0,	0,
	NULL,	".dw",		S_WORD,		0,	0,
	NULL,	".ascii",	S_ASCII,	0,	0,
	NULL,	".asciz",	S_ASCIZ,	0,	0,
	NULL,	".blkb",	S_BLK,		0,	1,
	NULL,	".ds",		S_BLK,		0,	1,
	NULL,	".blkw",	S_BLK,		0,	2,
	NULL,	".page",	S_PAGE,		0,	0,
	NULL,	".title",	S_TITLE,	0,	0,
	NULL,	".sbttl",	S_SBTL,		0,	0,
	NULL,	".globl",	S_GLOBL,	0,	0,
	NULL,	".area",	S_DAREA,	0,	0,
	NULL,	".even",	S_EVEN,		0,	0,
	NULL,	".odd",		S_ODD,		0,	0,
	NULL,	".if",		S_IF,		0,	0,
	NULL,	".else",	S_ELSE,		0,	0,
	NULL,	".endif",	S_ENDIF,	0,	0,
	NULL,	".include",	S_INCL,		0,	0,
	NULL,	".radix",	S_RADIX,	0,	0,
	NULL,	".org",		S_ORG,		0,	0,
	NULL,	".module",	S_MODUL,	0,	0,

	/* machine */

	NULL,	"?",		?,		S_END,	?
};
