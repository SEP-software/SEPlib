! Kirchhoff migration and diffraction.  (greased lightning)
!
subroutine kirchfast( adj, add, vrms,     t0,dt,dx, modl,nt,nx, data)
integer ix,iz,it,ib,  adj, add,                          nt,nx
real    amp,t,z,b,              vrms(nt), t0,dt,dx, modl(nt,nx),data(nt&
  &,nx)
call adjnull(         adj, add,                     modl,nt*nx, data,nt&
  &*nx)
do ib= -nx, nx  
  b = dx * ib                     ! b = offset
  do iz= 2, nt  
    z = t0 + dt * (iz-1)            ! z = travel-time depth
    t = sqrt( z**2  +  (b*2/vrms(iz))**2 )
    it = 1.5 + (t - t0) / dt
    if ( it > nt ) then
      exit
    end if
    amp = (z / t)  *  sqrt( nt*dt / t )
    do ix= max0(1, 1-ib),  min0(nx, nx-ib)
      if ( adj .eq. 0 ) then
        data(it,ix+ib)=data(it,ix+ib)+modl(iz,ix   )*amp
      else
        modl(iz,ix   )=modl(iz,ix   )+data(it,ix+ib)*amp
      end if
    end do
  end do
end do 
return
end  
