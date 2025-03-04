
! Nearest neighbor interpolation, essentially:   val = vec( 1.5 + (t-t0)/dt)
!
subroutine spot0( adj, add, nt,t0,dt, t, val,    vec    )
integer it,       adj, add, nt
real                           t0,dt, t, val,    vec( nt)
call adjnull(     adj, add,              val, 1, vec, nt)
it = 1.5 + (t-t0) / dt
if ( 0 < it .and. it <= nt) then
  if ( adj .eq. 0 ) then
! add value onto vector
    vec( it) = vec( it) + val
  else
! take value from vector
    val      = val      + vec( it)
  end if
end if
return
end  
