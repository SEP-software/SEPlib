! Convolve with triangle
!
subroutine triangle( nr, m1, n12, uu, vv)
! input:        nr      rectangle width (points) (Triangle base twice as wide.)
! input:        uu(m1,i2),i2=1,n12      is a vector of data.
! output:       vv(m1,i2),i2=1,n12      may be on top of uu
integer nr,m1,n12, i,np,nq
real uu( m1, n12),  vv( m1, n12)        
real pp(n12+nr-1), qq(n12+nr+nr-2), tt(n12)
do i=1,n12  
  qq(i) = uu(1,i)
end do 
if ( n12 .eq. 1 ) then
  do i= 1, n12
    tt(i) = qq(i)
  end do
else
  call boxconv( nr, n12, qq, pp)
  np = nr+n12-1
  call boxconv( nr, np , pp, qq)
  nq = nr+np-1
  do i= 1, n12
    tt(i) = qq(i+nr-1)
  end do 
  do i= 1, nr-1                                   
  ! fold back near end
    tt(i) = tt(i) + qq(nr-i)
  end do 
  do i= 1, nr-1                                   ! fold back far end
    tt(n12-i+1) = tt(n12-i+1) + qq(n12+(nr-1)+i)
  end do
end if 
do i=1,n12  
  vv(1,i) = tt(i)
end do 
return
end  
