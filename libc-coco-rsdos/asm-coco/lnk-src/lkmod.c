/* lkmod.c */

/*
 * Matthias Dörfel
 */


#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "aslink.h"


/*
 * This routine is called early in the
 * game to set up the module hashtable.
 */
VOID
modinit()
{
	struct mod **mpp;

	mpp = &modhash[0];
	while (mpp < &modhash[NHASH])
		*mpp++ = NULL;
}


struct mod *
newmod()
{
	struct mod *tsp;
	char id[NCPS];

	getmodid(id, -1);
	tsp = lkpmod(id, 1);

	return tsp;
}


/*
 * Lookup the name `id' in the hashtable.
 * If it is not found either return a
 * `NULL' (`f' is false) or a
 * pointer to a newly created hash table
 * entry (`f' is true).
 */
struct mod *
lkpmod(id, f)
char *id;
int f;
{
	struct mod *sp;
	int h;

	h = hash(id);
	sp = modhash[h];

	while (sp != NULL) {
		if (symeq(id, sp->m_id))
			return (sp);

		sp = sp->m_mp;
	}

	if (f == 0)
		return (NULL);

	sp = (struct mod *) new (sizeof(struct mod));
	sp->m_mp = modhash[h];
        modhash[h] = sp;
	sp->m_lib = cfp;
	strncpy(sp->m_id, id, NCPS);

	return (sp);
}


/*
 * Enhanced version of getid() (from lklex.c) for modules:
 *  Appends an identifier tag from the library name to
 *  the module name. This makes it possible to import
 *  modules with the same name from two different librairies.
 */
VOID
getmodid(id, c)
int c;
char *id;
{
	char *p;
	int len;

	/* get raw id */
	getid(id, c);

#define TAG_LEN  5
	/* add identifier tag (TAG_LEN letters at most) from the library */
	p = cfp->f_idp+3;  /* skip "lib" */
	len = 0;

	while ((*p != '.') && (len<TAG_LEN)) {
		p++;
		len++;
	}

	if (strlen(id) > NCPS-(len+1)) {
		id[NCPS-1-(len+1)] = '_';
		strncpy(id + NCPS-(len+1), cfp->f_idp+3, len);
	}
	else {
		strcat(id, "_");
		strncat(id, cfp->f_idp+3, len);
	}
}
