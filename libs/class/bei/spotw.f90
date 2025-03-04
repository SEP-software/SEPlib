!  Scaled linear interpolation.
!
subroutine spotw( adj, add, scale, nt,t0,dt, t, val,   vec   )
use sep_func_mod
integer it,itc,   adj, add,        nt
real tc, fraction,          scale,    t0,dt, t, val,   vec(nt)
call adjnull(     adj, add,                     val,1, vec,nt)
tc = .5+ (t-t0) / dt
itc = tc
it = 1 + itc
fraction = tc - itc
if ( 1 <= it  .and.  it < nt) then
  if ( adj .eq. 0) then
    vec(it  ) = vec(it  ) + (1.-fraction) * val * scale
    vec(it+1) = vec(it+1) +   fraction    * val * scale
  else
    val = val + ((1.-fraction) * vec(it)  +fraction    * vec(it+1)  ) &
      &* scale
  end if
else
  call erexit('spotw: at boundary')
end if 
return
end  
