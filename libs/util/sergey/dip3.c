/* 3-D dip estimation */
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

#include <stdio.h>
#include <math.h>
#include <float.h>

#include "sergey_rsf.h"

static float *u1, *u2, *dp, *p0;
static int n, n1, n2, n3, nn[3];

void dip3_init(int m1, int m2, int m3       /* dimensions */, 
	       int* rect                    /* smoothing radius [3] */, 
	       int niter                    /* number of iterations */)
/*< initialize >*/
{
    n1=m1;
    n2=m2;
    n3=m3;
    n = n1*n2*n3;

    u1 = sf_floatalloc(n);
    u2 = sf_floatalloc(n);
    dp = sf_floatalloc(n);
    p0 = sf_floatalloc(n);

    nn[0]=n1;
    nn[1]=n2;
    nn[2]=n3;

    divn_init (3, n, nn, rect, niter);
}

void dip3_close(void)
/*< free allocated storage >*/
{
    free (u1);
    free (u2);
    free (dp);
    divn_close();
}

void dip3(int dip                 /* 1 - inline, 2 - crossline */, 
	  int niter               /* number of nonlinear iterations */, 
	  int nw                  /* filter size */, 
	  int nj                  /* filter stretch for aliasing */, 
	  bool verb               /* verbosity */, 
	  float *u                /* input data */, 
	  float* p                /* output dip */, 
	  bool* mask              /* input mask for known data */,
	  float pmin, float pmax  /* minimum and maximum dip */)
/*< estimate local dip >*/
{
    int i, iter, k;
    float mean, usum, usum2, psum, ui, pi, lam;
    allpass ap;
 
    ap = allpass_init (nw,nj,n1,n2,n3,p);

    if (dip == 1) {
	allpass1 (false, ap, u,u2);
    } else {
	allpass2 (false, ap, u,u2);
    }

    for (iter =0; iter < niter; iter++) {
	if (dip == 1) {
	    allpass1 (true,  ap, u,u1);
	} else {
	    allpass2 (true,  ap, u,u1);
	}
	
	mean = 0.;
	for(i=0; i < n; i++) {
	    ui = u1[i];
	    mean += ui*ui;
	}
	if (mean == 0.) return;

	mean = sqrt (mean/n);

	usum = 0.;
	psum = 0.;

	for(i=0; i < n; i++) {
	    u1[i] /= mean;
	    u2[i] /= mean;
	    usum += u2[i]*u2[i];
	    if (verb) psum += p[i];
	    p0[i] = p[i];
	}

	if (verb) sf_warning("%d %g %g", iter+1, sqrt(usum/n), psum/n);
	
	if (NULL != mask) {
	    for(i=0; i < n; i++) {
		if (mask[i]) {
		    u1[i] = 0.;
		    u2[i] = 0.;
		}
	    }
	}

	divn (u2, u1, dp);

	lam = 1.;
	for (k=0; k < 8; k++) {
	    for(i=0; i < n; i++) {
		pi = p0[i]+lam*dp[i];
		if (pi < pmin) pi=pmin;
		if (pi > pmax) pi=pmax;
		p[i] = pi;
	    }
	    if (dip == 1) {
		allpass1 (false, ap, u,u2);
	    } else {
		allpass2 (false, ap, u,u2);
	    }

	    usum2 = 0.;
	    for(i=0; i < n; i++) {
		usum2 += u2[i]*u2[i];
	    }
	    if (usum2 < usum*mean*mean) break;
	    lam *= 0.5;
	}
    } /* iter */

    free(ap);
}

/* 	$Id: dip3.c 1131 2005-04-20 18:19:10Z fomels $	 */
