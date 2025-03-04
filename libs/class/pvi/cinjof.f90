
! CINJOF --- Convolution INternal with Jumps. Output and FILTER are adjoint.
!
subroutine cinjof( adj, add, jump,   n1,n2,xx, nb1,nb2,bb, yy)
use sep_func_mod
use classutil
integer            adj, add, jump,   n1,n2,    nb1,nb2    
! jump subsamples data
real                                  xx( n1,n2),  bb( nb1,nb2),  yy(&
  & n1,n2)
integer y1,y2, x1,x2, b1, b2, ny1, ny2
call adjnull( adj, add,                            bb, nb1*nb2,   yy,&
  & n1*n2)
ny1 = n1 - (nb1-1) * jump
if ( ny1<1 ) then
  call erexit('cinjof: ny1<1')
end if
ny2 = n2 - (nb2-1)
if ( ny2<1 ) then
  call erexit('cinjof: ny2<1')
end if
if ( adj .eq. 0 ) then
  do b2=1,nb2  
    do y2=1,ny2  
      x2 =  y2 - (b2-nb2)      
      do b1=1,nb1  
        do y1=1,ny1  
          x1 =  y1 - (b1-nb1) * jump
          yy(y1,y2) = yy(y1,y2) + bb(b1,b2) * xx(x1,x2)
        end do
      end do
    end do
  end do
else
  do b2=1,nb2  
    do y2=1,ny2  
      x2 =  y2 - (b2-nb2)      
      do b1=1,nb1  
        do y1=1,ny1  
          x1 =  y1 - (b1-nb1) * jump
          bb(b1,b2) = bb(b1,b2) + yy(y1,y2) * xx(x1,x2)
        end do
      end do
    end do
  end do
end if 
return
end  
