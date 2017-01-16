/* lkmain.c */

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


char ofile[FILSPC];
int vlevel;


VOID
verbose(lvl, text, t2)
int lvl;
char *text;
char *t2;
{
	if (vlevel >= lvl) 
		fprintf(stdout, "%s %s\n", text, t2);
}


VOID
addlpath(path)
char *path;
{
	verbose(2, "Adding libpath", path);
        
	if (!libpathp) {
		libpathp = (struct lfile *) new(sizeof(struct lfile));
		lpp = libpathp;
	} else {
		lpp->f_flp = (struct lfile *) new(sizeof(struct lfile));
		lpp = lpp->f_flp;
	}
        
	lpp->f_idp = (char *) new(strlen(path) + 1);
	strcpy(lpp->f_idp, path);
}


int
main(argc, argv)
int   argc;
char *argv[];
{
	int nlib, c, i;
	char *p;

	nlib = 0;
	pflag = 0;
	oflag = 2;
	vlevel = 0;
	ofile[0] = '\0';

	if (argc < 2)  /* at least one argument */
	   usage();

	for (i=1; i<argc; ++i) {
		p = argv[i];

		if (*p == '-') {
			c = *(++p);

			switch(c) {

				case 'v':
					vlevel = 1;
					if (*(p+1) != 0)
						vlevel = atoi( p+1 );
					break;

				case 'i':
					oflag = 1;
					break;

				case 's':
					oflag = 2;
					break;

				case 't':
					oflag = 3;
					break;

				case '9':
					oflag = 9;
					break;

				case 'm':
					mflag = 1;
					break;

				case 'x':
					xflag = 0;
					break;

				case 'q':
					mflag = 1;
					break;

				case 'd':
					xflag = 2;
					break;

				case 'b':
					if (*(p+1) != '\0') {
						bassav(p+1);
					}
					else {
						bassav(argv[++i]);
					}
					break;

				case 'g':
					if (*(p+1) != '\0') {
						gblsav(p+1);
					}
					else {
						gblsav(argv[++i]);
					}
					break;

				case 'o':
					if (*(p+1) != '\0') {
						strcpy(ofile, p+1);
					}
					else {
						strcpy(ofile, argv[++i]);
					}
					break;

				case 'l':
					if (!libp) {
						libp = (struct lfile *) new(sizeof(struct lfile));
						lp = libp;
					} else {
						lp->f_flp = (struct lfile *) new(sizeof(struct lfile));
						lp = lp->f_flp;
					}

					/* add a numeric identifier in order to differentiate multiple instances */
					lp->f_idp = (char *) new(strlen(p+1) + 6);
					sprintf(lp->f_idp, "lib%s.a", p+1);

					if (!linkp) {
						fprintf(stderr, "No object file before %s !\n", lp->f_idp);
						return 1;
					}

					lfp->f_flp = (struct lfile *) new(sizeof (struct lfile));
					lfp = lfp->f_flp;

					lfp->f_idp = (char *) new(strlen(lp->f_idp) + 1);
					strcpy(lfp->f_idp, lp->f_idp);
					lfp->f_type = F_LIB;
                                
					break;


				case 'L':
					if (*(p+1) != 0)
						addlpath(p+1);
					else
						addlpath(argv[++i]);

					break;

				default:
					usage();
			}
		}
		else {
			if (!linkp) {
				linkp = (struct lfile *) new(sizeof (struct lfile));
				lfp = linkp;
			} else {
				lfp->f_flp = (struct lfile *) new(sizeof (struct lfile));
				lfp = lfp->f_flp;
			}

			lfp->f_idp = (char *) new (strlen(p)+1);
			strcpy(lfp->f_idp, p);
			lfp->f_type = F_REL;
		}
	}

	if (vlevel > 0) {
		if (libpathp) {
			fprintf(stdout, "Library search starts here:\n");
			lpp = libpathp;

			while (lpp) {
				fprintf( stdout, "  %s\n", lpp->f_idp );
				lpp = lpp->f_flp;
			}
		}
		else {
			fprintf(stdout, "no library search path.\n");
		}
	}

	if (ofile[0] == '\0') {
		switch (oflag) {
			case 1:
				strcpy(ofile, "a.ihx");
				break;
			case 2:
			default:
				strcpy(ofile, "a.s19");
				break;
			case 3:
				strcpy(ofile, "a.bin");
				break;

			case 9:
				strcpy(ofile, "a");
				break;
		}
	}

	syminit();
	modinit();

	pass = 0;
	while (1) {
		cfp = NULL;
		sfp = NULL;
		filep = linkp;
		hp = NULL;
		radix = 10;

		while (getline()) {
			ip = ib;
			link();
		}

		if (pass == 0) {
			/*
			 * Set area base addresses.
			 */
			setbas();
			/*
			 * Link all area addresses.
			 */
			lnkarea();
			/*
			 * Process global definitions.
			 */
			setgbl();
			/*
			 * Check for undefined globals.
			 */
			symdef(stderr);
			/*
			 * Output Link Map.
			 */
			if (mflag)
				map();
			/*
			 * Prepare for relocation passes 
			 */
			reloc_ap = areap;

			/* find first non empty area */
			while (reloc_ap->a_size == 0) {
				reloc_ap = reloc_ap->a_ap;
				if (!reloc_ap) {
					/* no output file */
					fprintf(stderr, "Nothing to link !\n");
					return 1;
				}
			}

			/*
			 * Open output file
			 */
			switch (oflag) {
				case 1:
				case 2:
					ofp = afile(ofile, NULL, "w", 0);
					break;
				case 3:
					ofp = afile(ofile, NULL, "wb", 0);
					bin(-1);
					break;
				case 9:
					ofp = afile(ofile, NULL, "wb", 0);
					os9(-1);
					break;
			}
		}
		else {
			/*
			 * Next relocation pass
			 */
			reloc_ap = reloc_ap->a_ap;
		}

		/* skip non instantiated areas */
		while (reloc_ap && (!reloc_ap->a_inst))
			reloc_ap = reloc_ap->a_ap;

		if (reloc_ap) {
			pass++;
		}
		else {
			reloc('E');
			break;
		}
	}

	return 0;
}

