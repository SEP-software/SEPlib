! complex tridiagonal equation solver
subroutine ctris( n, endl, a, b, c, endr, d, q)
integer i,        n
complex q(n), d(n), a, b, c, den, endl, endr
complex f(n), e(n)
e(1) = -a/endl
f(1) = d(1)/endl
do i= 2, n-1  
  den = b+c*e(i-1)
  e(i) = -a/den
  f(i) = (d(i)-c*f(i-1))/den
end do 
q(n) = (d(n)-c*f(n-1)) / (endr+c*e(n-1))
do i= n-1, 1, -1
  q(i) = e(i) * q(i+1) + f(i)
end do 
return
end  
