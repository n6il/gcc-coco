/* lkos9.c */

/*
 * Boisy Pitre
 */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "aslink.h"


/* trailing NULL characters are mandatory */
//static char start_str[NCPS] = "start";

static void compute_crc(u_char a);
u_char _crc[3];

VOID
os9(i)
{
	struct area *last_ap;
	struct head *last_hp;
//	struct sym *start_sym;
	static addr_t base_addr = 0;
	addr_t moduleSize = 0;	/* OS-9 module header size */
	int headerSize;
	int dataSize;
	int nameOffset, execOffset;
	addr_t addr;
	char *modName;
	char headerParity;
	char typelang, attrev;
	char edition;

	switch (i) {

		case -1:  /* header */
			/* Initialize variables */
			dataSize = 0;		/* Data area size */
			headerParity = 0;
			_crc[0] = 0xFF;		/* CRC */
			_crc[1] = 0xFF;
			_crc[2] = 0xFF;
			moduleSize = 0;
			modName = "test";
			edition = 1;

                        /* reloc_ap is the first non empty area */
			base_addr = reloc_ap->a_addr;

			/* find the mainline module */
			last_hp = NULL;
                        hp = headp;
			do {
				dataSize += hp->m_stacksize;
				if (hp->m_typelang != 0)
				{
					last_hp = hp;
					modName = hp->m_id;
				}
				hp = hp->h_hp;
			} while (hp);

			if (last_hp == NULL)
			{
				fprintf(stderr, "No mainline found\n");
				exit(1);
			}

			/* Start Generating Module */
			/* Module signature */
			fputw(0x87CD, ofp);
			compute_crc(0x87); compute_crc(0xCD);
			headerParity ^= 0x87;
			headerParity ^= 0xCD;

			/* now that we know module name, compute headerSize */
			headerSize = 0x0D + strlen(modName) + sizeof(edition);

			/* find the last instantiated area */
                       last_ap = ap = reloc_ap;
			do {
				if (ap->a_inst)
					last_ap = ap;

				ap = ap->a_ap;
			} while (ap);

			moduleSize =last_ap->a_addr + last_ap->a_size - base_addr + headerSize + 3;
			fputw(moduleSize, ofp);
			compute_crc(moduleSize >> 8); compute_crc(moduleSize & 0xFF);
			headerParity ^= moduleSize >> 8;
			headerParity ^= moduleSize & 0xFF;
			
			/* Write module name offset (assumed for now) */
			nameOffset = 0x0D;
			fputw(nameOffset, ofp);
			compute_crc(nameOffset >> 8); compute_crc(nameOffset & 0xFF);
			headerParity ^= nameOffset >> 8;
			headerParity ^= nameOffset & 0xFF;
			
			/* module type/lang (assume prgrm+objct for now) */
			typelang = last_hp->m_typelang;
			fputc(typelang, ofp);
			compute_crc(typelang);
			headerParity ^= typelang;
			
			/* module attr/rev (assume reent+0 for now) */
			attrev = last_hp->m_attrev;
			fputc(attrev, ofp);
			compute_crc(attrev);
			headerParity ^= attrev;
			
			/* header check (computed at end) */
			headerParity = ~headerParity;
			fputc(headerParity, ofp);
			compute_crc(headerParity);
			
			/* execution offset */
			execOffset = (int)last_hp->m_modent + headerSize;
			fputw(execOffset, ofp);
			compute_crc(execOffset >> 8); compute_crc(execOffset & 0xFF);
			
			/* Compute data size - tally _BSS and _DATA areas */
			ap = reloc_ap;
			do
			{
				if (strcmp(ap->a_id, "_DATA") == 0 || strcmp(ap->a_id, "_BSS") == 0)
				{
					dataSize += ap->a_size;
				}
				ap = ap->a_ap;
			}
			while (ap);
			fputw(dataSize, ofp);
			compute_crc(dataSize >> 8); compute_crc(dataSize & 0xFF);
			/* module name */
			for (i = 0; i < strlen(modName) - 1; i++)
			{
				fputc(modName[i], ofp);
				compute_crc(modName[i]);
			}
			fputc(modName[i] | 0x80, ofp);
			compute_crc(modName[i] | 0x80);
			
			/* edition */
			edition = last_hp->m_edition;
			fputc(edition, ofp);
			compute_crc(edition);

			break;

		case 1:  /* data */
			/* calculate chunk address */
			addr = (rtval[0]<<8) + rtval[1];

#if 0
			/* fill gap */
			while (base_addr < addr) {
				fputc(0, ofp);
				base_addr++;
			}
#endif

			for (i = 2; i < rtcnt ; i++) {
				if (rtflg[i]) {
					fputc(rtval[i], ofp);
					compute_crc(rtval[i]);
					base_addr++;
				}
			}

			break;

		case 0:  /* final hunk */
			// Compute and write the CRC
			fputc(~_crc[0], ofp);
			fputc(~_crc[1], ofp);
			fputc(~_crc[2], ofp);
			break;
	}
}


static void compute_crc(u_char a)
{
	a ^= _crc[0];
	_crc[0] = _crc[1];
	_crc[1] = _crc[2];
	_crc[1] ^= (a >> 7);
	_crc[2] = (a << 1);
	_crc[1] ^= (a >> 2);
	_crc[2] ^= (a << 6);
	a ^= (a << 1);
	a ^= (a << 2);
	a ^= (a << 4);
	if (a & 0x80)
	{
		_crc[0] ^= 0x80;
		_crc[2] ^= 0x21;
	}

	return;
}
