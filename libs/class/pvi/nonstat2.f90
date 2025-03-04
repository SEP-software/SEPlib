! slide a window around on a wall of data.  Triangle weighting.
!
subroutine nonstat2( n1,n2, w1,w2, j1,j2, data, output, weight)
integer              n1,n2, w1,w2, j1,j2,          s1,s2, e1,e2, k1,k2&
  &, i1,i2
real    data(n1,n2), output(n1,n2), weight(n1,n2),  triangle1, triangle2&
  &, shape
real window(w1,w2), winout(w1,w2)
call null( weight, n1*n2)
call null( output, n1*n2)
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
    do i1= 1, w1  
      do i2= 1, w2  
        window(i1,i2) = data(s1+i1-1,s2+i2-1)
      end do
    end do 
    do i1= 1, w1  
! Trivial data processing
      do i2= 1, w2  
        winout(i1,i2) = window(i1,i2)
      end do
    end do 
    do i1= s1, e1  
      triangle1= amax1(0., 1. - abs(i1-.5*(e1+s1)) / (.5*w1))
      do i2= s2, e2  
        triangle2= amax1(0., 1. - abs(i2-.5*(e2+s2)) / (.5*w2))
        shape = triangle1 * triangle2
        output(i1,i2) = output(i1,i2) + shape * winout(i1-s1+1,i2-s2+1&
          &)
        weight(i1,i2) = weight(i1,i2) + shape
      end do
    end do 
    e1=e1+j1
  end do 
  e2=e2+j2
end do 
do i1= 1, n1  
  do i2= 1, n2  
    if ( weight(i1,i2) > 0. ) then
      output(i1,i2) = output(i1,i2) / weight(i1,i2)
    end if
  end do
end do 
return
end  
