module gmres_mod		

  use ddot_mod
  use llist_mod
  implicit none

  type(list), private		:: grads
  real, dimension(:), allocatable, private :: s, ss

contains

  subroutine gmres_init ()
    grads = llist_init ()
  end subroutine gmres_init

  subroutine gmres_close ()
    call llist_close (grads)
  end subroutine gmres_close

  function gmres(forget, x, grad, rr, cgrad) result(stat)
    integer                                      :: stat
    real, dimension(:):: x, grad, rr, cgrad
    logical           :: forget	

    real, dimension(:), pointer :: g, gg, gi
    double precision            :: alpha, beta, gn
    double precision, parameter :: eps = 1.d-30
    integer                     :: i, n, nm, nd

    nm = size (x) 
    nd = size (rr)
    
    allocate(gg (nm + nd)) ; g => gg(: nm)
    g  = grad   ; gg(nm + 1:) = cgrad
    
    if (.not. allocated(s)) allocate(s(nm), ss(nd))

    n = llist_depth (grads)
    
    call llist_rewind (grads)
    do i = 1, n
       call llist_down (grads, gi, beta)
       alpha = ddot (grad, gi (:nm)) / beta
       gg = gg - alpha * gi
    end do
    
    gn = ddot (g, g)

    if (n > 0) then
       alpha = gn / beta
    else
       alpha = 0.d0
    end if

    s =  g          + alpha * s
    ss = gg (nm+1 :) + alpha * ss
    
    beta = ddot (ss, ss)
    
    if (beta > eps) then
       alpha = gn / beta
       x =  x + alpha *  s
       rr = rr - alpha * ss
    end if
    
    if (gn > eps) then
       call llist_add (grads, gg, gn)
       if (forget) call llist_chop (grads)
    end if
    
    stat = 0
  end function gmres
end module gmres_mod








