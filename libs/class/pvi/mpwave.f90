subroutine mpwave( n, cx)       ! minimum phase equivalent wavelet
integer i,         n            ! input:  cx = any wavelet
complex cx(n)                   ! output: cx = min phase wavelet
call ftu( 1., n, cx)            !               with same spectrum.
call scaleit( sqrt(1.*n), 2*n, cx)
do i= 1, n
  cx(i) = cx(i) * conjg( cx(i))
end do 
call kolmogoroff( n, cx)
return
end  
