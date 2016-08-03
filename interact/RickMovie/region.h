/*
region picking object
*/
#define MARK(cell)	(cell) |= 0x80
#define UNMARK(cell)	(cell) &= 0x7F
#define ISMARK(cell)	((cell) & 0x80)
#define NOTMARK(cell)	(!(((cell) & 0x80)))
#define INRANGE(cell)	(NOTMARK(cell) && (cell)>=min && (cell)<=max)
#define OUTRANGE(cell)	(((cell)&0x7F)<min || ((cell)&0x7F)>max)
#define	MARK_FACE	1
#define	MARK_EDGE	2
#define	MARK_CORNER	4
#define	REGION_NLIST	100000

typedef struct {
	int	live;		/* regions enabled */
	int	seed[4];	/* seed index */
	int	value;		/* data value at seed */
	int	bound[2];	/* range bounds */
	int	neighborhood;	/* neighborhood mode: face, edge, corner */
	Shadow	list;		/* list of marked points */
	Shadow index;		/* list of saved point indexes */
	Buffer	save;		/* value of marked points */
	int	nlist;		/* list size */
	int	size;		/* count of marked points */
	} *REgion;
/* Region used by X11/Intrinsic.h */
