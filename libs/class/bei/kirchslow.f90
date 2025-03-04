! Kirchhoff migration and diffraction.  (tutorial, slow)
!
subroutine kirchslow(   adj, add,  velhalf, t0,dt,dx, modl,nt,nx,  data&
  &)
integer ix,iy,it,iz,nz, adj, add,                          nt,nx
real x0,y0,dy,z0,dz,t,x,y,z,hs,    velhalf, t0,dt,dx, modl(nt,nx), data&
  &(nt,nx)
call adjnull(           adj, add,                     modl,nt*nx,  data&
  &,nt*nx)
x0=0.
y0=0
dy=dx
z0=t0
dz=dt
nz=nt
do ix= 1, nx  
  x = x0 + dx * (ix-1)
  do iy= 1, nx  
    y = y0 + dy * (iy-1)
    do iz= 1, nz  
      z = z0 + dz * (iz-1)            ! z = travel-time depth
      hs=      (x-y) / velhalf
      t = sqrt( z * z  +  hs * hs )
      it = 1.5 + (t-t0) / dt
      if ( it <= nt ) then
        if ( adj .eq. 0 ) then
          data(it,iy) = data(it,iy) + modl(iz,ix)
        else
          modl(iz,ix) = modl(iz,ix) + data(it,iy)
        end if
      end if
    end do
  end do
end do 
return
end  
