! linear moveout
!
subroutine lmo( adj,add, slow, tau0, t0,dt, x0,dx, modl,nt,nx,  data  &
  &     )
integer         adj,add,                                nt,nx,       it&
  &,ix,iu
real t, x, tau,          slow, tau0, t0,dt, x0,dx, modl(nt,nx), data(nt&
  &,nx)
call adjnull(   adj,add,                           modl,nt*nx,  data,nt&
  &*nx)
do ix= 1, nx  
  x= x0 + dx * (ix-1)
  do it= 1, nt  
    t= t0 + dt * (it-1)
    tau =  t - x * slow
    iu = 1.5001 + (tau-tau0)/dt
    if ( 0 < iu  .and.  iu <= nt) then
      if ( adj .eq. 0 ) then
        data(it,ix) = data(it,ix) + modl(iu,ix)
      else
        modl(iu,ix) = modl(iu,ix) + data(it,ix)
      end if
    end if
  end do
end do 
return
end  
