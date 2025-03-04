
! Nearest neighbor interpolation would do this:    cbx = cb( 1.5 + (x-x0)/dx)
! Linear interpolation with the same definitions of variables is:
!
subroutine cinterp1( x, nx,x0,dx, cb, cbx)
integer ix,ixc,         nx
real    x, xc, x0, dx, fraction
complex cb(nx), cbx
xc      = (x-x0) / dx
ixc     =  xc
fraction = xc - ixc
ix      = 1 + ixc
if ( ix < 1 ) then
  cbx = cb( 1)
else if ( ix+1 > nx) then
  cbx = cb( nx)
else
  cbx = (1.-fraction) * cb(ix)  +  fraction * cb(ix+1)
end if 
return
end  