#define SKIP_MODULE()					\
{							\
	while (getline()) {				\
		if ((ib[0] == 'L') && (ib[1] == '1'))	\
			break;				\
	}						\
}


VOID
link()
{
	static long filepos;
	struct areax **a;
	struct mod *m;
	int aindex;
	register int c;

	if ((c=endline()) == 0)
		return;

	switch (c) {

		case 'X':
			radix = 16;
			break;

		case 'D':
			radix = 10;
			break;

		case 'Q':
			radix = 8;
			break;

		case 'H':
			if ((in_lib == L_NOLIB) || (pass > 0)) {
				if (pass == 0) {
					newhead();
				} else {
					hp = (hp ? hp->h_hp : headp);
				}

				sdp.s_area = NULL;
				sdp.s_areax = NULL;
				sdp.s_addr = 0;
			}
			break;

		case 'L':
			c = getnb();

			if (c == '0') {
				/* start of a module */
				getmodid(modname, -1);
				m = lkpmod(modname, 0);

				if (pass == 0) {
					if (in_lib == L_SCANIMP) {
						if (m) {
							/* skip all known modules -- already scanned */
							verbose(1, "Pass 0: skip", modname);
							SKIP_MODULE();
						}
						else {
							verbose(1, "Pass 0: scan", modname);
						}
					}
					else if (in_lib == L_NOLIB) {
						if (m && (!m->imported)) {
							/* flag the module as already imported to prevent multiple definition
							 * of the same symbol if the library is imported several times.
							 */
							verbose(1, "Pass 0: import", modname);
							m->imported = 1;
						}
						else {
							/* skip all already imported modules */
							SKIP_MODULE();
						}
					}
				}
				else {
					/* on subsequent passes, link modules */
					if (m && (m->m_lib == cfp)) {
						verbose(1, "Pass n: link", modname);
					}
					else {
						verbose(1, "Pass n: skip", modname);
						SKIP_MODULE();
					}	
				}
			}
			else if (c == '1') {
				if (pass == 0) {
					if (in_lib == L_SCANREF) {
						/* module added to the list: we need to rescan the whole library
						 * to track down backward cross-references between the modules.
						 */
						verbose(1, "Pass 0: need to import", modname);
						setfilepos(0);
						in_lib = L_SCANIMP;
						verbose(3, "in_lib =", "L_SCANIMP");
					}
				}
			}
			break;

		case 'E':
			if ((pass == 0) && (in_lib == L_SCANIMP)) {
				/* rewind the library to import the modules in order */
				setfilepos(0);
				in_lib = L_NOLIB;
				verbose(3, "in_lib =", "L_NOLIB");
			}
			break;

		case 'M': 
			if ((pass == 0) && (in_lib == L_NOLIB))
				module();  /* M field, not library module */
			break;

		case 'A':
			if ((in_lib == L_NOLIB) || (pass > 0)) {
				if (pass == 0)
					newarea();

				if (sdp.s_area == NULL) {
					sdp.s_area = areap;
					sdp.s_areax = areap->a_axp;
					sdp.s_addr = 0;
				}
			}
			break;

		case 'S':
			if (pass == 0) {
				switch (in_lib) {

					case L_SCANIMP:
						if (checksym()) {
							if (lkpmod(modname, 0)) {
								fprintf(stderr, "Module name %.15s already exists\n", modname);
								exit(1);
							}

							lkpmod(modname, 1);

							/* re-read the module */
							in_lib = L_SCANREF;
							verbose(3, "in_lib =", "L_SCANREF");
							setfilepos(filepos);
						}
						break;

					case L_SCANREF:
						newrefsym();
						break;

					case L_NOLIB:
						newsym();
						break;
				}
			}
			break;

		case 'T':
			if (pass > 0)
				reloc('T');
			break;

		case 'R':
		case 'P':
			if (pass == 0) {
				if (in_lib == L_NOLIB) {
					/* get area list */
					a = hp->a_list;

					/* verify area mode */
					if (eval() != (R_WORD | R_AREA) || eval())
						fprintf(stderr, "Pass 0: R or P input error in %s\n", hp->m_id);

					/* get area pointer */
					aindex = evword();
					if (aindex >= hp->h_narea) {
						fprintf(stderr, "Pass 0: R or P area error in %s\n", hp->m_id);
					}
					else {
						/* mark base area as instantiated */
						a[aindex]->a_bap->a_inst = 1;
					}
				}
			}
			else {
				reloc(c);
			}
			break;

		default:
			break;
	}

	if (c == 'X' || c == 'D' || c == 'Q') {
		/* save start position of the module */
		filepos = getfilepos();

		if ((c = get()) == 'H') {
			hilo = 1;
		} else if (c == 'L') {
			hilo = 0;
		}
	}
}


