
! Linear interpolation 1-D, uniform model mesh to data coordinates and values.
!
subroutine lint1( adj, add, o1,d1,coordinate,     mm,m1,  dd, nd)
integer i, im,    adj, add,                  id,     m1,      nd
real    f, fx,gx,           o1,d1,coordinate(nd), mm(m1), dd( nd)
call adjnull(     adj, add,                       mm,m1,  dd, nd)
do id= 1, nd  
  f = (coordinate(id)-o1)/d1
  i=f
  im= 1+i
  if ( 1<=im .and. im<m1) then
    fx=f-i
    gx= 1.-fx
    if ( adj .eq. 0) then
      dd(id) = dd(id) + gx * mm(im) + fx * mm(im+1)
    else
      mm(im  ) = mm(im  ) + gx * dd(id)
      mm(im+1) = mm(im+1) + fx * dd(id)
    end if
  end if
end do 
return
end  
