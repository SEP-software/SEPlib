module sep_par_mod
use, intrinsic :: iso_c_binding






interface 
  integer function npfao(a,b) bind(c,name="npfao")
    import
    integer(C_INT),value :: a,b
  end function

    subroutine pfacr( a,b,ar1,ar2) bind(c,name="pfacr")
    import
    integer(C_INT),value :: a,b
    real(C_FLOAT), dimension(*) :: ar2
    complex(C_FLOAT), dimension(*) :: ar1
  end subroutine
  

end interface


end module

