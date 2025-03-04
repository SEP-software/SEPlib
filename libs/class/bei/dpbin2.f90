! Data-push binning in 2-D.
!
subroutine dpbin2 ( adj, add, o1,d1,o2,d2, xy,       mm,m1,m2,  dd, nd&
  &)
integer      i1,i2, adj, add,                   id,     m1,m2,      nd
real                          o1,d1,o2,d2, xy(2,nd), mm(m1,m2), dd( nd&
  &)
call adjnull(       adj, add,                        mm,m1*m2,  dd, nd&
  &)
do id=1,nd  
  i1 = 1.5 + (xy(1,id)-o1)/d1
  i2 = 1.5 + (xy(2,id)-o2)/d2
  if ( 1<=i1 .and. i1<=m1 .and.  1<=i2 .and. i2<=m2   ) then
    if ( adj .eq. 0) then
      dd( id)   = dd( id)   +  mm(i1,i2)
    else
      mm(i1,i2) = mm(i1,i2) +  dd( id)
    end if
  end if
end do 
return
end  
