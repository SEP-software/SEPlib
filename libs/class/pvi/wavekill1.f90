!   vv = (aa Dx + pp Dt) uu
!
subroutine wavekill1( aa, pp,    n1,n2,uu,  vv )
integer i1,i2,                      n1,n2
real aa, pp, s11, s12, s21, s22, uu(n1,n2), vv( n1-1,  n2-1)
s11 = -aa-pp
s12 = aa-pp
s21 = -aa+pp
s22 = aa+pp
call null(                                  vv,(n1-1)*(n2-1))
do i1= 1, n1-1  
! vv is one point shorter than uu on both axes.
  do i2= 1, n2-1  
    vv(i1,i2) = vv(i1,i2) +uu(i1  ,i2) * s11 + uu(i1  ,i2+1) * s12 +uu&
      &(i1+1,i2) * s21 + uu(i1+1,i2+1) * s22
  end do
end do 
return
end  
