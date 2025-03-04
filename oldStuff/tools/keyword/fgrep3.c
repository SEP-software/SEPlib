static char *sccsid = "@(#)fgrep.c	4.2 (Berkeley) 10/20/82";
/*
 * fgrep3 -- print all lines containing any of a set of keywords
 *
 * Modified from fgrep2 by Dave Nichols. 2-3-91
 * Return code is zero unless somethin catastropic happens.
 * This is so we can pipe xargs into this (xargs checks the reurn code)
 *
 *	status returns:
 *		0 - ok
 *		2 - some error
 */

#include <sepConfig.h>
#if HAVE_STDLIB_H
#include <stdlib.h>
#endif
#include <stdio.h>
#if HAVE_UNISTD_H
#include <unistd.h>
#endif
#include <ctype.h>
#if defined(__APPLE__) || defined(LINUX)
#include <sys/types.h>
#ifdef __APPLE__
#include <sys/uio.h>
#endif
#ifdef LINUX
#include <sys/stat.h>
#endif
#include <fcntl.h>
#endif

#define	MAXSIZ 6000
#define QSIZE 400
/*
 * This program is just like fgrep, except that it prints out the file
 * name even when there is only ONE file name argument present.
 * This is needed by the shell index. It also differs in that it gives
 * up after the first GIVE_UP lines, exiting at that point with a status of
 * 0 regardless of what's happened.
 */
#define ONE 0
#define GIVE_UP 100
struct words {
	char 	inp;
	char	out;
	struct	words *nst;
	struct	words *link;
	struct	words *fail;
} w[MAXSIZ], *smax, *q;

long	lnum;
int	bflag, cflag, fflag, lflag, nflag, vflag, xflag, yflag;
int	hflag	= 1;
int	sflag;
int	retcode = 0;
int	nfile;
long	blkno;
int	nsucc;
long	tln;
FILE	*wordf;
char	*argptr;

#if defined(__stdc__) || defined(__STDC__)
void execute(char *file);
int getargc(void);
void cgotofn(void);
void overflo(void);
void cfail(void);
#endif

#if defined(__stdc__) || defined(__STDC__)
int
main(int argc, char **argv)
#else
main(argc, argv)
char **argv;
#endif
{
	while (--argc > 0 && (++argv)[0][0]=='-')
		switch (argv[0][1]) {

		case 's':
			sflag++;
			continue;

		case 'h':
			hflag = 0;
			continue;

		case 'b':
			bflag++;
			continue;

		case 'c':
			cflag++;
			continue;

		case 'e':
			argc--;
			argv++;
			goto out;

		case 'f':
			fflag++;
			continue;

		case 'l':
			lflag++;
			continue;

		case 'n':
			nflag++;
			continue;

		case 'v':
			vflag++;
			continue;

		case 'x':
			xflag++;
			continue;

		case 'i':		/* Berkeley */
		case 'y':		/* Btl */
			yflag++;
			continue;
		default:
			fprintf(stderr, "fgrep: unknown flag\n");
			continue;
		}
out:
	if (argc<=0)
#if defined(__stdc__) || defined(__STDC__)
		return (2);
#else
		exit(2);
#endif
	if (fflag) {
		wordf = fopen(*argv, "r");
		if (wordf==NULL) {
			fprintf(stderr, "fgrep: can't open %s\n", *argv);
#if defined(__stdc__) || defined(__STDC__)
			return (0);
#else
			exit(0);
#endif
		}
	}
	else argptr = *argv;
	argc--;
	argv++;

	cgotofn();
	cfail();
	nfile = argc;
	if (argc<=0) {
		if (lflag)
#if defined(__stdc__) || defined(__STDC__)
			return (0);
#else
			exit (0);
#endif
		execute((char *)NULL);
	}
	else while (--argc >= 0) {
		execute(*argv);
		argv++;
	}
#if defined(__stdc__) || defined(__STDC__)
	return (0);
#else
	exit(0);
#endif
}

