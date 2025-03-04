! Mihai Nov 92
! 1D Fourier transform on a 3D data set along the 1-axis
!
subroutine  ft3D1axis(adj,sign1,n1,n2,n3,cx)
integer  i2,i3,adj,n1,n2,n3
complex cx(n1,n2,n3)
real sign1
do i3=1,n3
  do i2=1,n2
    call fth( adj, sign1, 1,n1, cx(1,i2,i3))
  end do
end do 
return
end
! 1D Fourier transform on a 3D data set along the 2-axis
!
subroutine  ft3D2axis( adj, sign2, n1,n2,n3, cx)
integer i1,i3,adj,n1,n2,n3
complex cx(n1,n2,n3)
real    sign2
do i3=1,n3
  do i1=1,n1
    call fth( adj, sign2, n1,n2, cx(i1,1,i3))
  end do
end do 
return
end
! 1D Fourier transform on a 3D data set along the 3-axis
!
subroutine  ft3D3axis( adj, sign3, n1,n2,n3, cx)
integer i1,i2,adj,n1,n2,n3
complex cx(n1,n2,n3)
real    sign3
do i2=1,n2
  do i1=1,n1
    call fth( adj, sign3, n1*n2,n3, cx(i1,i2,1))
  end do
end do 
return
end  
