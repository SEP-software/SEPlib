! Kirchhoff dip-moveout and modelling.  (tutorial, slow)
!
subroutine  kdmoslow(   adj, add, v,     h, t0,dt,dx, nt,nx,   p0,   &
  & pn)
integer ix,iy,it,iz,nz, adj, add,                     nt,nx
real x0,y0,dy,z0,dz,tn,x,y,z,hs,   v,     h, t0,dt,dx,   p0(nt,nx),  &
  & pn(nt,nx)
real r,tnmx,wgt,tmax
call adjnull(           adj, add,                        p0,nt*nx,   &
  & pn,nt*nx)
x0=0.
y0=0
dy=dx
z0=t0
dz=dt
nz=nt
tmax=t0+(nt-1)*dt
wgt = 1.
if ( h .ne. 0. ) then
  wgt = dx / h
end if
do ix= 1, nx  
  x = x0 + dx * (ix-1)
  do iy= 1, nx  
    y = y0 + dy * (iy-1)
    hs = abs((x-y) / h)
    if ( hs > 0.999) then
      cycle            ! x-y is bigger than DMO aperture
    end if
    r = sqrt( 1. - hs * hs)
    if ( hs .ne. 0. ) then
      tnmx = 2 * h / v * r / hs    ! cutoff at 90-degrees dip
    else
      tnmx = tmax
    end if 
    tnmx = min(tnmx,tmax)           
    do it= 1, nt  
      tn= t0 + dt * (it-1)    ! tn = finite-offset time after NMO
      if ( tn > tnmx ) then
        exit
      end if
      z = tn * r                      !  z = zero-offset time
      iz = 1.5 + (z-z0) / dz
      if ( adj .eq. 0 ) then
        pn(it,iy) =   pn(it,iy) +   p0(iz,ix) * wgt
      else
        p0(iz,ix) =   p0(iz,ix) +   pn(it,iy) * wgt
      end if
    end do
  end do
end do 
return
end  
