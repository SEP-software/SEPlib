! anti-aliased kirchhoff migration (adj=1) and modeling (adj=0)
!
subroutine aamig( adj,add, slow,antialias,t0,dt, dx, nt,nx, image, data&
  &  )
integer adj, add, ix, nx, nt, iy
real    h,            slow(nt),antialias,t0,dt, dx, image(nt,nx), data&
  &(nt,nx)
call adjnull(    adj, add,                          image,nt*nx,  data&
  &,nt*nx)
do ix= 1, nx  
  do iy= 1, nx  
    h  = dx * (iy - ix)
    call trimo( adj, 1, t0,dt,dx, h, nt,slow, 0., 1., antialias,      &
      &                                                   image(1,iy&
      &), data(1,ix))
  end do
end do 
return
end  
