
! fill in missing data on 1-axis by minimizing power out of a given filter.
!
subroutine miss1(     na, a, np, p, copy, niter)
integer iter, ip, nr, na,    np,          niter
real    p(np)           
! in: known data with zeros for missing values.
! out: known plus missing data.
real    copy(np)        
! in: copy(ip) vanishes where p(ip) is a missing value.
real    a(na)           ! in: roughening filter
real  dp(np),sp(np),  r(np+na-1),dr(np+na-1),sr(np+na-1)
nr = np+na-1
call contran( 0, 0, na,a, np, p, r)     ! r = a*p   convolution
call scaleit  (        -1., nr,    r)     ! r = -r
do iter= 0, niter  
! niter= number missing or less
  call contran( 1, 0, na,a, np,dp, r)     ! dp(a,r)   correlation
  do ip= 1, np
    if ( copy(ip) .ne. 0.) then
! missing data where copy(ip)==0
      dp(ip) = 0.             ! can't change known data
    end if
  end do 
  call contran( 0, 0, na,a, np,dp, dr)    ! dr=a*dp   convolution
  call cgstep( iter, np,p,dp,sp, nr,r,dr,sr)      ! p=p+dp; r=r-dr
end do 
return
end  
