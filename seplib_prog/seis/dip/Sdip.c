/*$
                                                                                              
=head1 NAME
                                                                                              
 Sdip - Estimate dip (Sergey Fomel's method)
                                                                                              
=head1 DESCRIPTION
                                                                                              
        3-D dip estimation by plane wave destruction.
                                                                                              
=head1 PARAMETERS

=item idip  - sepfile

      [none]  initial in-line dip

=item mask  - sepfile 

     [none]  mask on where to calculate dip

=item liter -  int

    [20] number of linear iterations

=item n4 -  int

    [2] What to compute in 3-D. 0: in-line, 1: cross-line, 2: both

=item niter - int

    [5]  number of non-linear iteartions


=item nj1   -  int

     [1]  in-line antialiasing

=item nj2   -  int

     [1]  cross-line antialiasing

=item order   -  int

     [1,2,3]  accuracy order

=item p0   -  float

     [0.] initial in-line dip

=item q0   -  float

     [0.]  initial cross-line dip

=item rect1,rect2,rect3 - integer

      [1,1,1]  Dip smoothness

=item pmin,pmax - float

     [none,none]  Minimum and maximum inline dip

=item qmin,qmax - float

     [none,none]  Minimum and maximum cross-line dip

=item verb - boolean

     [n] verbosity flag


=item xdip - sepfile

    [none] initial cross-line dip
                                                                                              
=item maxsize  - integer

      [100]  amount of memory (in megabytes) to use by default

=head1 SYNOPSIS

  Sdip < in.H > out.H mask=mask.H idip=idip0.H xdip=xdip0.H n4=2 niter=5 liter=20 rect1=1 rect2=1 rect3=1 p0=0. q0=0. order=1 nj1=1 nj2=1 verb=n pmin=-FLT_MAX pmax=+FLT_MAX qmin=-FLT_MAX qmax=+FLT_MAX mask= idip= xdip=
                                                                                              
=head1 SEE ALSO
                                                                                              
L<Dip>,L<Dipintegrator>
                                                                                              
=head1 CATEGORY
                                                                                              
B<seis/dip>
                                                                                              
=cut
                                                                                              
>*/

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

#include <sergey_rsf.h>
#include<seplib.h>
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


    initpar(argc,argv);
sep_add_doc_line("NAME");
sep_add_doc_line("     Sdip - Estimate dip (Sergey Fomel's method)");
sep_add_doc_line("");
sep_add_doc_line("DESCRIPTION");
sep_add_doc_line("            3-D dip estimation by plane wave destruction.");
sep_add_doc_line("");
sep_add_doc_line("PARAMETERS");
sep_add_doc_line("    idip - sepfile");
sep_add_doc_line("          [none]  initial in-line dip");
sep_add_doc_line("");
sep_add_doc_line("    mask - sepfile");
sep_add_doc_line("         [none]  mask on where to calculate dip");
sep_add_doc_line("");
sep_add_doc_line("    liter - int");
sep_add_doc_line("        [20] number of linear iterations");
sep_add_doc_line("");
sep_add_doc_line("    n4 - int");
sep_add_doc_line("        [2] What to compute in 3-D. 0: in-line, 1: cross-line, 2: both");
sep_add_doc_line("");
sep_add_doc_line("    niter - int");
sep_add_doc_line("        [5]  number of non-linear iteartions");
sep_add_doc_line("");
sep_add_doc_line("    nj1 - int");
sep_add_doc_line("         [1]  in-line antialiasing");
sep_add_doc_line("");
sep_add_doc_line("    nj2 - int");
sep_add_doc_line("         [1]  cross-line antialiasing");
sep_add_doc_line("");
sep_add_doc_line("    order - int");
sep_add_doc_line("         [1,2,3]  accuracy order");
sep_add_doc_line("");
sep_add_doc_line("    p0 - float");
sep_add_doc_line("         [0.] initial in-line dip");
sep_add_doc_line("");
sep_add_doc_line("    q0 - float");
sep_add_doc_line("         [0.]  initial cross-line dip");
sep_add_doc_line("");
sep_add_doc_line("    rect1,rect2,rect3 - integer");
sep_add_doc_line("          [1,1,1]  Dip smoothness");
sep_add_doc_line("");
sep_add_doc_line("    pmin,pmax - float");
sep_add_doc_line("         [none,none]  Minimum and maximum inline dip");
sep_add_doc_line("");
sep_add_doc_line("    qmin,qmax - float");
sep_add_doc_line("         [none,none]  Minimum and maximum cross-line dip");
sep_add_doc_line("");
sep_add_doc_line("    verb - boolean");
sep_add_doc_line("         [n] verbosity flag");
sep_add_doc_line("");
sep_add_doc_line("    xdip - sepfile");
sep_add_doc_line("        [none] initial cross-line dip");
sep_add_doc_line("");
sep_add_doc_line("    maxsize - integer");
sep_add_doc_line("          [100]  amount of memory (in megabytes) to use by default");
sep_add_doc_line("");
sep_add_doc_line("SYNOPSIS");
sep_add_doc_line("      Sdip < in.H > out.H mask=mask.H idip=idip0.H xdip=xdip0.H n4=2 niter=5 liter=20 rect1=1 rect2=1 rect3=1 p0=0. q0=0. order=1 nj1=1 nj2=1 verb=n pmin=-FLT_MAX pmax=+FLT_MAX qmin=-FLT_MAX qmax=+FLT_MAX mask= idip= xdip=");
sep_add_doc_line("");
sep_add_doc_line("SEE ALSO");
sep_add_doc_line("    Dip,Dipintegrator");
sep_add_doc_line("");
sep_add_doc_line("CATEGORY");
sep_add_doc_line("    seis/dip");
sep_add_doc_line("");

    doc(SOURCE);

    sf_init(argc,argv);
    in = sf_input ("in");
    out = sf_output ("out");
    sep_begin_prog();
    
	fprintf(stderr,"memsize %d",memsize);

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

    if (!sf_getint("maxsize",&mem)) mem = 100;
    /* Available memory size (in Mb) */
    memsize = mem * (1 << 20); /* convert Mb to bytes */
	fprintf(stderr,"memsize %d",memsize);

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
    
    sep_end_prog();
    exit (0);
}

/* 	$Id: Mdip.c 1131 2005-04-20 18:19:10Z fomels $	 */
