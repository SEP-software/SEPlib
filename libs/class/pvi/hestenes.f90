subroutine hestenes( nx,x, nr,yy,rr, aaa, niter)
integer i, iter,     nx,   nr,            niter
real    alpha, beta, gamma, gammam
real    dot
real    x(nx), yy(nr), rr(nr), aaa(nr,nx)
real g(nx), s(nx), ss(nr)
do i= 1, nx
  x(i) = 0.
end do 
do i= 1, nr
  rr(i) = yy(i)
end do 
call matmult( 1, aaa, nx,g, nr,yy)
do i= 1, nx
  s(i) = g(i)
end do 
gammam = dot(nx,g,g)
do iter= 0, niter  
  call matmult( 0, aaa, nx,s, nr,ss)
  alpha = gammam / dot(nr,ss,ss)
  do i = 1, nx
    x(i) = x(i) + alpha*s(i)
  end do 
  do i = 1, nr
    rr(i) = rr(i) - alpha*ss(i)
  end do 
  call matmult( 1, aaa, nx,g, nr,rr)
  gamma = dot(nx,g,g)
  beta = gamma / gammam
  gammam = gamma
  do i = 1, nx
    s(i) = g(i) + beta*s(i)
  end do
end do 
return
end  
