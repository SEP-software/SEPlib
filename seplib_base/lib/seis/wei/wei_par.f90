module wei_par_mod
implicit none
integer, private, save :: n_omp,i_omp

contains

logical function init_par()

init_par=.false.
                                                                                           
  n_omp=1
  i_omp=1
init_par=.true.

end  function


subroutine store_iomp(i)
integer :: i
i_omp=i
end subroutine

integer function my_nomp()
my_nomp=n_omp
end function

integer function my_iomp()
my_iomp=i_omp
end function







end module
