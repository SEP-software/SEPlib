subroutine ftu( signi, nx, cx )
use sep_func_mod
!   complex fourier transform with unitary scaling
!
!               1         nx          signi*2*pi*i*(j-1)*(k-1)/nx
!   cx(k)  =  -------- * sum cx(j) * e
!             sqrt(nx)   j=1             for k=1,2,...,nx=2**integer
!
integer nx, i, j, k, m, istep, pad2
real    signi, scale, arg
complex cx(nx), cmplx, cw, cdel, ct
if ( nx .ne. pad2(nx) ) then
  call erexit('ftu: nx not a power of 2')
end if
scale = 1. / sqrt( 1.*nx)
do i= 1, nx
  cx(i) = cx(i) * scale
end do 
j = 1
k = 1
do i= 1, nx  
  if (i<=j) then
    ct = cx(j)
    cx(j) = cx(i)
    cx(i) = ct
  end if
  m = nx/2
  do while  (j>m .and. m>1)
    j = j-m
    m = m/2
  end do 
! "&&" means .AND.
  j = j+m
end do 
do   
  istep = 2*k
  cw = 1.
  arg = signi*3.14159265/k
  cdel = cmplx( cos(arg), sin(arg))
  do m= 1, k  
    do i= m, nx, istep
      ct=cw*cx(i+k)
      cx(i+k)=cx(i)-ct
      cx(i)=cx(i)+ct
    end do 
    cw = cw * cdel
  end do 
  k = istep
  if (k>=nx) then
    exit
  end if
end do 
return
end  
