!       Convolve and correlate (adjoint convolve).
!
subroutine contran( adj, add, nx, xx, nb, bb, yy)
integer ix, ib, ny, adj, add, nx,     nb
real    xx(nx)                  ! input signal
real    bb(nb)                  
! filter      (or output crosscorrelation)
real    yy(nx+nb-1)             
! filtered signal (or second input signal)
ny = nx + nb - 1                ! length of filtered signal
call adjnull(       adj, add,         bb, nb, yy, ny)
do ib= 1, nb  
  do ix= 1, nx  
    if ( adj .eq. 0 ) then
      yy( ib+ix-1) = yy( ib+ix-1) + xx( ix) * bb(ib)
    else
      bb( ib)      = bb( ib)      + xx( ix) * yy( ib+ix-1)
    end if
  end do
end do 
return
end  
