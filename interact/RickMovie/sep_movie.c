#include <sitedef.h>
#if defined(HAVE_MOTIF) || defined(HAVE_ATHENA)
/*
movie object code
one animator shared between all parts of a view
*/
#include <sys/time.h>
#include <stdio.h>
#include "main.h"
#include "movie.h"

Movie movie = 0;

/* initialize movie object */
MovieInit ()
	{
	NEW (Movie,movie,1);
	movie->dir = MOVIE_REVERSE;
	movie->run = 0;
	movie->delay = 0;
	movie->cache = 0;
	GETPARINT ("dir","d",&movie->dir);
	GETPARINT ("run","d",&movie->run);
	GETPARINT ("delay","d",&movie->delay);
	GETPARINT ("cache","d",&movie->cache);
	}

/* return movie direction */
MovieDir ()
	{
	if (!movie) return (0);
	return (movie->dir);
	}

/* set movie direction */
MovieSetDir (dir)
int dir;
	{
	if (!movie) return;
	movie->dir = dir > 0 ? MOVIE_FORWARD : MOVIE_REVERSE;
	}

/* toggle movie direction */
MovieToggleDir ()
	{
	if (!movie) return;
	if (movie->dir == MOVIE_FORWARD) movie->dir = MOVIE_REVERSE;
	else movie->dir = MOVIE_FORWARD;
	}

/* set cache mode */
MovieToggleCache ()
	{
	if (!movie) return;
	movie->cache = 1 - movie->cache;
	}

/* return cache mode */
MovieCache ()
	{
	if (!movie) return (NO_INDEX);
	return (movie->cache);
	}

/* return delay */
MovieDelay ()
	{
	if (!movie) return (0);
	return (movie->delay);
	}

/* set run mode */
MovieSetRun (run)
int run;
	{
	if (!movie) return;
	movie->run = run;
	}

/* return run mode */
MovieRun ()
	{
	if (!movie) return (0);
	return (movie->run);
	}

/* set movie speed 0-100 */
MovieSetSpeed (speed)
int speed;
	{
	movie->delay = 100 - speed;
	/* reset timer */
	if (MovieRun()) {
		MovieOff();
		MovieOn();
		}
	}

/* start animation oscillator */
MovieOn ()
	{
	if (ViewMovieOK() == 0) return;
	movie->run = 1;
#ifdef XVIEW
	static struct itimerval	timer;
	int value;

	value = movie->delay * 20000 + 1000;
	timer.it_interval.tv_sec = value / 1000000;
	timer.it_interval.tv_usec = value % 1000000;
	timer.it_value.tv_sec = value / 1000000;
	timer.it_value.tv_usec = value % 1000000;
	UITimer (&timer);
#endif
#if defined(HAVE_ATHENA)
	ViewDrawMovie ();
#endif
#if defined(HAVE_MOTIF)
	ViewDrawMovie ();
#endif
	}

/* stop animation oscillator */
MovieOff ()
	{
	if (!movie->run) return;
	UITimer (-1,0);
	movie->run = 0;
	}

/* return movie information */
MovieInfo ()
	{
	Message message;
	extern Movie movie;

	if (!movie) return;
	sprintf (message,"Movie: dir=%d run=%d delay=%d cache=%d",
		movie->dir,
		movie->run,
		movie->delay,
		movie->cache);
	UIMessage (message);
	}

/* save movie parameters */
MovieSavePar ()
	{
	Message message;
	extern Movie movie;

	sprintf (message,"Movie: dir=%d run=%d delay=%d cache=%d",
		movie->dir,
		movie->run,
		movie->delay,
		movie->cache);
	UISaveMessage (message);
	}
#endif
