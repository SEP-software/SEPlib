! tridiagonal simultaneous equations as in FGDP and IEI
!
subroutine tris( n, endl, a, b, c, endr, d, t )
integer i,       n
real endl, a, b, c, endr, d(n), t(n)
real e(n), f(n), deni(n)
if ( n .eq. 1) then
  t(1) = d(1) / b
  return
end if
e(1) = - a / endl
do i= 2, n-1  
  deni(i) = 1. / ( b + c * e(i-1) )
  e(i) = - a * deni(i)
end do 
f(1) = d(1) / endl
do i= 2, n-1
  f(i) = (d(i) - c * f(i-1)) * deni(i)
end do 
t(n) = ( d(n) - c * f(n-1) )  /  ( endr + c * e(n-1) )
do i= n-1, 1, -1
  t(i) = e(i) * t(i+1) + f(i)
end do 
return
end  
