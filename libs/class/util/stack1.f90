subroutine stack1( adj, add, slow,     t0,dt, x0,dx, nt,nx, stack, gather&
  &)
integer ix,        adj, add,                         nt,nx
real     x,                  slow(nt), t0,dt, x0,dx,   stack(nt), gather&
  &(nt,nx)
call adjnull(      adj, add,                           stack,nt,  gather&
  &,nt*nx)
do ix= 1, nx  
  x = x0 + dx * (ix-1)
  call nmo1( adj, 1, slow, x, t0,dt, nt, stack, gather(1,ix))
end do 
return
end  
