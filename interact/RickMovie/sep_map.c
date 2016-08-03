#include <sitedef.h>
#if defined (HAVE_MOTIF) || defined(HAVE_ATHENA)
/*
data axis to image axis map object
does window, zoom, frame tracking, and tic labels
*/
#include <stdio.h>
#include "main.h"
#include "axis.h"
#include "data.h"
#include "map.h"
#include "movie.h"

/*
initialize map object
*/
Map
MapInit (axis,name,imap)
Axis axis;
string name;
int imap;
	{
	Map map;
	extern Data data;
	string parname;
	int iaxis;

	NEW (Map,map,1);
	strcpy (map->name,name);
	map->axis = axis;
	map->map = 0;
	map->interp = 0;
	map->inv = 0;
	map->frame = 0;
	map->prev = 0;
	map->first = 0;
	map->frame1 = map->first;
	map->last = AxisSize(axis)-1;
	map->frame2 = map->last;
	map->dframe = 1;
	map->size = AxisSize(axis);
	/* recover saved parameters */
	if (imap > 0) {
	sprintf (parname,"axis%d",imap); if (GETPARINT (parname,"d",&iaxis)) {
		map->axis = DataAxis (data,iaxis);
		}
	sprintf (parname,"size%d",imap); GETPARINT (parname,"d",&map->size);
	sprintf (parname,"first%d",imap); GETPARINT (parname,"d",&map->first);
	sprintf (parname,"last%d",imap); GETPARINT (parname,"d",&map->last);
	sprintf (parname,"frame%d",imap); GETPARINT (parname,"d",&map->frame);
	sprintf (parname,"prev%d",imap); GETPARINT (parname,"d",&map->prev);
	sprintf (parname,"frame1%d",imap); GETPARINT (parname,"d",&map->frame1);
	sprintf (parname,"frame2%d",imap); GETPARINT (parname,"d",&map->frame2);
	sprintf (parname,"dframe%d",imap); GETPARINT (parname,"d",&map->dframe);
		}
	MapSet (map,map->axis,map->size,map->first,map->last,map->frame1,map->frame2,map->dframe);
	return (map);
	}

/*
set map to given data axis, map, and bounds
used when changing orientation and magnification
*/
MapSet (map,axis,size,first,last,frame1,frame2,dframe)
Map map;
Axis axis;
int first, last, size, frame1, frame2, dframe;
	{
	int resize = 0;

	if (!map || !axis) return;
	if (first == last) return;
	if (axis != map->axis ||last != map->last || first != map->first || size != map->size) {
		resize = 1;
		}
	map->axis = axis;
	map->first = MapBound (first,0,AxisSize(axis)-1);
	map->last = MapBound (last,0,AxisSize(axis)-1);
	map->frame1 = MapBound (frame1,map->first,map->last);
	map->frame2 = MapBound (frame2,map->first,map->last);
	map->dframe = map->dframe > 0 ? map->dframe : -map->dframe;
	MapSetFrame (map,map->frame);
	map->size = size;
	if (resize) {
		MapSetSize (map,size);
		}
	}

/* internal utility for forcing index within bounds */
MapBound (index,bound1,bound2)
int index, bound1, bound2;
	{
	if (bound1 < bound2) {
		index = index > bound1 ? index : bound1;
		index = index < bound2 ? index : bound2;
		}
	else	{
		index = index < bound1 ? index : bound1;
		index = index > bound2 ? index : bound2;
		}
	return (index);
	}
