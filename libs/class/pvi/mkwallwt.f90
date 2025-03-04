! make wall weights from window weights.
!
subroutine mkwallwt( k1,k2, windwt, w1,w2,  wallwt, n1,n2)
integer i1,i2,       k1,k2,         w1,w2,          n1,n2
real                        windwt( w1,w2), wallwt( n1,n2)
call null(                                  wallwt, n1*n2)
do i1= 1, k1  
  do i2= 1, k2  
    call patch( 1, 1, i1,i2, k1,k2, wallwt, n1,n2, windwt,w1,w2 )
  end do
end do 
do i2= 1, n2  
  do i1= 1, n1  
    if (  wallwt(i1,i2) .ne. 0.) then
      wallwt(i1,i2)  = 1. / wallwt(i1,i2)
    end if
  end do
end do 
return
end  
