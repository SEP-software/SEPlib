subroutine cadd( n, xx, yy)
integer i, n
real xx(n), yy(n)
do i= 1, n
  yy(i) = yy(i) + xx(i)
end do 
return
end  