# define ccomp(a,b) (yflag ? lca(a)==lca(b) : a==b)
# define lca(x) (isupper(x) ? tolower(x) : x)
#if defined(__stdc__) || defined(__STDC__)
void
execute(char *file)
#else
execute(file)
char *file;
#endif
{
	register struct words *c;
	register int ccount;
	register char ch;
	register char *p;
	char buf[2*BUFSIZ];
	int f;
	int failed;
	char *nlp;
	if (file) {
		if ((f = open(file, 0)) < 0) {
			fprintf(stderr, "fgrep: can't open %s\n", file);
			retcode = 0;
			return;
		}
	}
	else f = 0;
	ccount = 0;
	failed = 0;
	lnum = 1;
	tln = 0;
	blkno = 0;
	p = buf;
	nlp = p;
	c = w;
	for (;;) {
		if (--ccount <= 0) {
			if (p == &buf[2*BUFSIZ]) p = buf;
			if (p > &buf[BUFSIZ]) {
				if ((ccount = read(f, p, &buf[2*BUFSIZ] - p)) <= 0) break;
			}
			else if ((ccount = read(f, p, BUFSIZ)) <= 0) break;
			blkno += ccount;
		}
		nstate:
			if (ccomp(c->inp, *p)) {
				c = c->nst;
			}
			else if (c->link != 0) {
				c = c->link;
				goto nstate;
			}
			else {
				c = c->fail;
				failed = 1;
				if (c==0) {
					c = w;
					istate:
					if (ccomp(c->inp ,  *p)) {
						c = c->nst;
					}
					else if (c->link != 0) {
						c = c->link;
						goto istate;
					}
				}
				else goto nstate;
			}
		if (c->out) {
			while (*p++ != '\n') {
				if (--ccount <= 0) {
					if (p == &buf[2*BUFSIZ]) p = buf;
					if (p > &buf[BUFSIZ]) {
						if ((ccount = read(f, p, &buf[2&BUFSIZ] - p)) <= 0) break;
					}
					else if ((ccount = read(f, p, BUFSIZ)) <= 0) break;
					blkno += ccount;
				}
			}
			if ( (vflag && (failed == 0 || xflag == 0)) || (vflag == 0 && xflag && failed) )
				goto nomatch;
	succeed:	nsucc = 1;
			if (cflag) tln++;
			else if (sflag)
				;	/* ugh */
			else if (lflag) {
				printf("%s\n", file);
				close(f);
				return;
			}
			else {
				if (nfile > ONE && hflag) printf("%s:", file);
				if (bflag) printf("%ld:", (blkno-ccount-1)/BUFSIZ);
				if (nflag) printf("%ld:", lnum);
				if (p <= nlp) {
					while (nlp < &buf[2*BUFSIZ]) putchar(*nlp++);
					nlp = buf;
				}
				while (nlp < p) putchar(*nlp++);
			}
	nomatch:	lnum++;
/*
 * Abort after the GIVE_UP'th line
 */
 if (lnum > GIVE_UP) { close(f); return; }
			nlp = p;
			c = w;
			failed = 0;
			continue;
		}
		if (*p++ == '\n')
			if (vflag) goto succeed;
			else {
				lnum++;
/*
 * Abort after the GIVE_UP'th line
 */
 if (lnum > GIVE_UP) { close(f); return; }
				nlp = p;
				c = w;
				failed = 0;
			}
	}
	close(f);
	if (cflag) {
		if (nfile > ONE)
			printf("%s:", file);
		printf("%ld\n", tln);
	}
}

#if defined(__stdc__) || defined(__STDC__)
int 
getargc(void)
#else
getargc()
#endif
{
	register int c;
	if (wordf)
		return(getc(wordf));
	if ((c = *argptr++) == '\0')
		return(EOF);
	return(c);
}

#if defined(__stdc__) || defined(__STDC__)
void cgotofn(void)
#else
cgotofn()
#endif
{
	register int c;
	register struct words *s;

	s = smax = w;
nword:	for(;;) {
		c = getargc();
		if (c==EOF)
			return;
		if (c == '\n') {
			if (xflag) {
				for(;;) {
					if (s->inp == c) {
						s = s->nst;
						break;
					}
					if (s->inp == 0) goto nenter;
					if (s->link == 0) {
						if (smax >= &w[MAXSIZ -1]) overflo();
						s->link = ++smax;
						s = smax;
						goto nenter;
					}
					s = s->link;
				}
			}
			s->out = 1;
			s = w;
		} else {
		loop:	if (s->inp == c) {
				s = s->nst;
				continue;
			}
			if (s->inp == 0) goto enter;
			if (s->link == 0) {
				if (smax >= &w[MAXSIZ - 1]) overflo();
				s->link = ++smax;
				s = smax;
				goto enter;
			}
			s = s->link;
			goto loop;
		}
	}

	enter:
	do {
		s->inp = c;
		if (smax >= &w[MAXSIZ - 1]) overflo();
		s->nst = ++smax;
		s = smax;
	} while ((c = getargc()) != '\n' && c!=EOF);
	if (xflag) {
	nenter:	s->inp = '\n';
		if (smax >= &w[MAXSIZ -1]) overflo();
		s->nst = ++smax;
	}
	smax->out = 1;
	s = w;
	if (c != EOF)
		goto nword;
}

#if defined(__stdc__) || defined(__STDC__)
void overflo(void)
#else
overflo()
#endif
{
	fprintf(stderr, "wordlist too large\n");
	exit(2);
}
#if defined(__stdc__) || defined(__STDC__)
void cfail(void)
#else
cfail()
#endif
{
	struct words *queue[QSIZE];
	struct words **front, **rear;
	struct words *state;
	int bstart;
	register char c;
	register struct words *s;
	s = w;
	front = rear = queue;
init:	if ((s->inp) != 0) {
		*rear++ = s->nst;
		if (rear >= &queue[QSIZE - 1]) overflo();
	}
	if ((s = s->link) != 0) {
		goto init;
	}

	while (rear!=front) {
		s = *front;
		if (front == &queue[QSIZE-1])
			front = queue;
		else front++;
	cloop:	if ((c = s->inp) != 0) {
			bstart = 0;
			*rear = (q = s->nst);
			if (front < rear)
				if (rear >= &queue[QSIZE-1])
					if (front == queue) overflo();
					else rear = queue;
				else rear++;
			else
				if (++rear == front) overflo();
			state = s->fail;
		floop:	if (state == 0) {
				state = w;
				bstart = 1;
			}
			if (state->inp == c) {
			qloop:	q->fail = state->nst;
				if ((state->nst)->out == 1) q->out = 1;
				if ((q = q->link) != 0) goto qloop;
			}
			else if ((state = state->link) != 0)
				goto floop;
			else if(bstart == 0){
				state = 0;
				goto floop;
			}
		}
		if ((s = s->link) != 0)
			goto cloop;
	}
}
