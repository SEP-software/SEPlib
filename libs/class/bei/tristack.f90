! Modeling and stacking using triangle weighted moveout.
!
subroutine tristack( adj,add, slow,anti,t0,dt,x0,dx, nt,nx, stack, gather&
  &   )
integer ix,          adj,add,                        nt,nx
real x,                    slow(nt),anti,t0,dt,x0,dx, stack(nt), gather&
  &(nt,nx)
call adjnull(        adj, add,                        stack,nt,  gather&
  &,nt*nx)
do ix= 1, nx  
  x =  x0 + dx * (ix-1)
  call trimo( adj,1,t0,dt,dx, x, nt,slow,0.,1.,anti,stack, gather(1,ix&
    &))
end do 
return
end  