VOID
map()
{
	register int i;
	register struct head *hdp;

	/*
	 * Open Map File
	 */
	mfp = afile(ofile, "map", "w" ,0);

	/*
	 * Output Map Area Lists
	 */
	page = 0;
	ap = areap;
	while (ap) {
		lstarea(ap);
		ap = ap->a_ap;
	}
	/*
	 * List Linked Files
	 */
	fprintf(mfp, "\nFiles Linked      [ module(s) ]\n\n");
	hdp = headp;
	filep = linkp;
	while (filep) {
		fprintf(mfp, "%-16s", filep->f_idp);
		i = 0;
		while ((hdp != NULL) && (hdp->h_lfile == filep)) {
			if (i % 5) {
			    fprintf(mfp, ", %8.8s", hdp->m_id);
			} else {
			    if (i) {
				fprintf(mfp, ",\n%20s%8.8s", "", hdp->m_id);
			    } else {
				fprintf(mfp, "  [ %8.8s", hdp->m_id);
			    }
			}
			hdp = hdp->h_hp;
			i++;
		}
		if (i)
			fprintf(mfp, " ]");
		fprintf(mfp, "\n");
		filep = filep->f_flp;
	}
	/*
	 * List Base Address Definitions
	 */
	if (basep) {
		fprintf(mfp, "\nUser Base Address Definitions\n\n");
		bsp = basep;
		while (bsp) {
			fprintf(mfp, "%s\n", bsp->b_strp);
			bsp = bsp->b_base;
		}
	}
	/*
	 * List Global Definitions
	 */
	if (globlp) {
		fprintf(mfp, "\nUser Global Definitions\n\n");
		gsp = globlp;
		while (gsp) {
			fprintf(mfp, "%s\n", gsp->g_strp);
			gsp = gsp->g_globl;
		}
	}
	fprintf(mfp, "\n");
	symdef(mfp);
}


/*
 * Base string save
 */
