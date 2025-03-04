!!$=head1 NAME
!!$
!!$broyden_mod  - on step of broyden_method
!!$
!!$=head1 SYNOPSIS
!!$
!!$INIT:  C<call broyden_init()>
!!$ 
!!$OPERATOR:C<ierr= brodyen(forget,x,g)>
!!$ 
!!$=head1 PARAMETERS
!!$   
!!$=over 4
!!$ 
!!$=item forget - logical
!!$
!!$      Wheter or not to forget previous step
!!$ 
!!$=item x      - C<real(:)>
!!$ 
!!$      Model
!!$ 
!!$=item g      - C<real(:)>
!!$
!!$      Gradient
!!$
!!$back
!!$
!!$=head1 DESCRIPTION
!!$
!!$One step of brodyen method
!!$
!!$=head1 head1 SEE ALSO
!!$
!!$L<nonlin_solver>, L<cgstep>
!!$
!!=head1 $head1 LIBRARY
!!$
!!$B<geef90>
!!$=cut

module broyden_mod 

  use ddot_mod
  use llist_mod

  implicit none

  type(list), private :: steps
  integer,     private :: nmem

contains

  subroutine broyden_init (n)
    integer :: n
    steps  = llist_init ()
    nmem = n
  end subroutine broyden_init

  subroutine broyden_close ()
    call llist_close (steps)
  end subroutine broyden_close

  function broyden (forget, x, grad) result (stat)
    integer                      :: stat
    real, dimension (:)          :: x, grad
    logical                      :: forget 

    double precision             :: alpha, beta
    double precision, parameter  :: eps = 1.d-20
    real, dimension (:), pointer :: g, gi
    integer    :: i, n

    allocate (g (size (x))) ; g = grad

    alpha = 0.d0 ; n = llist_depth (steps)
    call llist_rewind (steps )
    do i = 1, n
       call llist_down (steps , gi , beta )
       g  =  g + alpha * gi
       alpha = ddot (g, gi) / beta
    end do
    g  =  g / (1. - alpha)

    alpha = ddot (g, g)
    if (alpha > eps) then
       x = x + g
       if (forget ) then
          call llist_close (steps)
          steps = llist_init ()
          forget = .false.
          deallocate (g)
       else
          call llist_add (steps, g, alpha)
       end if
    else
       deallocate (g)
    end if

    if ((n > 2 .and. alpha > 100. * beta) .or. n > nmem) then
       call llist_close (steps)
       steps = llist_init ()
       forget = .true.
    end if

    stat = 0
  end function broyden

end module broyden_mod






