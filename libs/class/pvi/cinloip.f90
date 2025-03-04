
! cinloip --- apply time and space variable 2-D filter, adjoint to input.
!
subroutine cinloip( adj,add, w1,w2,lag1,lag2, aa,a1,a2,k1,k2, data,n1&
  &,n2, fout)
use classutil
integer i1,i2,      adj,add, w1,w2,lag1,lag2,    a1,a2,k1,k2,      n1&
  &,n2
real                                 aa( a1,a2, k1,k2), data(n1,n2),&
  & fout(n1,n2)
real pdat(w1,w2),   copie(n1,n2)
real pfou(w1,w2), wallwt(n1,n2), windwt(w1,w2)
call adjnull(       adj,add,                            data,n1*n2, &
  & fout,n1*n2)
call cinloiwt( a1,a2, lag1,lag2,             windwt,w1,w2)
call mkwallwt( k1,k2, windwt, w1,w2, wallwt,n1,n2)
if ( adj .eq. 0 ) then
  do i1= 1, k1  
    do i2= 1, k2  
      call patch(  0, 0, i1,i2, k1,k2, data,n1,n2, pdat,w1,w2 )
      call cinloi( 0, 0, lag1,lag2, a1,a2, aa(1,1,i1,i2),             &
        &                              w1,w2, pdat,       pfou       )
      call diag(   0, 0,windwt, w1*w2, pfou,       pfou       )
      call patch(  1, 1, i1,i2, k1,k2, copie,n1,n2, pfou,w1,w2 )
    end do
  end do 
  call diag(           0, 1,wallwt, n1*n2, copie,       fout       )
else
  call diag(           1, 0,wallwt, n1*n2, copie,       fout       )
  do i1= 1, k1  
    do i2= 1, k2  
      call patch(  0, 0, i1,i2, k1,k2, copie,n1,n2, pfou,w1,w2 )
      call diag(   1, 0,windwt, w1*w2, pfou,       pfou       )
      call cinloi( 1, 0, lag1,lag2, a1,a2, aa(1,1,i1,i2),             &
        &                              w1,w2, pdat,       pfou       )
      call patch(  1, 1, i1,i2, k1,k2, data,n1,n2, pdat,w1,w2 )
    end do
  end do
end if 
return
end  
