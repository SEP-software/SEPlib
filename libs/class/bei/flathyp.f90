! Flat topped hyperbolas and constant-offset section migration
!
subroutine flathyp(   adj, add, vel    , h, t0,dt,dx, modl,nt,nx, data&
  &)
integer ix,iz,it,ib,  adj, add,                            nt,nx
real    t, amp, z,b,            vel(nt), h, t0,dt,dx, modl(nt,nx),data&
  &(nt,nx)
call adjnull(        adj, add,                        modl,nt*nx, data&
  &,nt*nx)
do ib= -nx, nx  
  b = dx * ib             ! b = midpt separation y-y0
  do iz= 2, nt  
    z = t0 + dt * (iz-1)    ! z = zero-offset time
    t = .5 * ( sqrt( z**2 +((b-h)*2/vel(iz))**2) +sqrt( z**2 +((b+h)*2&
      &/vel(iz))**2)   )
    it = 1.5 + (t - t0) / dt
    if ( it > nt ) then
      exit
    end if
    amp = (z/t)/ sqrt(t)
    do ix= max0(1, 1-ib),  min0(nx, nx-ib)
      if ( adj .eq. 0 ) then
        data(it,ix+ib)= data(it,ix+ib) + modl(iz,ix   ) * amp
      else
        modl(iz,ix   )= modl(iz,ix   ) + data(it,ix+ib) * amp
      end if
    end do
  end do
end do 
return
end  
