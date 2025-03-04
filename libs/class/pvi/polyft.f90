! Fourier transform by polynomial evaluation.
subroutine polyft( nt,tt, nw,cww )
integer nt      ! number of points in the time domain
integer nw      ! number of points in the fourier transform
real    tt(nt)  ! sampled function of time
complex cww(nw) ! sampled fourier transform
integer it, iw
real omega
complex cz, cw
do iw= 1, nw  
  omega =  3.14159265 * (iw-1.) / ( nw-1.)
  cz = cexp( cmplx( 0., omega ) )
  cw = tt(nt)
  do it= nt-1, 1, -1      ! loop runs backwards
    cw = cw * cz + tt(it)
  end do 
  cww(iw) = cw
end do 
return
end  
