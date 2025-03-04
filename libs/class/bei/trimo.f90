! moveout with triangle shaped smoothing window.
!
subroutine trimo(  adj, add, t0,dt, dx,x, nt, slow, s02, wt, anti, zz,&
  &    tt )
integer iz,itp,itm,adj, add,              nt
real                         t0,dt, dx,x, slow(nt), s02, wt, anti, zz&
  &(nt),tt(nt)
real z, t,tm,tp, amp, slope
real ss(nt)
call null(     ss,nt)
call adjnull( adj, add,                    zz,nt, tt,nt)
if ( adj .ne. 0 ) then
  call doubint( 1, 0, nt, ss, tt)
end if
do iz= 2, nt  
  z = t0 + dt * (iz-1)
  t = sqrt( z**2 + (slow(iz) * x)**2 )
  slope = anti * ( slow(iz)**2 - s02 ) * x / t
  tm = t - abs(slope * dx) - dt
  itm = 1.5 + (tm-t0) / dt
  if ( itm <= 1  ) then
    cycle
  end if
  tp = t + abs(slope * dx) + dt
  itp = 1.5 + (tp-t0) / dt
  if ( itp >= nt ) then
    exit
  end if
  amp = wt * sqrt( nt*dt/t) * z/t * (dt/(dt+tp-tm)) ** 2
  call spotw( adj, 1,  -amp, nt,t0,dt,tm, zz(iz), ss)
  call spotw( adj, 1, 2*amp, nt,t0,dt,t , zz(iz), ss)
  call spotw( adj, 1,  -amp, nt,t0,dt,tp, zz(iz), ss)
end do 
if ( adj .eq. 0) then
  call doubint( 0, add, nt, ss, tt)
end if
return
end  
