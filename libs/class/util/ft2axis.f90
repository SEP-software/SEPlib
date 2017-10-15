! 1D Fourier transform on a 2D data set along the 2-axis
!
subroutine  ft2axis( adj, sign2, n1,n2, cx)
integer i1,          adj,        n1,n2
complex cx(n1,n2)
real    sign2
do i1= 1, n1
  call fth( adj, sign2, n1,n2, cx(i1,1))
end do 
return
end  
