
! MISSIF -- find MISSing Input data and Filter on 1-axis by min power out.
!
subroutine missif ( na, lag, aa, np, pp, known, niter)
use sep_func_mod
integer iter,      na, lag,     np,            niter, nx, ax, px, ip,&
  & nr
real    pp(np)          
! input: known data with zeros for missing values.
! output: known plus missing data.
real    known(np)       
! known(ip) vanishes where p(ip) is a missing value.
real    aa(na)          ! input and output: roughening filter
real  x(np+na), g(np+na), s(np+na)
real  rr(np+na-1), gg(np+na-1), ss(np+na-1)
nr= np+na-1
nx= np+na
px=1
ax=1+np
call copy( np,  pp, x(px))
call copy( na,  aa, x(ax))
if ( aa(lag) .eq. 0. ) then
  call erexit('missif: a(lag)== 0.')
end if
do iter= 0, niter  
  call contran( 0, 0, na,aa, np, pp,    rr)
  call scaleit  (         -1., nr,        rr)
  call contran( 1, 0, na,aa, np, g(px), rr)
  call contran( 1, 0, np,pp, na, g(ax), rr)
  do ip= 1, np
    if ( known(ip) .ne. 0) then
      g( ip) = 0.     
    end if
  end do 
  g( lag+np) = 0.                 
  call contran( 0, 0, na,aa, np, g(px), gg)
  call contran( 0, 1, np,pp, na, g(ax), gg)
  call cgstep( iter, nx, x, g, s, nr, rr, gg, ss)
  call copy( np, x(px), pp)
  call copy( na, x(ax), aa)
end do 
return
end  
