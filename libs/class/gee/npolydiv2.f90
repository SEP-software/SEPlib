module npolydiv2  
  use classutil
  use npolydiv
  implicit none
  real ,private,  dimension (:), allocatable  :: tt 
  contains
  subroutine npolydiv2_init ( nd,aa )
    integer,        intent (in) :: nd
    type( nfilter), intent (in) :: aa
    if (.not. allocated(tt)) then
      allocate(tt ( nd)) 
    end if
    call npolydiv_init (nd, aa)
  end subroutine
  function npolydiv2_lop ( adj, add, xx, yy) result(stat)
    integer            :: stat 
    logical,intent(in) :: adj,add 
    real,dimension(:)  :: xx,yy 
    call adjnull (adj,add,xx,yy )
    call npolydiv2_lop2(adj,add,xx,yy )
    stat=0
  end function 
  subroutine npolydiv2_lop2(adj,add,xx,yy)
    logical,intent(in) :: adj,add 
    real, dimension (:)  :: xx 
    real, dimension (:)  :: yy 
    integer :: stat1, stat2
    if (adj) then
      stat1 = npolydiv_lop (.false.,.false.,yy,tt)
      stat2 = npolydiv_lop (.true.,.true.,xx,tt)
    else
      stat1 = npolydiv_lop (.false.,.false.,xx,tt)
      stat2 = npolydiv_lop (.true.,.true.,yy,tt)
    end if
  end subroutine
  subroutine  npolydiv2_close()
    deallocate( tt )
    call npolydiv_close ()
  end subroutine 
end module 
