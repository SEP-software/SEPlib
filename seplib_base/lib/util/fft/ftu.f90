!<
!ftu
!
! usage
! ftu (signi,nx,cx)
!
! Description
!   complex fourier transform with unitary scaling
!
! Input Parameters
! signi  - integer  sign for fourier transform
! nx     - integer  number of elements
! cx     - complex* complex vector to transform
!
! Comments
!               1         nx          signi*2*pi*i*(j-1)*(k-1)/nx
!   cx(k)  =  -------- * sum cx(j) * e
!             sqrt(nx)   j=1             for k=1,2,...,nx=2**integer
! Category
! Lib:Fft
!
! COMPILE LEVEL
! DISTR
!>
subroutine ftu( signi, nx, cx )
use sep_mod
integer        nx, i, j, k, m, istep, pad2,a
real        signi, scale, arg
complex        cx(nx), cmplx, cw, cdel, ct
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
! "&" means .AND.
  j = j+m
end do 
a=0
do while (a.eq.0)
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
integer function pad2(nx)
integer nx,n
n=1
do while (n < nx)
  n=n*2
end do 
pad2=n
return
end  
