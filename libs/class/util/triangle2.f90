! smooth by convolving with triangle in two dimensions.
!
subroutine triangle2( rect1, rect2, n1, n2, uu, vv)
integer i1,i2,        rect1, rect2, n1, n2
real uu(n1,n2), vv(n1,n2)
real ss(n1,n2)
do i1= 1, n1
  call triangle( rect2, n1, n2, uu(i1,1), ss(i1,1))
end do 
do i2= 1, n2
  call triangle( rect1,  1, n1, ss(1,i2), vv(1,i2))
end do 
return
end  
