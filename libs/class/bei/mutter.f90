!  Data is weighted by sine squared inside a mute zone.
!  The weight is zero when      t <       x * slope0
!  The weight is one  when      t >  tp + x * slopep
!  Suggested defaults: slopep = slope0= 1./1.45 sec/km;  tp=.150 sec
!
subroutine mutter( tp, slope0,slopep, dt,dx, t0,x0, data,nt,nx)
integer it,ix,                                           nt,nx
real t,x, wt,      tp, slope0,slopep, dt,dx, t0,x0, data(nt,nx)
do ix=1,nx  
  x= x0+(ix-1)*dx
  x = abs( x)
  do it=1,nt  
    t= t0+(it-1)*dt
    if ( t <      x * slope0) then
      wt = 0
    else if ( t > tp + x * slopep) then
      wt = 1.
    else
      wt = sin(  0.5 * 3.14159265 * (t-x*slope0)/(tp+x*(slopep-slope0)&
        &)) ** 2
    end if 
    data(it,ix) = data(it,ix) * wt
  end do
end do 
return
end  
