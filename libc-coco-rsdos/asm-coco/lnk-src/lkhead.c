/* lkhead.c */

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
#include "aslink.h"

/*
 * Create a new header entry.
 *
 * H n areas n global symbols
 *   |       |
 *   |       `---- hp->h_nglob
 *   `------------ hp->h_narea
 *
 */
VOID
newhead()
{
	register int i;
	struct head *thp;

	hp = (struct head *) new (sizeof(struct head));
	if (headp == NULL) {
		headp = hp;
	} else {
		thp = headp;
		while (thp->h_hp)
			thp = thp->h_hp;
		thp->h_hp = hp;
	}
	/*
	 * Set file pointer
	 */
	hp->h_lfile = cfp;
	/*
	 * Evaluate and build Area pointer list
	 */
	i = hp->h_narea = eval();
	if (i)
		hp->a_list = (struct areax **) new (i*sizeof(struct areax *));
	/*
	 * Evaluate and build Global symbol pointer list
	 */
	skip(-1);
	i = hp->h_nglob = eval();
	if (i)
		hp->s_list = (struct sym **) new (i*sizeof(struct sym *));
	/*
	 * Setup Absolute DEF linkage.
	 */
	lkparea(_abs_);
	ap->a_flag = A_ABS|A_OVR;
}

/*
 * Module Name
 */
VOID
module()
{
	char id[NCPS];
	static int mainline = 0;

	if (headp) {
		getid(id, -1);
		strncpy(hp->m_id, id, NCPS);

		/* only do the following if we're linking an OS-9 module */
		if (oflag == 9)
		{
			hp->m_typelang = eval();
			hp->m_attrev = eval();
			hp->m_edition = eval();
			hp->m_stacksize = eval();
			hp->m_modent = eval();

			if (mainline == 1 && hp->m_typelang != 0)
			{
				/* mainline already defined -- error here */
				fprintf(stderr, "Multiple mainlines detected\n");
				exit(1);
			}
			if (hp->m_typelang != 0)
			{
				mainline = 1;
			}
		}
	} else {
		fprintf(stderr, "No header defined\n");
	}
}