/*
compute data to image maps
compute tic spacing
*/
MapSetSize (map,size)
Map map;
int size;
	{
	int i, j, len;
	float index;

	if (!map || size<=0) return;
	FREE(map->map);
	FREE(map->interp);
	FREE(map->inv);
	NEW(Vec,map->map,size);
	NEW(Vec,map->interp,size);
	NEW(Vec,map->inv,AxisSize(map->axis));
	j = AxisStride(map->axis);
	len = map->last - map->first;
	if (map->first < map->last) {
		for (i=0; i<size; i++) {
			/* nearest neighbor interpolation */
			index = map->first + (float)(i * (map->last - map->first + 1)) / (float)(size);
			map->map[i] = index;
			map->interp[i] = (index-map->map[i]) * MAP_INTERP;
			/* map scaled by stride for animation speed */
			map->map[i] *= j;
			}
		}
	else	{
		for (i=0; i<size; i++) {
			/* nearest neighbor interpolation */
			index = map->last + (float)(i * (map->first - map->last + 1)) / (float)(size);
			map->map[size-i-1] = index;
			map->interp[size-i-1] = (1. - index + map->map[size-i-1]) * MAP_INTERP;
			/* map scaled by stride for animation speed */
			map->map[size-i-1] *= j;
			}
		}
	/* inverse map mainly used for picking */
	for (i=0; i<AxisSize(map->axis); i++) {
		j = ((i - map->first) * (size - 1)) / (map->last - map->first);
		/* -1 is absent value */
		j = j > -1 ? j : NO_INDEX;
		j = j < size ? j : NO_INDEX;
		map->inv[i] = j;
		}
	if (map->size != size) {
		map->size = size;
		MapSetTics (map);
		}
	}

MapSetTics (map)
Map map;
	{
	float first, last, dtic, tic0, tic2;
	int i;
	double log10();

	first = AxisValue (map->axis,map->first);
	last = AxisValue (map->axis,map->last);
	/* interval near to MAP_TIC pixels */
	dtic = (last - first) * MAP_TIC / map->size;
	dtic = last > first ? dtic : -dtic;
	/* find nearest magnitude */
	for (map->dtic=1.; map->dtic<dtic;) map->dtic *= 10.;
	for (; map->dtic>dtic;) map->dtic *= 0.1;
	/* round to nearest 1., 2., or 5. */
	if (dtic/map->dtic > 8.0) map->dtic *= 10.;
	else if (dtic/map->dtic > 3.0) map->dtic *= 5.;
	else if (dtic/map->dtic > 1.65) map->dtic *= 2.;
	dtic = map->dtic;
	/* computer bounding tics */
	tic0 = (int)(first/dtic) * dtic;
	tic2 = (int)(last/dtic) * dtic;
	/* force between bounds */
	if (first < last) {
		tic0 = tic0 >= first ? tic0 : tic0 + dtic;
		tic2 = tic2 <= last ? tic2 : tic2 - dtic;
		map->tic0 = tic0;
		map->tic2 = tic2;
		}
	else	{
		tic0 = tic0 <= first ? tic0 : tic0 - dtic;
		tic2 = tic2 >= last ? tic2 : tic2 + dtic;
		/* tic0 < tic2 ; dtic > 0 ; despite axis orientation */
		map->tic0 = tic2;
		map->tic2 = tic0;
		}
	/* count decimal place for tic label format */
	i = dtic > 1. ? 0 : 1 - log10 (dtic);
	sprintf (map->format,"%%.%df ",i);
	/* count number of tics for position axis name between tic labels */
	map->ntic = (map->tic2 - map->tic0) / map->dtic + 1;
	map->dtic = dtic;
	}

/* swap two axes into each other's size */
MapSwap (a,b)
Map a, b;
	{
	Map_ A, B;

	A = *a;
	B = *b;
	MapSet (a,B.axis,a->size,B.first,B.last,B.frame1,B.frame2,B.dframe);
	MapSetFrame (a,B.frame);
	MapSet (b,A.axis,b->size,A.first,A.last,A.frame1,A.frame2,A.dframe);
	MapSetFrame (b,A.frame);
	}

/* change direction of axis, perserving size and bounds */
MapFlip (map)
Map map;
	{
	MapSet (map,map->axis,map->size,map->last,map->first,map->frame2,map->frame1,map->dframe);
	}

/* return data axis of map */
Axis
MapAxis (map)
Map map;
	{
	if (!map) return (0);
	return (map->axis);
	}

/* return map name */
char*
MapName (map)
Map map;
	{
	if (!map) return (0);
	return (map->name);
	}

/* return map of map */
Vec
MapVec (map)
Map map;
	{
	if (!map) return (0);
	return (map->map);
	}

/* return map interption */
Vec
MapInterp (map)
Map map;
	{
	if (!map) return (0);
	return (map->interp);
	}

/* return size of map */
MapSize (map)
Map map;
	{
	if (!map) return (0);
	return (map->size);
	}

