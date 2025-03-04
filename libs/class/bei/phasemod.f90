subroutine phasemod( image, nz, nx, dz, dx, up, nt, dt, vel)
integer                     nz, nx,            nt,       iw,nw,ikx,iz
real    dt,dx,dz, w,w0,dw, kx,kx0,dkx, vel, sig1,sig2,pi, w2, vkx2
complex up(nt,nx), image(nz,nx), cc
pi = 3.14159265
sig1 = +1.
sig2 = -1.
call ft2axis( 0, sig2, nz, nx, image)
nw = nt
w0  = -pi/dt
dw = 2.*pi/(nt*dt)
kx0 = -pi/dx
dkx= 2.*pi/(nx*dx)
call null( up, nw*nx*2)
do iw  = 2, nw   
  w  = w0  + (iw-1)  * dw     
  do ikx = 2, nx   
    kx = kx0 + (ikx-1) * dkx
    w2   = w * w
    vkx2 = vel*vel * kx*kx / 4.
    if ( w2 > vkx2 ) then
      cc = cexp( cmplx( 0., w * dz * sqrt(1. - vkx2/w2) ))
      do iz = nz, 1, -1
        up(iw,ikx) = up(iw,ikx) * cc  + image(iz,ikx)
      end do
    end if
  end do
end do 
call ft1axis( 1, sig1, nt, nx, up)
call ft2axis( 1, sig2, nt, nx, up)
return
end  
