/* m04mch.c */

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
#include "m6804.h"

/*
 * Process a machine op.
 */
VOID
machine(mp)
struct mne *mp;
{
	register op, t1, t2, type;
	struct expr e1, e2, e3;
	struct area *espa;
	int c, v1, v2, v3;
	char id[NCPS];

	op = mp->m_valu;
	type = mp->m_type;
	switch (type) {

	case S_SDP:
		e1.e_mode = 0;
		e1.e_flag = 0;
		e1.e_addr = 0;
		e1.e_base.e_ap = NULL;
		espa = NULL;
		if (more()) {
			expr(&e1, 0);
			if (e1.e_flag == 0 && e1.e_base.e_ap == NULL) {
				if (e1.e_addr) {
					err('b');
				}
			}
			if ((c = getnb()) == ',') {
				getid(id, -1);
				espa = alookup(id);
				if (espa == NULL) {
					err('u');
				}
			} else {
				unget(c);
			}
		}
		if (espa) {
			outdp(espa, &e1);
		} else {
			outdp(dot.s_area, &e1);
		}
		lmode = SLIST;
		break;

	case S_INH:
		outab(op);
		break;

	case S_BRA:
		expr(&e1, 0);
		v1 = e1.e_addr - dot.s_addr - 1;
		if ((v1 < -16) || (v1 > 15))
			aerr();
		if (e1.e_base.e_ap != dot.s_area)
			rerr();
		outab(op | v1&0x1F);
		break;

	case S_TYP1:
		expr(&e1, 0);
		v1 = e1.e_addr;
		if ((v1 < -4096) || (v1 > 4095))
			aerr();
		e1.e_addr += op;
		outrw(&e1, 0);
		break;

	case S_TYP2:
	case S_TYP3:
		t1 = addr(&e1);
		if (type == S_TYP3 & t1 == S_IMMED) {
			outab(op|0x08);
			outrb(&e1, 0);
			break;
		}
		if (t1 == S_DIR) {
			v1 = e1.e_addr;
			if ((e1.e_base.e_ap == NULL) &
			    v1 >= 0x80 & v1 <= 0x83) {
				v1 &= 0x03;
				if (op == 0xE0) {
					outab(0xAC | v1);
					break;
				}
				if (op == 0xE1) {
					outab(0xBC | v1);
					break;
				}
				if (op == 0xE6) {
					outab(0xA8 | v1);
					break;
				}
				if (op == 0xE7) {
					outab(0xB8 | v1);
					break;
				}
			}
			outab(op|0x18);
			outrb(&e1, R_PAG0);
			break;
		}
		if (t1 == S_IX) {
			outab(op);
			break;
		}
		if (t1 == S_IY) {
			outab(op|0x10);
			break;
		}
		aerr();
		break;

	case S_CLR:
		outab(0xB0);
		outab(op);
		outab(0x00);
		break;

	case S_LD:
		t1 = addr(&e1);
		if (t1 == S_IMMED) {
			outab(0xB0);
			outab(op);
			outrb(&e1, 0);
			break;
		}
		aerr();
		break;

	case S_MVI:
		t1 = addr(&e1);
		if (t1 != S_DIR)
			aerr();
		comma();
		t2 = addr(&e2);
		if (t2 != S_IMMED)
			aerr();
		outab(op);
		outrb(&e1, 0);
		outrb(&e2, 0);
		break;

	case S_APOST:
		outab(op);
		outab(0xFF);
		break;

	case S_BPM:
	case S_BXPM:
	case S_BYPM:
		expr(&e2, 0);
		outab(op);
		if (type == S_BPM)
			v1 = 0xFF;
		if (type == S_BXPM)
			v1 = 0x80;
		if (type == S_BYPM)
			v1 = 0x81;
		outab(v1);
		if (e2.e_base.e_ap == NULL || e2.e_base.e_ap == dot.s_area) {
			v2 = e2.e_addr - dot.s_addr - 1;
			if ((v2 < -128) || (v2 > 127))
				aerr();
			outab(v2);
		} else {
			outrb(&e2, R_PCR);
		}
		if (e2.e_mode != S_USER)
			rerr();
		break;

	case S_BTB:
	case S_BSC:
		t1 = addr(&e1);
		if (t1 != S_IMMED || e1.e_addr & ~0x07)
			aerr();
		comma();
		t2 = addr(&e2);
		if (t2 != S_DIR)
			aerr();
		if (type == S_BTB) {
			comma();
			expr(&e3, 0);
		}
		outab(op + (e1.e_addr & 0x07));
		outrb(&e2, R_USGN);
		if (type == S_BTB) {
			if (e3.e_base.e_ap == NULL || e3.e_base.e_ap == dot.s_area) {
				v3 = e3.e_addr - dot.s_addr - 1;
				if ((v3 < -128) || (v3 > 127))
					aerr();
				outab(v3);
			} else {
				outrb(&e3, R_PCR);
			}
			if (e3.e_mode != S_USER)
				rerr();
		}
		break;

	default:
		err('o');
	}
}


/*
 * The next character must be a
 * comma.
 */
VOID
comma()
{
	if (getnb() != ',')
		qerr();
}

/*
 * Machine specific initialization.
 */
VOID
minit()
{
}
