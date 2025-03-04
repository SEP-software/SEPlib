subroutine phasemig( up, nt, nx, dt, dx, image, ntau, dtau, vel)
integer                  nt, nx,                ntau,         iw,nw,ikx&
  &,itau
real    dt,dx, w,w0,dw, kx,kx0,dkx,dtau, vel, sig1,sig2,pi, w2, vkx2
complex up(nt,nx), image(ntau,nx), cc
pi = 3.14159265
sig1 = +1.
sig2 = -1.
call ft1axis( 0, sig1, nt, nx, up)   
call ft2axis( 0, sig2, nt, nx, up)
nw = nt
w0  = -pi/dt
dw = 2.*pi/(nt*dt)
kx0 = -pi/dx
dkx= 2.*pi/(nx*dx)
call null( image, ntau*nx*2)
do iw   = 2, nw   
  w  = w0  + (iw -1) * dw
  do ikx  = 2, nx   
    kx = kx0 + (ikx-1) * dkx
    w2   = w * w
    vkx2 = vel*vel * kx*kx / 4.
    if ( w2 > vkx2 ) then
      cc = cexp( cmplx( 0., - w * dtau * sqrt( 1. - vkx2/w2 ) ) )
      do itau = 1, ntau  
        up(iw,ikx) = up(iw,ikx) * cc
        image(itau,ikx) = image(itau,ikx) + up(iw,ikx)
      end do
    end if
  end do
end do 
call ft2axis( 1, sig2, ntau, nx, image)
return
end  
