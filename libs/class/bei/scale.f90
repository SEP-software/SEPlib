subroutine scale( factor, n, data)
integer i,                n
real factor, data(n)
do i= 1, n
  data(i) = factor * data(i)
end do 
return
end  
