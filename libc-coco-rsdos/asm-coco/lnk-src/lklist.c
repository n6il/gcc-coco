/* lklist.c */

/*
 * (C) Copyright 1989,1990
 * All Rights Reserved
 *
 * Alan R. Baldwin
 * 721 Berkeley St.
 * Kent, Ohio  44240
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
/* #include <alloc.h> */
#include "aslink.h"

/*
 * Area Map Output
 */
VOID
lstarea(rp)
struct area *rp;
{
	/* register struct area *op; */
	register struct areax *oxp;
	register int c, i, j;
	register char *ptr;
	int nmsym;
	addr_t a0, ai, aj;
	char *id0, *idi;
	struct sym *sp;
	struct sym **p;

	putc('\n', mfp);
	if (xflag == 0) {
		fprintf(mfp, "Hexidecimal\n\n");
	} else
	if (xflag == 1) {
		fprintf(mfp, "Octal\n\n");
	} else
	if (xflag == 2) {
		fprintf(mfp, "Decimal\n\n");
	}
	fprintf(mfp, "Area                               ");
	fprintf(mfp, "Addr   Size   Decimal Bytes (Attributes)\n");
	fprintf(mfp, "--------------------------------   ");
	fprintf(mfp, "----   ----   ------- ----- ------------\n");
	/*
	 * Output Area Header
	 */
	ptr = &rp->a_id[0];
        i = &rp->a_id[NCPS] - ptr;
        i = NCPS;
        i = 0;
	while (ptr < &rp->a_id[NCPS]) {
		if ((c = *ptr++) != 0) {
			putc(c, mfp);
		} else {
			putc(' ', mfp);
		}
                i++;
	}
	ai = rp->a_addr;
	aj = rp->a_size;
	if (xflag == 0) {
		fprintf(mfp, "   %04X   %04X", ai, aj);
	} else
	if (xflag == 1) {
		fprintf(mfp, " %06o %06o", ai, aj);
	} else
	if (xflag == 2) {
		fprintf(mfp, "  %05u  %05u", ai, aj);
	}
	fprintf(mfp, " = %6u. bytes ", aj);
	if (rp->a_flag & A_ABS) {
		fprintf(mfp, "(ABS");
	} else {
		fprintf(mfp, "(REL");
	}
	if (rp->a_flag & A_OVR) {
		fprintf(mfp, ",OVR");
	} else {
		fprintf(mfp, ",CON");
	}
	if (rp->a_flag & A_PAG) {
		fprintf(mfp, ",PAG");
	}
	if (rp->a_inst) {
		fprintf(mfp, ",I");
	}
	fprintf(mfp, ")");
	if (rp->a_flag & A_PAG) {
		ai = (ai & 0xFF);
		aj = (aj > 256);
		if (ai || aj) { fprintf(mfp, "  "); }
		if (ai)      { fprintf(mfp, " Boundary"); }
		if (ai & aj)  { fprintf(mfp, " /"); }
		if (aj)      { fprintf(mfp, " Length"); }
		if (ai || aj) { fprintf(mfp, " Error"); }
	}

	/*
	 * Find number of symbols in area
	 */
	nmsym = 0;
	oxp = rp->a_axp;
	while (oxp) {
		for (i=0; i<NHASH; i++) {
			sp = symhash[i];
			while (sp != NULL) {
				if (oxp == sp->s_axp)
					++nmsym;
				sp = sp->s_sp;
			}
		}
		oxp = oxp->a_axp;
	}
	if (nmsym == 0) {
		putc('\n', mfp);
		return;
	}

	/*
	 * Allocate space for an array of pointers to symbols
	 * and load array.
	 */
	if ( (p = (struct sym **) malloc(nmsym*sizeof(struct sym *)))
		== NULL) {
		fprintf(mfp, "\nInsufficient space to build Map Segment.\n");
		return;
	}
	nmsym = 0;
	oxp = rp->a_axp;
	while (oxp) {
		for (i=0; i<NHASH; i++) {
			sp = symhash[i];
			while (sp != NULL) {
				if (oxp == sp->s_axp) {
					p[nmsym++] = sp;
				}
				sp = sp->s_sp;
			}
		}
		oxp = oxp->a_axp;
	}

	/*
	 * Bubble Sort of Addresses in Symbol Table Array
	 */
	j = 1;
	while (j) {
		j = 0;
		sp = p[0];
		a0 = sp->s_addr + sp->s_axp->a_addr;
		id0 = sp->s_id;
		for (i=1; i<nmsym; ++i) {
			sp = p[i];
			ai = sp->s_addr + sp->s_axp->a_addr;
			idi = sp->s_id;
			if ((a0 > ai) || ((a0 == ai) && (memcmp(id0, idi, NCPS) > 0))) {
				j = 1;
				p[i] = p[i-1];
				p[i-1] = sp;
			}
			a0 = ai;
			id0 = idi;
		}
	}

	/*
	 * Symbol Table Output
	 */
	i = 0;
	fprintf(mfp, "\n\n");
	fprintf(mfp, "      Value  Global\n");
	fprintf(mfp, "      -----  --------------------------------");
	while (i < nmsym) {
		/*
		if (i % 4 == 0) {
			fprintf(mfp, "\n");
			slew(mfp);
			fprintf(mfp, "     ");
		}
		*/
		fprintf(mfp, "\n");
		fprintf(mfp, "     ");

		sp = p[i];
		aj = sp->s_addr + sp->s_axp->a_addr;
		if (xflag == 0) {
			fprintf(mfp, "  %04X  ", aj);
		} else
		if (xflag == 1) {
			fprintf(mfp, "%06o  ", aj);
		} else
		if (xflag == 2) {
			fprintf(mfp, " %05u  ", aj);
		}
		ptr = &sp->s_id[0];
		while (ptr < &sp->s_id[NCPS]) {
			if ((c = *ptr++) != 0) {
				putc(c, mfp);
			} else {
				putc(' ', mfp);
			}
		}
		i++;
		/*
		if (++i < nmsym)
			if (i % 4 != 0)
				fprintf(mfp, " | ");
		*/
	}
	putc('\n', mfp);
	free(p);
}
