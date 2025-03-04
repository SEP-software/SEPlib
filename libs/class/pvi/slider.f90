
! slide a window around on a wall of data measuring coherency, dip, residual
!
subroutine slider( n1,n2, w1,w2, k1,k2, data, coh, pp, res)
integer i1,i2,     n1,n2, w1,w2, k1,k2,                    s1,s2, e1&
  &,e2
integer p1,p2                           
! number of subwindows is p1*p2
real    data(n1,n2)                     ! input
real    res(n1,n2)                      
! outputs. math size (n1-1,n2-1)
real    pp(n1,n2), coh(n1,n2)           
! outputs defined at pp( 1..p1, 1..p2)
real  count( n1,n2)
real  window(w1,w2), tres(w1-1,w2-1)
call null(      count, n1*n2)
call null(        res, n1*n2)
p2=0
e2=w2
do while ( e2<=n2)
  p2=p2+1
  s2=e2-w2+1
  p1=1
  e1=w1
  do while ( e1<=n1)
    p1=p1+1
    s1=e1-w1+1
    do i1 = 1, w1  
      do i2 = 1, w2  
        window(i1,i2) = data(i1+s1-1,i2+s2-1)
      end do
    end do 
    call null(                                         tres, (w1-1)*(w2&
      &-1))
    call puck ( w1, w2, window, coh(p1,p2), pp(p1,p2), tres)
    do i1= s1, e1-1  
      do i2= s2, e2-1  
        res(  i1,i2) =    res(i1,i2) + tres( i1-s1+1, i2-s2+1)
        count(i1,i2) =  count(i1,i2) + 1.
      end do
    end do 
    e1=e1+k1
  end do 
  e2=e2+k2
end do 
do i2= 1, n2-1  
  do i1= 1, n1-1  
    if ( count(i1,i2) > 0. ) then
      res(i1,i2) = res(i1,i2) / count(i1,i2)
    end if
  end do
end do 
return
end  
