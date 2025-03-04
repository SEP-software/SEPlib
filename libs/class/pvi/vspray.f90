subroutine vspray( adj,  nt,dt,t0,  nx,dx,x0, tx,  ns,ds,s0, zs)
use classutil
integer adj, it, nt, iz, nz, ix, nx, is, ns, isp, ism
real    tx(nt,nx), zs(nt,ns), scale
real    z,dz,z0, t,dt,t0, x,dx,x0, s,ds,s0, sm,sp, xm,xp, tm,tp
nz=nt
dz=dt
z0=t0
call adjnull( adj, 0,              tx, nt*nx,     zs, nz*ns)
if ( adj .eq. 0) then
  do ix=1,nx
    call halfdif ( 1, nt, tx(1,ix), tx(1,ix) )
  end do
end if
do iz=  1, nz  
  z = z0 + dz*(iz-1)
  do ix=  1, nx  
    x = x0 + dx*(ix-1)
    do it= iz, nt  
      t = t0 + dt*(it-1)
      tm = t-dt/2
      xm = x
      tp = t+dt/2
      xp = x
      sm = (tm**2 -z**2)/xp**2
      ism = 1.5+(sm-s0)/ds
      sp = (tp**2 -z**2)/xm**2
      isp = 1.5+(sp-s0)/ds
      if ( ism<2 ) then
        cycle
      end if
      if ( isp>ns) then
        cycle
      end if
      scale = sqrt( t / (1.+isp-ism) ) / ( abs(x) + abs(dx)/2.)
      do is= ism, isp  
        if ( adj .eq. 0) then
          zs(iz ,is) = zs(iz ,is) + tx(it ,ix) * scale
        else
          tx(it ,ix) = tx(it ,ix) + zs(iz ,is) * scale
        end if
      end do
    end do
  end do
end do 
if ( adj .ne. 0) then
  do ix=1,nx
    call halfdif ( 0, nt, tx(1,ix), tx(1,ix) )
  end do
end if
return
end  
