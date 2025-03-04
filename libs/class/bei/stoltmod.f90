subroutine stoltmod( nz,nt,nx, dz,dt,dx, vel, cftimage, cftdata)
integer iz,it,ix,    nz,nt,nx,    ikz,iw,ikx, nkz,nw,nkx
real    dz,dt,dx, kz0,w0,kx0, dkz,dw,dkx, pi, vel,vhalf, kz,w,kx,&
  & signum
complex cwkx, cftimage(nz,nx), cftdata(nt,nx)
pi = 3.1415926
nkz = nz
kz0 = -pi/dz
dkz = 2.*pi/(nz*dz)
nw  = nt
w0  = -pi/dt
dw  = 2.*pi/(nt*dt)
nkx = nx
kx0 = -pi/dx
dkx = 2.*pi/(nx*dx)
do iw = 1, nw   
  cftdata(  iw,   1) = (0.,0.)
end do 
! zero the Nyquist.
do ikx= 1, nkx  
  cftdata(   1, ikx) = (0.,0.)
end do 
! zero the Nyquist.
vhalf = 0.5 * vel
do ikx = 2, nkx  
  kx = kx0 + dkx * (ikx-1)
  do iw  = 2, nw   
    w  = w0  + dw  * (iw -1)
    kz = w*w/(vhalf*vhalf)-kx*kx
    if (kz >= 0.) then
      kz = - signum( w)*sqrt( kz)
    else
      kz = 0.
    end if 
    call cinterp1( kz, nkz,kz0,dkz, cftimage(1,ikx), cwkx)
    if ( kz .ne. 0.) then
      cftdata(iw,ikx) = cwkx
    else
      cftdata(iw,ikx) = 0.
    end if
  end do
end do 
return
end  
