/* lkbin.c */

/*
 * Eric Botcazou
 */


#include <stdio.h>
#include <string.h>
#include "aslink.h"


/* trailing NULL characters are mandatory */
static char start_str[NCPS] = "start";


VOID
fputw(val, file)
int val;
FILE *file;
{
	fputc(val>>8, file);
	fputc(val&0xFF, file);
}


VOID
bin(i)
{
	struct area *last_ap;
	struct sym *start_sym;
	static addr_t base_addr = 0;
	addr_t addr;

	switch (i) {

		case -1:  /* header */
			fputc(0, ofp);

                        /* reloc_ap is the first non empty area */
			base_addr = reloc_ap->a_addr;

			/* find the last instantiated area */
                        last_ap = ap = reloc_ap;
			do {
				if (ap->a_inst)
					last_ap = ap;

				ap = ap->a_ap;
			} while (ap);

			fputw(last_ap->a_addr + last_ap->a_size - base_addr, ofp);
			fputw(base_addr, ofp);	
			break;

		case 1:  /* data */
			/* calculate chunk address */
			addr = (rtval[0]<<8) + rtval[1];

			/* fill gap */
			while (base_addr < addr) {
				fputc(0, ofp);
				base_addr++;
			}

			for (i = 2; i < rtcnt ; i++) {
				if (rtflg[i]) {
					fputc(rtval[i], ofp);
					base_addr++;
				}
			}

			break;

		case 0:  /* final hunk */
			fputc(0xFF, ofp);
			fputw(0, ofp);
			start_sym = lkpsym(start_str, 0);
			if (start_sym)
				fputw(start_sym->s_addr + start_sym->s_axp->a_addr, ofp);
			else
				fputw(0, ofp);
			break;
	}
}