/* return map window size */
MapWindow (map)
Map map;
	{
	if (!map) return (0);
	if (map->last > map->first) return (map->last-map->first+1);
	else return (map->first-map->last+1);
	}

/* return zoom window size */
MapZoom (map)
Map map;
	{
	if (!map) return (0);
	if (map->last > map->first) return ((int)((map->last-map->first+1)*AxisZoom(map->axis)));
	else return ((int)((map->first-map->last+1)*AxisZoom(map->axis)));
	}

/* return first element of map */
MapFirst (map)
Map map;
	{
	if (!map) return (0);
	return (map->first);
	}

/* return last element of map */
MapLast (map)
Map map;
	{
	if (!map) return (0);
	return (map->last);
	}

/* return lowest element of map */
MapLow (map)
Map map;
	{
	if (!map) return (0);
	return (map->first<map->last?map->first:map->last);
	}

/* return highest element of map */
MapHigh (map)
Map map;
	{
	if (!map) return (0);
	return (map->first>map->last?map->first:map->last);
	}

/* return frame of map */
MapFrame (map)
Map map;
	{
	if (!map) return (0);
	return (map->frame);
	}

/* return map position */
MapFrame1 (map)
Map map;
	{
	if (!map) return (0);
	return (map->imap);
	}

/* number of frames */
MapNFrame (map)
Map map;
	{
	if (!map) return (0);
	return (map->frame2>map->frame1?(map->frame2-map->frame1+1):(map->frame1-map->frame2+1));
	}

/* return previous frame of map */
MapPrev (map)
Map map;
	{
	if (!map) return (0);
	return (map->prev);
	}

/* return saved frame of map */
MapSave (map)
Map map;
	{
	if (!map) return (0);
	return (map->save);
	}

/* return first tic of map */
float
MapTic0 (map)
Map map;
	{
	if (!map) return (0);
	return (map->tic0);
	}

/* return last tic of map */
float
MapTic2 (map)
Map map;
	{
	if (!map) return (0);
	return (map->tic2);
	}

/* return number of tics of map */
MapNtic (map)
Map map;
	{
	if (!map) return (0);
	return (map->ntic);
	}

/* return tic spacing of map */
float
MapDtic (map)
Map map;
	{
	if (!map) return (0);
	return (map->dtic);
	}

/* return start frame */
MapMovie1 (map)
Map map;
	{
	if (!map) return (0);
	return (map->frame1);
	}

/* return end frame */
MapMovie2 (map)
Map map;
	{
	if (!map) return (0);
	return (map->frame2);
	}

/* return frame increment */
MapDmovie (map)
Map map;
	{
	if (!map) return (0);
	return (map->dframe);
	}

/* return tic spacing of map */
char*
MapFormat (map)
Map map;
	{
	if (!map) return (0);
	return (map->format);
	}

/* set frame of map inclusive of bounds */
MapSetFrame (map,frame)
Map map;
int frame;
	{
	if (!map || frame<0) return;
	map->prev = MapBound (map->frame,map->frame1,map->frame2);
	map->frame = MapBound (frame,map->frame1,map->frame2);
	}

/* set frame bounds */
MapSetFrameBounds (map,frame1,frame2)
Map map;
int frame1, frame2;
	{
	if (!map) return;
	MapSet (map,map->axis,map->size,map->first,map->last,frame1,frame2,map->dframe);
	MovieSetDir (frame2-frame1);
	}

MapSetDmovie (map,dframe)
Map map;
int dframe;
	{
	if (!map) return;
	map->dframe = dframe;
	}
/* set map position */
MapSetFrame1 (map,frame)
Map map;
int frame;
	{
	if (!map) return;
	map->imap = MapBound (frame,0,map->size-1);
	}

/* compute next frame depending upon animation direction and bounds */
MapNextFrame (map)
Map map;
	{
	map->prev = map->frame;
	if (map->frame1 < map->frame2) {
		if (MovieDir() == MOVIE_FORWARD) {
			map->frame = map->frame <= map->frame2-map->dframe ? map->frame+map->dframe : map->frame1;
			}
		else	{
			map->frame = map->frame >= map->frame1+map->dframe ? map->frame-map->dframe : map->frame2;
			}
		}
	else	{
		if (MovieDir() == MOVIE_FORWARD) {
			map->frame = map->frame >= map->frame2+map->dframe ? map->frame-map->dframe : map->frame1;
			}
		else	{
			map->frame = map->frame <= map->frame1-map->dframe ? map->frame+map->dframe : map->frame2;
			}
		}
	}

