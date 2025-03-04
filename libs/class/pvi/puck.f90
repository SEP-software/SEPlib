
! measure coherency and dip, and compute residual  res = (Dx + p Dt) uu
!
subroutine puck ( n1, n2, uu, coh, pp, res )
integer i1, i2,   n1, n2
real    uu(n1,n2), res(n1,n2), xx, xt, tt, coh, pp
real dx(n1,n2-1), dt(n1-1,n2-1)
call wavekill1( 1., 0.,  n1,n2 , uu, dx)
call wavekill1( 0., 1.,  n1,n2 , uu, dt)
xx = 1.e-30
tt = 1.e-30
xt = 0.
do i1= 1, n1-1  
  do i2= 1, n2-1  
    xt = xt + dt(i1,i2) * dx(i1,i2)
    tt = tt + dt(i1,i2) * dt(i1,i2)
    xx = xx + dx(i1,i2) * dx(i1,i2)
  end do
end do 
coh = sqrt((xt/tt)*(xt/xx))
pp  =  - xt/tt 
call wavekill1( 1., pp,  n1,n2 , uu, res)
return
end  
