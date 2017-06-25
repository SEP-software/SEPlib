/* This file is automatically generated. DO NOT EDIT! */

#ifndef _allp3_h
#define _allp3_h


typedef struct Allpass *allpass;
/* abstract data type */


allpass allpass_init(int nw                 /* filter size (1,2,3) */, 
		     int nj                 /* filter step */, 
		     int nx, int ny, int nz /* data size */, 
		     float *pp              /* data [nz*ny*nx] */);
/*< Initialize >*/


void allpass1 (bool der         /* derivative flag */, 
	       const allpass ap /* PWD object */, 
	       float* xx        /* input */, 
	       float* yy        /* output */);
/*< in-line plane-wave destruction >*/


void allpass2 (bool der         /* derivative flag */, 
	       const allpass ap /* PWD object */, 
	       float* xx        /* input */, 
	       float* yy        /* output */);
/*< cross-line plane-wave destruction >*/


void allpass3_init (allpass ap, allpass aq);
/*< Initialize linear operator >*/


void allpass3_lop (bool adj, bool add, int n1, int n2, float* xx, float* yy);
/*< PWD as linear operator >*/

#endif
