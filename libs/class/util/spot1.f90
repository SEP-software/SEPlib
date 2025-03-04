
! Nearest neighbor interpolation would do this:    val = vec( 1.5 + (t-t0)/dt)
! This is the same but with _linear_ interpolation.
!
subroutine spot1( adj, add, nt,t0,dt, t, val,    vec    )
integer it, itc,  adj, add, nt
real tc, fraction,             t0,dt, t, val,    vec(nt)
call adjnull(    adj, add,               val, 1, vec,nt)
tc      = (t-t0) / dt
itc     =  tc
it      = 1 + itc
fraction = tc - itc
if ( 1 <= it  .and.  it < nt) then
  if ( adj .eq. 0) then
! add value onto vector
    vec(it  ) = vec(it  ) + (1.-fraction) * val
    vec(it+1) = vec(it+1) +   fraction    * val
  else
! take value from vector
    val = val + (1.-fraction) * vec(it)  +  fraction * vec(it+1)
  end if
end if
return
end  
