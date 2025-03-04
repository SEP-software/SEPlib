
! slide a window around on a wall of data.  Count times each data point used.
!
subroutine nonstat( n1,n2, w1,w2, j1,j2, count)
integer n1,n2           ! size of data wall
integer w1,w2           ! size of window
integer j1,j2           ! increments for jumping along the wall
integer s1,s2, e1,e2    
! starting and ending points of window on wall
integer k1,k2           ! output math size of array of windows
integer i1,i2
real       count( n1,n2)
call null( count, n1*n2)
k2=0
e2=w2
do while ( e2<=n2)
  k2=k2+1
  s2=e2-w2+1
  k1=0
  e1=w1
  do while ( e1<=n1)
    k1=k1+1
    s1=e1-w1+1
    do i1= s1, e1  
      do i2= s2, e2  
        count(i1,i2) =  count(i1,i2) + 1.
      end do
    end do 
    e1=e1+j1
  end do 
  e2=e2+j2
end do 
return
end  
