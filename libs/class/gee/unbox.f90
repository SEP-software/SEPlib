module unbox  
! helixfilter aa = cube(a1,a2,...)
  use helix
  use cartesian
  implicit none
  contains
  function unboxn( nd, center, na, cube)  result( aa)
    type( filter)                       :: aa
    integer, dimension( :), intent( in) :: nd, center, na      
    ! (ndim)
    real,    dimension( :), intent( in) :: cube                       
    ! cube(a1,a2,...)
    logical, dimension( size( cube))    :: keep                       
    ! keep(a1*a2*...)
    integer, dimension( size( nd))      :: ii                       ! (ndim)
    integer                             :: ic, lag0a, lag0d, i, h
    call cart2line(  na, center, lag0a)
    call cart2line(  nd, center, lag0d)
    keep = ( abs( cube) > epsilon( cube))     
    ! epsilon is a Fortran intrinsic
    keep( lag0a) = .false.                    ! throw away the 1.0.
    call allocatehelix( aa, count( keep))
    h = 0
    do ic = 1, size( cube)
! sweep cube
      if ( keep( ic) ) then
        h = h + 1  ! only the keepers
        call line2cart(  na, ic, ii)          ! ii(ic)= indices on na
        call cart2line(  nd,     ii, i)       ! i     = index   on nd
        aa%lag( h) = i - lag0d                 ! lag = index - center
        aa%flt( h) = cube( ic)                       ! copy coefs.
      end if
    end do
  end function 
end module 
