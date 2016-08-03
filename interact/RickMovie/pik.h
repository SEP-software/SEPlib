/*
point pick object
*/
#ifdef __convex__
#define NPIK		100000
#endif
#ifndef __convex__
#define NPIK		25000
#endif
#define	PIK_RANGE	5
#define	PIK_SIZE	5
#define PIK_NEAR	3000
#define	PIKOP_ADD	'a'
#define	PIKOP_DELETE	'd'
#define	PIKOP_MOVE	'm'

typedef short Pik[DATA_NAXIS];
typedef struct {
	Pik		*pik;		/* piks */
	string		file;		/* pik file name */
	int		npik;		/* number of piks */
	int		nmax;		/* maximum number of piks */
	int		range;		/* planes to display on */
	int		size;		/* display size in pixels */
	int		last_op;	/* last operation */
	int		last_item;	/* last item changed */
	} *PikList;
