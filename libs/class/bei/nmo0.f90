subroutine nmo0( adj, add, slow,    x, t0, dt, n,zz,  tt )
integer  it, iz, adj, add,                        n
real  xs, t , z,           slow(n), x, t0, dt, zz(n), tt(n)
call adjnull(    adj, add,                     zz,n,  tt,n)
do iz= 1, n  
  z = t0 + dt*(iz-1)              ! Travel-time depth
  xs= x * slow(iz)
  t = sqrt ( z * z + xs * xs)
  it= 1 + .5 + (t - t0) / dt      ! Round to nearest neighbor.
  if ( it <= n ) then
    if ( adj .eq. 0 ) then
      tt(it) = tt(it) + zz(iz)
    else
      zz(iz) = zz(iz) + tt(it)
    end if
  end if
end do 
return
end  
