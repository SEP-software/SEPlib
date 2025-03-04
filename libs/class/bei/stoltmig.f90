subroutine stoltmig( nt,nz,nx, dt,dz,dx, vel, cftdata, cftimage)
integer it,iz,ix,    nt,nz,nx,  iw,ikz,ikx, nw,nkz,nkx
real    dt,dz,dx, w0,kz0,kx0, dw,dkz,dkx, pi, vel,w,kz,kx, signum
complex ckzkx, cftdata(nt,nx), cftimage(nz,nx)
pi = 3.1415926
nw  = nt
w0  = -pi/dt
dw  = 2.*pi/(nt*dt)
nkz = nz
kz0 = -pi/dz
dkz = 2.*pi/(nz*dz)
nkx = nx
kx0 = -pi/dx
dkx = 2.*pi/(nx*dx)
do ikz= 1, nkz  
  cftimage( ikz,   1) = 0.
end do 
! zero the Nyquist.
do ikx= 1, nkx  
  cftimage(   1, ikx) = 0.
end do 
! zero the Nyquist.
do ikx = 2, nkx  
  kx = kx0 + dkx * (ikx-1)
  do ikz = 2, nkz  
    kz = kz0 + dkz * (ikz-1)
    w = - signum( kz) * sqrt( kx*kx + kz*kz) * vel / 2.
    call cinterp1( w, nw,w0,dw, cftdata(1,ikx), cftimage(ikz,ikx) )
  end do
end do 
return
end  
