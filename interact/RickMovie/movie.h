/*
movie description

animation parameters
This version uses XView timers
*/

/* direction options */
#define	MOVIE_REVERSE	-1
#define	MOVIE_FORWARD	1

/* Movie object */
typedef struct {
	int	dir;	/* direction */
	int	run;	/* movie on or off */
	int	delay;	/* delay: 100 = 5 seconds */
	int	cache;	/* save frames */
	} *Movie;
