/* Claerbout-style adjoint zeroing. */
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

/*^*/

void sf_adjnull (bool adj /* adjoint flag */, 
		 bool add /* addition flag */, 
		 int nx   /* size of x */, 
		 int ny   /* size of y */, 
		 float* x, 
		 float* y) 
/*< Zeros out the output (unless add is true). 
  Useful first step for any linear operator. >*/
{
    int i;
    
    if(add) return;
    
    if(adj) {
	for (i = 0; i < nx; i++) {
	    x[i] = 0.;
	}
    } else {
	for (i = 0; i < ny; i++) {
	    y[i] = 0.;
	}
    }
}

#ifndef __cplusplus
/*^*/

void sf_cadjnull (bool adj /* adjoint flag */, 
		  bool add /* addition flag */, 
		  int nx   /* size of x */, 
		  int ny   /* size of y */, 
		  float complex* x, float complex* y) 
/*< adjnull version for complex data. >*/
{
    int i;
    
    if(add) return;
    
    if(adj) {
	for (i = 0; i < nx; i++) {
	    x[i] = 0.;
	}
    } else {
	for (i = 0; i < ny; i++) {
	    y[i] = 0.;
	}
    }
}

#endif
/*^*/

/* 	$Id: adjnull.c 722 2004-07-27 09:18:18Z fomels $	 */
