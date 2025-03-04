
! Phase shift modeling and migration.   (Warning: destroys its input!)
!
subroutine gazadj( adj, dt,dx, v,nt,nx, modl,         data )
integer            adj,          nt,nx,                  iw, ikx, iz&
  &,nz
complex eiktau, cup,                    modl(nt,nx),  data(nt,nx)
real                      dt,dx, v(nt),              pi, w,w0,dw, kx,kx0&
  &,dkx,qi
call adjnull(     adj,  0,              modl,nt*nx*2, data,nt*nx*2 )
pi = 4.*atan(1.)
w0  = -pi/dt
dw = 2.*pi/(nt*dt)
qi=.5/(nt*dt)
nz = nt
kx0 = -pi/dx
dkx= 2.*pi/(nx*dx)
if ( adj .eq. 0) then
  call ft2axis( 0, -1., nz, nx, modl)
else
  call ft2axis( 0, -1., nt, nx, data)
  call ft1axis( 0,  1., nt, nx, data)
end if 
do ikx  = 2, nx      
  kx = kx0 + (ikx-1) * dkx
  do iw   = 2, 1+nt/2  
    w  = w0  + (iw -1) * dw
    if ( adj.eq. 0) then
      data(iw,ikx) = modl(nz,ikx)
      do iz = nz-1, 1, -1
        data(iw,ikx) = data(iw,ikx) * eiktau(dt,w,v(iz)*kx,qi) +modl(iz&
          &,ikx)
      end do
    else
      cup          = data(iw,ikx)
      do iz = 1, nz  
        modl(iz,ikx) = modl(iz,ikx)  +  cup
        cup          = cup *  conjg(  eiktau(dt,w,v(iz)*kx,qi))
      end do
    end if
  end do
end do 
if ( adj .eq. 0) then
  call ft1axis( 1,  1., nt, nx, data)
  call ft2axis( 1, -1., nt, nx, data)
else
  call ft2axis( 1, -1., nz, nx, modl)
end if 
return
end  
