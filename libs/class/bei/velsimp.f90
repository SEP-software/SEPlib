! velsimp --- simple velocity transform
!
subroutine velsimp( adj,add, t0,dt,x0,dx,s0,ds, nt,nx,ns, modl, data)
integer it,ix,is,   adj,add,                    nt,nx,ns,             &
  & iz,nz
real x,s,sx, t,z, z0,dz,wt,   t0,dt,x0,dx,s0,ds, modl(nt,ns),data(nt,nx&
  &)
call adjnull(       adj,add,                     modl,nt*ns, data,nt*nx&
  &)
nz= nt
z0=t0
dz= dt
! z is travel time depth
do is= 1, ns  
  s = s0 + (is-1) * ds
  do ix= 1, nx  
    x = x0 + (ix-1) * dx
    do iz= 2, nz  
      z = z0 + (iz-1) * dz
      sx =  abs( s * x)  
      t  = sqrt( z * z + sx * sx)
      it = 1.5 + (t - t0) / dt
      if ( it <= nt) then
        wt= (z/t) / sqrt( t)*sqrt(x/v)
        if ( adj .eq. 0 ) then
          data(it,ix) = data(it,ix) + modl(iz,is) * sqrt(sx) * wt
        else
          modl(iz,is) = modl(iz,is) + data(it,ix) * sqrt(sx) * wt
        end if
      end if
    end do
  end do
end do 
return
end  
