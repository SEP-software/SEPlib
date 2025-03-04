/* 3-D dip estimation by plane wave destruction. 

Takes: w1=n1 w2=n2 w3=n3 p1=1 p2=1 p3=1

w1,w2,w3 is window size, p1,p2,p3 is number of patches. 
*/
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
#ifndef _LARGEFILE_SOURCE
#define _LARGEFILE_SOURCE
#endif
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>

#include <rsf.h>

#include "dip3.h"
#include "mask6.h"
#include "ocpatch.h"
#include "oc.h"

int main (int argc, char *argv[])
{
    int w123,p123,n123, niter, order, nj1,nj2, i,j, liter, mem,memsize, ip,iw;
    int n[3], rect[3], nw[3], w[3], n4; 
    off_t nall;
    float p0, q0, *u, *p, win, *tent, *tmp, pmin, pmax, qmin, qmax;
    char key[3], *dipname, *wallname;
    bool verb, *m1, *m2;
    sf_file in, out, mask, dip0;
    FILE *wall, *dip;

    sf_init(argc,argv);
    in = sf_input ("in");
    out = sf_output ("out");

    if (SF_FLOAT != sf_gettype(in)) sf_error("Need float type");

    if (!sf_histint(in,"n1",&n[0])) sf_error("Need n1= in input");
    if (!sf_histint(in,"n2",&n[1])) n[1]=1;
    if (!sf_histint(in,"n3",&n[2])) n[2]=1;
    n123 = n[0]*n[1]*n[2];

    if (1 == n[2]) {
      n4=0; 
    } else {
      if (!sf_getint("n4",&n4)) n4=2;
      /* what to compute in 3-D. 0: in-line, 1: cross-line, 2: both */ 
      if (n4 > 1) sf_putint(out,"n4",n4);
    }

    if (!sf_getint("niter",&niter)) niter=5;
    /* number of iterations */
    if (!sf_getint("liter",&liter)) liter=20;
    /* number of linear iterations */

    if (!sf_getint("rect1",&rect[0])) rect[0]=1;
    if (!sf_getint("rect2",&rect[1])) rect[1]=1;
    if (!sf_getint("rect3",&rect[2])) rect[2]=1;
    /* dip smoothness */

    if (!sf_getint("memsize",&mem)) mem = 100;
    /* Available memory size (in Mb) */
    memsize = mem * (1 << 20); /* convert Mb to bytes */

    /* estimated relative window size */
    win = powf((1. + memsize/40.)/n123,1./3.);
    if (win > 1.) win=1.;
    
    for (j=0; j <3; j++) {
	snprintf(key,3,"w%d",j+1);
	if (!sf_getint(key,w+j)) {
	    w[j] = n[j]*win;
	    if (w[j] < 1) w[j]=1;
	} else if (w[j] > n[j]) {
	    w[j] = n[j];
	}

	snprintf(key,3,"p%d",j+1);
	if (!sf_getint(key,nw+j)) {
	    if (n[j] > w[j]) {
		nw[j] = 1 + 1.5*n[j]/w[j]; /* 50% overlap */
	    } else {
		nw[j] = 1;
	    }
	}
    }
    w123 = w[0]*w[1]*w[2];
    p123 = nw[0]*nw[1]*nw[2];

    if (!sf_getfloat("p0",&p0)) p0=0.;
    /* initial in-line dip */
    if (!sf_getfloat("q0",&q0)) q0=0.;
    /* initial cross-line dip */

    if (!sf_getint("order",&order)) order=1;
    /* [1,2,3] accuracy order */
    if (order < 1 || order > 3) 
	sf_error ("Unsupported order=%d, choose between 1 and 3",order);
    if (!sf_getint("nj1",&nj1)) nj1=1;
    /* in-line antialiasing */
    if (!sf_getint("nj2",&nj2)) nj2=1;
    /* cross-line antialiasing */

    if (!sf_getbool("verb",&verb)) verb = false;
    /* verbosity flag */
    if (!sf_getfloat("pmin",&pmin)) pmin = -FLT_MAX;
    /* minimum inline dip */
    if (!sf_getfloat("pmax",&pmax)) pmax = +FLT_MAX;
    /* maximum inline dip */
    if (!sf_getfloat("qmin",&qmin)) qmin = -FLT_MAX;
    /* minimum cross-line dip */
    if (!sf_getfloat("qmax",&qmax)) qmax = +FLT_MAX;
    /* maximum cross-line dip */

    /* initialize dip estimation */
    dip3_init(w[0], w[1], w[2], rect, liter);

    u = sf_floatalloc(w123);
    p = sf_floatalloc(w123);

    /* Fix later for patching mask */
    if (p123 == 1 && NULL != sf_getstring("mask")) {
	m1 = sf_boolalloc(n123);
	m2 = sf_boolalloc(n123);
	mask = sf_input("mask");
	sf_floatread(u,n123,mask);
	mask32 (order, nj1, nj2, n[0], n[1], n[2], u, m1, m2);
    } else {
	m1 = NULL;
	m2 = NULL;
    }

    if (p123 > 1) {
	sf_warning("Going out of core...");
	sf_warning("window: %d %d %d",w[0],w[1],w[2]);
	sf_warning("patches: %d %d %d",nw[0],nw[1],nw[2]);

	nall = n123*sizeof(float);

	sf_unpipe(in,nall);
	dip = sf_tempfile(&dipname,"w+b");
	wall = sf_tempfile(&wallname,"w+b");
	
	tent = sf_floatalloc(w123);
	tmp = sf_floatalloc(w123);

	sf_tent2 (3, w, tent);

	ocpatch_init(3,w123,p123,nw,n,w);

	if (1 != n4) {
	    oc_zero(nall,dip);
	    oc_zero(nall,wall);
	    
	    /* loop over patches */
	    for (ip=0; ip < p123; ip++) {
		/* read data */
		ocpatch_flop (ip,false,in,u);
		
		/* initialize t-x dip */
		for(i=0; i < w123; i++) {
		    p[i] = p0;
		}
		
		/* estimate t-x dip */
		dip3(1, niter, order, nj1, verb, u, p, m1, pmin, pmax);
		
		/* write weight */
		ocpatch_lop (ip,false,wall,tmp);
		for (iw=0; iw < w123; iw++) {
		    tmp[iw] += tent[iw];
		}
		ocpatch_lop (ip,true,wall,tmp);
		
		/* write dip */
		ocpatch_lop (ip,false,dip,tmp);
		for (iw=0; iw < w123; iw++) {
		    tmp[iw] += tent[iw]*p[iw];
		}
		ocpatch_lop (ip,true,dip,tmp);
	    }
	    
	    oc_divide(nall,dip,wall,out);
	}

	if (0 == n4) { /* done if only t-x dip */
	    unlink(dipname);
	    unlink(wallname);
	    exit(0);
	}

	oc_zero(nall,dip);
	oc_zero(nall,wall);
	
        /* loop over patches */
	for (ip=0; ip < p123; ip++) {
	    /* read data */
	    ocpatch_flop (ip,false,in,u);
	    
	    /* initialize t-y dip */
	    for(i=0; i < w123; i++) {
		p[i] = q0;
	    }
	    
            /* estimate t-y dip */
	    dip3(2, niter, order, nj2, verb, u, p, m2, qmin, qmax);
	    
	    
            /* write weight */
	    ocpatch_lop (ip,false,wall,tmp);
	    for (iw=0; iw < w123; iw++) {
		tmp[iw] += tent[iw];
	    }
	    ocpatch_lop (ip,true,wall,tmp);


	    /* write dip */
	    ocpatch_lop (ip,false,dip,tmp);
	    for (iw=0; iw < w123; iw++) {
		tmp[iw] += tent[iw]*p[iw];
	    }
	    ocpatch_lop (ip,true,dip,tmp);
	}

	oc_divide(nall,dip,wall,out);

	unlink(dipname);
	unlink(wallname);

    } else {
	/* read data */
	sf_floatread(u,n123,in);
	
	if (1 != n4) {
	    /* initialize t-x dip */
	    if (NULL != sf_getstring("idip")) {
		dip0 = sf_input("idip");
		sf_floatread(p,n123,dip0);
		sf_fileclose(dip0);
	    } else {
		for(i=0; i < n123; i++) {
		    p[i] = p0;
		}
	    }
	    
	    /* estimate t-x dip */
	    dip3(1, niter, order, nj1, verb, u, p, m1, pmin, pmax);
	    
	    /* write t-x dip */
	    sf_floatwrite(p,n123,out);
	}

	if (0 == n4) exit(0); /* done if only t-x dip */

	/* initialize t-y dip */
	if (NULL != sf_getstring("xdip")) {
	    dip0 = sf_input("xdip");
	    sf_floatread(p,n123,dip0);
	    sf_fileclose(dip0);
	} else {
	    for(i=0; i < n123; i++) {
		p[i] = q0;
	    }
	}	

	/* estimate t-y dip */
	dip3(2, niter, order, nj2, verb, u, p, m2, pmin, pmax);
	
	/* write t-y dip */
	sf_floatwrite(p,n123,out);
    }
    
    exit (0);
}

/* 	$Id: Mdip.c 1131 2005-04-20 18:19:10Z fomels $	 */
