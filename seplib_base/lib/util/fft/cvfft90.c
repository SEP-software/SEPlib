/*$

=head1 NAME

 cvfft - Complex fft

=head1 SYNOPSIS

     void cvfft (x,lx,nx,isign,scale)

=head1 INPUT PARAMETERS

=over 4

=item  x   - complex     

       input/output array

=item  lx  - int         

       length of complex vectors

=item  nx  - int         

       number of vectors; must be a power of 2

=item  isign-int         

       sign of sqrt(-1)

=item  scale-double     

       scale factor; sqrt(1./lx) conserves energy

=back

=head1 DESCRIPTION

     Complex fast Fourier transform between vectors of an array.  
     Cvfft takes a 2D panel and does a complex fast fourier
     transform across the second dimension, of all the time 
     samples. The arguments are as follows:

=head1 SEE ALSO

L<refft>,L<rvfft>,L<cvfft>

=head1 LIBRARY

B<sepfft>

=cut

>*/

/* Four fft subroutines based on the algorithm used in fork (FGDP, p. 12) 
 * and modeled after Clayton's and Ottolini's subroutines
 *********************************************************************
 *								     *
 *		       lx-1					     *
 *	x(k) = scale * sum  [x(j)*exp(isign*2*pi*sqrt(-1)*j*k/lx]    *
 *		       j=0					     *
 *								     *
 *********************************************************************
 *
 *		refft (x,lx,isign,scale,mode)
 *		cefft (x,lx,isign,scale)
 *		rvfft (x,lx,nx,isign,scale,mode)
 *		cvfft (x,lx,nx,isign,scale)
 *
 * See each subroutine below for a description of the arguments.
 * Dave Hale, 3/17/82
 * Modified  5/8/96  Stew Levin  (Mobil) corrected ROWCC declaration
 *                        for Fortran subroutine linkage.
 */
#include<sepfftf.h>
/* 	cvfft	nx complex vectors to nx complex vectors in core
 *
 *	x	input/output array
 *	lx	length of complex vectors
 *	nx	number of vectors; must be a power of 2
 *	isign	sign of sqrt(-1)
 *	scale	scale factor; sqrt(1./nx) conserves energy
*/
#if NeedFunctionPrototypes
_XFUNCPROTOBEGIN
int cvfft (complex *x,int lx,int nx,int isign,double scale)
_XFUNCPROTOEND
#else
int cvfft (x,lx,nx,isign,scale)
complex *x;
int lx,nx,isign; double scale;
#endif
#if defined CONVEX || defined __convex__
   { 
    float rscale;
    static int ione = 1;
    int sign2, ierr, nelt;

    if(isign > 0) {
	sign2 = -1;
	rscale = scale * ((float) nx);
    } else {
	sign2 = 1;
	rscale = scale;
    }

    cffts_(x,&nx,&lx,&lx,&ione,&sign2,&ierr);
    if(ierr!=0) seperr("cffts ierr=%d\n",ierr);

    if(rscale != 1.0) {
	 nelt = lx*nx*2;
	 sscal_(&nelt,&rscale,x,&ione);
    }
   }
#else
   {
    float rscale, sign2, *xx;

    rscale = scale;
    sign2 = (float) isign;
    xx = (float *) x;
		
    ROWCC(lx,nx,xx,sign2,rscale);

	return 0;
   }
#endif
