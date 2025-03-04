! from par:  integer n3:nt=12, n2:nx=48, n1:nz=96,  nw=2, nlam=4
! from par:  real dx=2, dz=1, v=1
!
subroutine wavemovie( nt, nx, nz, nw, nlam, dx,dz,v, p, cd, q)
integer it,nt,ix,nx,iz,nz,iw,nw, nlam
real dx,dz,v, phase,pi2,z0,x0,dt,dw,lambda,w,wov,x, p(nz,nx,nt)
complex aa,a,b,c,cshift, cd(nx),q(nx)
lambda=nz*dz/nlam
pi2=2.*3.141592
dw=v*pi2/lambda
dt=pi2/(nt*dw)
x0 = nx*dx/3
z0 = nz*dz/3
call null( p, nz*nx*nt)
do iw = 1,nw  
! superimpose nw frequencies
  w =  iw*dw
  wov = w/v                 ! frequency / velocity
  do ix = 1,nx  
! initial conditions for a
    x = ix*dx-x0
! collapsing spherical wave
    phase = -wov*sqrt( z0**2+x**2)
    q(ix) = cexp( cmplx( 0.,phase))
  end do 
  aa = (0.,1.)*dz/(4.*dx**2*wov)          
  ! tridiagonal matrix coefficients
  a = -aa
  b = 1.+2.*aa
  c = -aa
  do iz = 1,nz  
! extrapolation in depth
    do ix = 2,nx-1                  ! diffraction term
      cd(ix) = aa*q(ix+1) + (1.-2.*aa)*q(ix) + aa*q(ix-1)
    end do 
    cd(1) = 0.
    cd(nx) = 0.
    call ctris( nx,-a,a,b,c,-c,cd,q)
! Solves complex tridiagonal equations
    cshift = cexp( cmplx( 0.,wov*dz))
    do ix = 1,nx                    ! shifting term
      q(ix) = q(ix) * cshift
    end do 
    do it=1,nt  
! evolution in time
      cshift = cexp( cmplx( 0.,-w*it*dt))
      do ix = 1,nx
        p(iz,ix,it) = p(iz,ix,it) + q(ix)*cshift
      end do
    end do
  end do
end do 
return
end  