VOID
bassav(value)
char *value;
{
	if (!basep) {
		basep = (struct base *)
                        	new (sizeof (struct base));
		bsp = basep;
	} else {
		bsp->b_base = (struct base *)
				new (sizeof (struct base));
		bsp = bsp->b_base;
	}

	bsp->b_strp = (char *) new (strlen(value)+1);
	strcpy(bsp->b_strp, value);
}


VOID
setbas()
{
	register int v;
	char id[NCPS];

	bsp = basep;
	while (bsp) {
		ip = bsp->b_strp;
		getid(id, -1);
		if (getnb() == '=') {
			v = expr(0);
			for (ap = areap; ap != NULL; ap = ap->a_ap) {
				if (symeq(id, ap->a_id))
					break;
			}
			if (ap == NULL) {
				fprintf(stderr,
				"No definition of area %s\n", id);
			} else {
				ap->a_addr = v;
			}
		} else {
			fprintf(stderr, "No '=' in base expression");
		}
		bsp = bsp->b_base;
	}
}


/*
 * Global string save
 */
VOID
gblsav(value)
char *value;
{
	if (globlp == NULL) {
		globlp = (struct globl *)
			new (sizeof (struct globl));
		gsp = globlp;
	} else {
		gsp->g_globl = (struct globl *)
				new (sizeof (struct globl));
		gsp = gsp->g_globl;
	}
	gsp->g_strp = (char *) new (strlen(value)+1);
	strcpy(gsp->g_strp, value);
}


VOID
setgbl()
{
	register int v;
	register struct sym *sp;
	char id[NCPS];

	gsp = globlp;
	while (gsp) {
		ip = gsp->g_strp;
		getid(id, -1);
		if (getnb() == '=') {
			v = expr(0);
			sp = lkpsym(id, 0);
			if (sp == NULL) {
				fprintf(stderr,
				"No definition of symbol %s\n", id);
			} else {
				if (sp->s_flag & S_DEF) {
					fprintf(stderr,
					"Redefinition of symbol %s\n", id);
					sp->s_axp = NULL;
				}
				sp->s_addr = v;
				sp->s_type |= S_DEF;
			}
		} else {
			fprintf(stderr, "No '=' in global expression");
		}
		gsp = gsp->g_globl;
	}
}


FILE *
afile(fn, ft, mode, lf)
char *fn;
char *ft;
char *mode;
int   lf;  /* lib flag   */
{
	FILE *fp = NULL;
	char fb[FILSPC];

	strcpy(fb, fn);
	if (ft) {
		strcat(fb, ".");
		strcat(fb, ft);
	}

	if (!lf) {        
		if ((fp = fopen(fb, mode)) == NULL) {
			fprintf(stderr, "cannot %s %s\n", mode[0] == 'w' ? "create" : "open", fb);
			exit(1);
		}
		return fp;
	}
        
	lpp = libpathp;
	while (lpp && !fp) {
		strcpy( fb, lpp->f_idp );
		strcat( fb, DIRSEP );
		strcat( fb, fn );
		verbose( 2, "opening", fb );
		fp = fopen(fb, mode);
		lpp = lpp->f_flp;
	}
        
	if (fp) {
		verbose( 2, "opened library", fb );
		return fp;
	}

	fprintf( stderr, "cannot find %s\n", fn );
	exit(1);
}


char *usetxt[] = {
	"Startup:",
	"  -c                           Command line input",
	"  -f   file[LNK]               File input",
	"Usage: [-Options] file [file ...]",
	"  -p   Prompt and echo of file[LNK] to stdout (default)",
	"  -n   No echo of file[LNK] to stdout",
	"  -o   Specify output name",
	"Relocation:",
	"  -b   area base address = expression",
	"  -g   global symbol = expression",
	"Map format:",
	"  -m   Map output generated as file[map]",
	"  -x   Hexidecimal (default)",
	"  -d   Decimal",
	"  -q   Octal",
	"Output format:",
	"  -i   Intel Hex",
	"  -s   Motorola S19",
	"  -t   Thomson BIN",
	"  -9   OS-9 BIN",
	"End:",
	"  -e   or null line terminates input",
	0
};


VOID
usage()
{
	register char **dp;

	fprintf(stderr, "ASxxxx Linker %s\n\n", VERSION);

	for (dp = usetxt; *dp; dp++)
		fprintf(stderr, "%s\n", *dp);

	exit(1);
}
