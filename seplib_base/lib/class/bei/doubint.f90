! Double integration, first causal, then anticausal.
!
subroutine doubint( adj, add, n,             pp   , qq  )
integer             adj, add, n
real  pp(n), qq(n)
real tt(n)
call adjnull(       adj, add,                pp,n,  qq,n)
if ( adj .eq. 0 ) then
  call causint( 0,   0, n,pp,  tt  )
  call causint( 1, add, n,qq,  tt  )
else
  call causint( 1,   0, n,tt,  qq  )
  call causint( 0, add, n,tt,  pp  )
end if 
return
end  
