module allpass_3d  
  use classutil
  implicit none
  integer, private :: nx 
  integer, private :: ny 
  integer, private :: nz 
  real ,private,  dimension (:), pointer  :: pp 
  contains
  subroutine allpass_3d_init ( nx_in,ny_in,nz_in,pp_in )
    integer    :: nx_in 
    integer    :: ny_in 
    integer    :: nz_in 
    real ,   dimension (:), pointer :: pp_in 
    nx = nx_in 
    ny = ny_in 
    nz = nz_in 
    pp => pp_in
  end subroutine
  function allpass_3d_lop ( adj, add, xx, yy) result(stat)
    integer            :: stat 
    logical,intent(in) :: adj,add 
    real,dimension(:)  :: xx,yy 
    call adjnull (adj,add,xx,yy )
    call allpass_3d_lop2(adj,add,xx,yy )
    stat=0
  end function 
  subroutine allpass_3d_lop2(adj,add,xx,yy)
    logical,intent(in) :: adj,add 
    real, dimension (nx,ny,nz)  :: xx 
    real, dimension (nx,ny,nz)  :: yy 
    integer :: ix, iy,iz
    real    :: a, ap, am, p
    integer, parameter :: dp = selected_real_kind(10,50)
    real(kind=dp) :: t
    do iz = 1,nz  
      do iy = 2,ny  
        do ix = 2,nx-1  
          p = pp(ix+(iy-2)*nx+(iz-1)*nx*ny)            
          ap = (1.+p)*(2.+p)
          am = (1.-p)*(2.-p)
          a = 12. - ap - am        
          a=a/12.
          am=am/12.
          ap=ap/12.
          if ( adj) then
            xx(ix,  iy,iz)   =                xx(ix,  iy,iz)   + yy(ix&
              &,iy,iz) * a
            xx(ix+1,iy,iz)   =                xx(ix+1,iy,iz)   + yy(ix,iy-1,iz) * ap
            xx(ix-1,iy,iz)   =                xx(ix-1,iy,iz)   + yy(ix,iy-1,iz) * am
            xx(ix,  iy-1,iz) =                xx(ix,  iy-1,iz) - yy(ix,iy-1,iz) * a
            xx(ix-1,iy-1,iz) =                xx(ix-1,iy-1,iz) - yy(ix,iy-1,iz) * ap
            xx(ix+1,iy-1,iz) =                xx(ix+1,iy-1,iz) - yy(ix,iy-1,iz) * am
          else
            t=0.
            t=           t+  real((xx(ix-1,iy,iz)-xx(ix+1,iy-1,iz)),dp&
              &) *real( am,dp)
            t=           t+ real((xx(ix,  iy,iz)-xx(ix,  iy-1,iz)),dp)&
              &*real(a ,dp)
            t=           t+ real( (xx(ix+1,iy,iz)-xx(ix-1,iy-1,iz)),dp&
              &) *real( ap,dp)
            yy(ix,iy-1,iz) =           yy(ix,iy-1,iz) +t
          end if
        end do
      end do
    end do
  end subroutine 
  subroutine allpass_3d_close()
  end subroutine 
end module 
