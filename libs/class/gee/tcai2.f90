module tcai2  
  use classutil
  use tcai1
  implicit none
  integer, private :: nx 
  contains
  subroutine tcai2_init ( aa,nx_in )
    integer    :: nx_in 
    real, dimension (:), pointer :: aa
    nx = nx_in 
    call tcai1_init (aa)
  end subroutine
  function tcai2_lop ( adj, add, x, r) result(stat)
    integer            :: stat 
    logical,intent(in) :: adj,add 
    real,dimension(:)  :: x,r 
    call adjnull (adj,add,x,r )
    call tcai2_lop2(adj,add,x,r )
    stat=0
  end function 
  subroutine tcai2_lop2(adj,add,x,r)
    logical,intent(in) :: adj,add 
    real, dimension (:)  :: x 
    real, dimension (:)  :: r 
    integer stat1
    stat1 = tcai1_lop (adj, .true., x(:nx),   r)
  end subroutine 
  subroutine tcai2_close()
  end subroutine 
end module 
