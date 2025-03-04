/* Conversion between line and Cartesian coordinates of a vector. */
/*
  Copyright (C) 2004 University of Texas at Austin
  
  This program is free software; you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation; either version 2 of the License, or
  (at your option) any later version.
  
  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.
  
  You should have received a copy of the GNU General Public License
  along with this program; if not, write to the Free Software
  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
*/

#include "sergey_rsf.h"

void sf_line2cart( int dim       /* number of dimensions */, 
		   const int* nn /* box size [dim] */, 
		   int i         /* line coordinate */, 
		   int* ii       /* cartesian coordinates [dim] */)
/*< Convert line to Cartesian >*/
{
    int axis;
 
    for (axis = 0; axis < dim; axis++) {
	ii[axis] = i%nn[axis];
	i /= nn[axis];
    }
}

int sf_cart2line( int dim       /* number of dimensions */, 
		  const int* nn /* box size [dim] */, 
		  const int* ii /* cartesian coordinates [dim] */) 
/*< Convert Cartesian to line >*/
{
    int i, axis;

    if (dim < 1) return 0;

    i = ii[dim-1];
    for (axis = dim-2; axis >= 0; axis--) {
	i = i*nn[axis] + ii[axis];
    }
    return i;
}

int sf_first_index (int i        /* dimension [0...dim-1] */, 
		    int j        /* line coordinate */, 
		    int dim      /* number of dimensions */, 
		    const int *n /* box size [dim] */, 
		    const int *s /* step [dim] */)
/*< Find first index for multidimensional transforms >*/
{
    int i0, n123, k, ii;

    n123 = 1;
    i0 = 0;
    for (k=0; k < dim; k++) {
	if (k == i) continue;
	ii = (j/n123)%n[k]; /* to cartesian */
	n123 *= n[k];	
	i0 += ii*s[k];      /* back to line */
    }

    return i0;
}

/* 	$Id: decart.c 716 2004-07-20 18:58:08Z fomels $	 */
