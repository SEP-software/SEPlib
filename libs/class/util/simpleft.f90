subroutine simpleft( adj, add, t0,dt,tt,nt,  f0,df,  ff,nf)
integer it,ie,       adj, add,          nt,             nf
complex cexp, cmplx,                  tt(nt),         ff(nf)
real pi2, freq, time, scale,   t0,dt,        f0,df
call adjnull(        adj, add,       tt,nt*2,        ff,nf*2 )
pi2= 2. * 3.14159265
scale = 1./sqrt( 1.*nt)
df = (1./dt) / nf
f0 =   - .5/dt  
do ie = 1, nf  
  freq= f0 + df*(ie-1)
  do it = 1, nt  
    time= t0 + dt*(it-1)
    if ( adj .eq. 0 ) then
      ff(ie)= ff(ie) + tt(it) * cexp(cmplx(0., pi2*freq*time)) * scale
    else
      tt(it)= tt(it) + ff(ie) * cexp(cmplx(0.,-pi2*freq*time)) * scale
    end if
  end do
end do 
return
end  
