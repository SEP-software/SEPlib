#include <sitedef.h>
#if defined (HAVE_MOTIF) || defined(HAVE_ATHENA)
/*
code for plane object

The plane object records all planes drawn in an render
*/

#include <stdio.h>
#include "main.h"
#include "axis.h"
#include "map.h"
#include "render.h"
#include "plane.h"

Plane plane=0, lastplane=0, planelist=0;

/* initialize planes */
Plane
PlaneInit ()
	{
	int iplane;

	NEW(Plane,planelist,NPLANE);
	for (iplane=0, plane=planelist; iplane<NPLANE; iplane++, plane++) NEW(RenderAttr,plane->attr,1);
	PlaneReset ();
	return (planelist);
	}


/* find a plane given axis and frame */
Plane
PlaneFind (dir3,frame3,dir4,frame4,dir5,frame5)
int dir3,frame3,dir4,frame4,dir5,frame5;
	{
	Plane plane;

	for (plane=planelist; plane < planelist+NPLANE && 
		plane->attr->orient != NO_INDEX; plane++) {
		if (AxisDir(MapAxis(plane->zmap)) == dir3 && 
			(frame3 == NO_INDEX ||  plane->frame3 == frame3) &&
			(dir4 == NO_INDEX || (
				AxisDir(MapAxis(plane->map4)) == dir4 &&
				(frame4 == NO_INDEX ||  plane->frame4 == frame4) &&
				AxisDir(MapAxis(plane->map5)) == dir5 &&
				(frame5 == NO_INDEX ||  plane->frame5 == frame5)) )) {
			return (plane);
			}
		}
	return (0);
	}

/* empty the list */
PlaneReset ()
	{
	for (plane=planelist; plane < planelist+NPLANE; plane++) { 
		plane->attr->orient = NO_INDEX;
		}
	plane = planelist;
	}

/* record a plane */
PlaneSet (hmap,vmap,zmap,map4,map5,h0,v0,nh,nv,render,margins,attr)
Map hmap, vmap, zmap, map4, map5;
Render render;
RenderAttr attr;
int h0, v0, nh, nv, *margins;
	{
	plane->hmap = hmap;
	plane->vmap = vmap;
	plane->zmap = zmap;
	plane->map4 = map4;
	plane->map5 = map5;
	plane->frame3 = zmap->frame;
	plane->frame4 = map4->frame;
	plane->frame5 = map5->frame;
	plane->h0 = h0;
	plane->v0 = v0;
	plane->nh = nh;
	plane->nv = nv;
	plane->margins = margins;
	*(plane->attr) = *attr;
	lastplane = plane;
	plane++;
	}

/* set frame */
PlaneSetFrame (plane,frame3)
Plane plane;
int frame3;
	{
	if (!plane) return;
	plane->frame3 = frame3;
	}

/* print list of planes */
PlaneListInfo ()
	{
	Plane plane;

	printf ("Plane list:\n");
	for (plane=planelist; plane < planelist+NPLANE && 
		plane->attr->orient != NO_INDEX; plane++) {
		printf ("dir3=%d frame3=%d dir4=%d frame4=%d dir5=%d frame5=%d h0=%d v0=%d nh=%d nv=%d\n",
			AxisDir(MapAxis(plane->zmap)),plane->frame3,
			AxisDir(MapAxis(plane->map4)),plane->frame4,
			AxisDir(MapAxis(plane->map5)),plane->frame5,
			plane->h0,
			plane->v0,
			plane->nh,
			plane->nv);
		}
	}

/* return plane dir */
PlaneDir (plane)
Plane plane;
	{
	if (!plane) return (NO_INDEX);
	return (AxisDir(MapAxis(plane->zmap)));
	}

/* return plane frame */
PlaneFrame (plane)
Plane plane;
	{
	if (!plane) return (NO_INDEX);
	return (plane->frame3);
	}

/* return plane rectangle */
PlaneRect (h0,v0,nh,nv)
int *h0, *v0, *nh, *nv;
	{
	*h0 = NO_INDEX;
	*v0 = NO_INDEX;
	*nh = NO_INDEX;
	*nv = NO_INDEX;
	if (!lastplane) return;
	*h0 = lastplane->h0;
	*v0 = lastplane->v0;
	*nh = lastplane->nh;
	*nv = lastplane->nv;
	}

/* return plane skew */
PlaneSkew (plane) 
Plane plane;
	{
	if (!plane) return (0);
	return (plane->attr->skew);
	}

/* return plane type */
PlaneType (plane) 
Plane plane;
	{
	if (!plane) return (0);
	return (plane->attr->orient);
	}

/* return plane v0 */
PlaneV0 (plane) 
Plane plane;
	{
	if (!plane) return (0);
	return (plane->v0);
	}

/* return plane h0 */
PlaneH0 (plane) 
Plane plane;
	{
	if (!plane) return (0);
	return (plane->h0);
	}

/* return plane nv */
PlaneNV (plane) 
Plane plane;
	{
	if (!plane) return (0);
	return (plane->nv);
	}

/* return plane nh */
PlaneNH (plane) 
Plane plane;
	{
	if (!plane) return (0);
	return (plane->nh);
	}

/* return plane hmap */
Map
PlaneHmap (plane) 
Plane plane;
	{
	if (!plane) return (0);
	return (plane->hmap);
	}

/* return plane vmap */
Map
PlaneVmap (plane) 
Plane plane;
	{
	if (!plane) return (0);
	return (plane->vmap);
	}

/* return plane vmap */
Map
PlaneZmap (plane) 
Plane plane;
	{
	if (!plane) return (0);
	return (plane->zmap);
	}

#endif
