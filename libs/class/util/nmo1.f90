subroutine nmo1( adj, add, slow,    x, t0, dt, n,zz,  tt )
integer  it, iz, adj, add,                        n
real  xs, t , z,           slow(n), x, t0, dt, zz(n), tt(n), wt
call adjnull(    adj, add,                     zz,n,  tt,n)
do iz= 1, n  
  z = t0 + dt*(iz-1)
  xs = x * slow(iz)
  t = sqrt ( z * z + xs * xs) + 1.e-20
  wt = z/t * (1./sqrt(t))                 !  weighting function
  it = 1 + .5 + (t - t0) / dt
  if ( it <= n ) then
    if ( adj .eq. 0 ) then
      tt(it) = tt(it) + zz(iz) * wt
    else
      zz(iz) = zz(iz) + tt(it) * wt
    end if
  end if
end do 
return
end  