/* return data axis value given map index */
float
MapValue (map,index)
Map map;
int index;
	{
	index = index > 0 ? index : 0;
	index = index < map->size ? index : map->size-1;
	/* unscale map by stride */
	return (AxisValue(map->axis,map->map[index]/AxisStride(map->axis)));
	}

/* return map index given axis value */
MapIndex (map,value)
Map map;
float value;
	{
	float first, last;
	int index;

	first = MapValue (map,0);
	last = MapValue (map,map->size-1);
	index = (map->size-1) * (value - first) / (last - first);
	index = index <= map->size ? index : NO_INDEX;
	return (index);
	}

/* return map value given index */
MapMap (map,index)
Map map;
int index;
	{
	if (!map || index<0 || index >= map->size) return (NO_INDEX);
	return (map->map[index]/map->axis->stride);
	}

/* return inverse index */
MapInverse (map,index)
Map map;
int index;
	{
	/* fprintf(stderr,"Name: %s   Index: %d   \n",map->name,index); */
	if (!map) return (NO_INDEX);
	if (index < 0) return (NO_INDEX);
	if (index >= AxisSize(map->axis)) return (NO_INDEX);
	/* index=1; */
	return (map->inv[index]);
	}

/* print map information */
MapInfo (map)
Map map;
	{
	Message message;

	if (!map) return;
	sprintf (message,
		 "Map %s: %s: %%=%g size=%d first=%d last=%d frame1=%d frame2=%d dframe=%d dtic=%g tic0=%g tic2=%g format=%s",
		
		map->name,
		AxisLabel(map->axis),
		(float)map->size/(float)AxisSize(map->axis),
		map->size,
		map->first,
		map->last,
		map->frame1,
		map->frame2,
		map->dframe,
		map->dtic,
		map->tic0,
		map->tic2,
		map->format);
	UIMessage (message);
	}

/* save map parameters */
MapSavePar (map)
Map map;
	{
	Message message;
	int imap;

	if (!map) return;
	if (!strcmp(map->name,"DOWN")) imap = 1;
	else if (!strcmp(map->name,"ACROSS")) imap = 2;
	else if (!strcmp(map->name,"DEEP")) imap = 3;
	else if (!strcmp(map->name,"4D")) imap = 3;
	else if (!strcmp(map->name,"5D")) imap = 3;
	sprintf (message, "Map%d: %s: axis%d=%d size%d=%d first%d=%d last%d=%d frame%d=%d prev%d=%d frame1=%d frame2=%d dframe=%d",
		imap,map->name,
		imap,AxisDir(map->axis),
		imap,map->size,
		imap,map->first,
		imap,map->last,
		imap,map->frame,
		imap,map->prev,
		map->frame1,
		map->frame2,
		map->dframe);
	UISaveMessage (message);
	}

/* write map vectors to files for debugging */
MapDump (map)
Map map;
	{
	string filename;
	int fd;

	sprintf (filename,"map.%s.map.%dx32",map->name,map->size);
	fd = creat (filename,0664);
	write (fd,map->map,sizeof(map->map[0])*map->size);
	close (fd);
	sprintf (filename,"map.%s.inv.%dx32",map->name,map->size);
	fd = creat (filename,0664);
	write (fd,map->inv,sizeof(map->inv[0])*map->size);
	close (fd);
	sprintf (filename,"map.%s.interp.%dx32",map->name,map->size);
	fd = creat (filename,0664);
	write (fd,map->interp,sizeof(map->interp[0])*map->size);
	close (fd);
	UIMessage ("map dumped to file");
	}

/* remember map frame */
MapSaveFrame (map)
Map map;
	{
	map->save = map->frame;
	}

/* recall map frame */
MapRestoreFrame (map)
Map map;
	{
	map->frame = map->save;
	}

#endif
