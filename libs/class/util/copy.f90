subroutine copy( n, xx, yy)
integer i, n
real xx(n), yy(n)
do i= 1, n
  yy(i) = xx(i)
end do 
return
end  
