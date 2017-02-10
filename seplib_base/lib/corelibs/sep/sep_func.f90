module sep_func_mod
use, intrinsic :: iso_c_binding
implicit none



 
interface 

  subroutine erexit(string) bind(c,name="seperr")
    import
    character(C_CHAR), dimension(*) :: string
  end subroutine
    subroutine seperr(string) bind(c,name="seperr")
    import
    character(C_CHAR), dimension(*),intent(in) :: string
  end subroutine

  subroutine sep_add_doc_line(string) bind(c,name="sep_add_doc_line")
    import
    character(C_CHAR), dimension(*) :: string
  end subroutine
  subroutine sep_prog(string) bind(c,name="sep_prog")
    import
    character(C_CHAR), dimension(*) :: string
  end subroutine
  subroutine sep_begin_prog() bind(c,name="sep_begin_prog")
    import
 end subroutine
   subroutine sep_end_prog() bind(c,name="sep_end_prog")
    import
end subroutine
integer function strlen(strin) bind(c,name="strlen")
  import
  character(C_CHAR),dimension(*) :: strin
end function
end interface

contains

subroutine c2forstr(str)
 character(len=*) :: str
 integer ::n,i
 
 n=strlen(str)
   do i=n+1,len(str)
     str(i:i)=" "
   end do
end subroutine




end module
