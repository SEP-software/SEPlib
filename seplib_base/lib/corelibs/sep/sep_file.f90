module sepfile_mod
  use hypercube_mod
  implicit none
  
  type,extends(hypercube) :: sepfile
    character(len=128) :: tag,data_type
    contains 
     procedure, pass  :: write_description
 end type


 interface init_sepfile
   module procedure from_tag,from_hyper 
 end interface
 
 
 interface sep_read
    module procedure sre_r1,sre_r2,sre_r3,sre_r4,sre_r5
    module procedure sre_i1,sre_i2,sre_i3, sre_i4,sre_i5
    module procedure sre_c1,sre_c2,sre_c3, sre_c4,sre_c5

end interface

interface sep_write
  module procedure sri_r1,sri_r2,sri_r3,sri_r4,sri_r5
  module procedure sri_i1,sri_i2,sri_i3,sri_i4,sri_i5
  module procedure sri_c1,sri_c2,sri_c3,sri_c4,sri_c5

end interface

 contains
 

 subroutine from_hyper(hout,tag,hyper,int,typ)
   character(len=*),intent(in) :: tag,int,typ
   type(sepfile),intent(out) :: hout
   type(hypercube), intent(in)  :: hyper
  
  if(int(1:3)=="INO") then
     call auxinout(tag)
  else if(int(1:2)=="IN") then
    call seperr("can't a sepfile from a hypercube when input file intent is in")
  else if(int(1:3)=="OUT") then
    !SEPlib will do the right thing with out type by default
  else if(int(1:3)=="TEM") then
    call auxtmp(tag)
  else 
    write(0,*) "tag=",trim(int)
    call seperr("unknown intent")
  end if
  hout%tag=tag
  hout%data_type=typ
  
  if(typ(1:2)/="RE" .and. typ(1:2)/="CO" .and. typ(1:2)/="IN") &
    call seperr("unknown data type")
  
  call hout%hyper_copy(hyper)
  call hout%write_description()
end subroutine

subroutine from_tag(hout,tag,int,typ)
  type(sepfile),intent(out) :: hout
  character(len=*),intent(in) :: tag,int,typ
  integer :: i,ndim
  if(int(1:3)=="INO") then
     call auxinout(tag)
  else if(int(1:3)=="OUT") then
    call seperr("can't create a sepfile from a tag when intent is out")
  else if(int(1:2)=="IN") then
    !SEPlib will do the right thing with out type by default
    write(0,*) "tag=",trim(int)
    call seperr("unknown intent")
  end if
  hout%tag=tag
  if(0/=sep_get_number_data_axes(tag,ndim)) &
    call seperr("trouble getting the number of data axes")
  
  call set_dimensions(ndim)
  do i=1,size(hout%n)
    if(0/=sep_get_data_axis_par(tag,i,hout%n(i),hout%o(i),hout%d(i),hout%label(i))) &
      call seperr("trouble getting data axis")
 end do
 
    hout%data_type=typ

  if(typ(1:2)/="RE" .and. typ(1:2)/="CO" .and. typ(1:2)/="IN") &
    call seperr("unknown data type")
end subroutine


subroutine write_description(hyper)
  class(sepfile) :: hyper
  integer :: i
  
  do i=1,size(hyper%n)
    if(0/=sep_put_data_axis_par(hyper%tag,i,hyper%n(i),hyper%o(i),hyper%d(i),hyper%label(i))) &
      call seperr("trouble writing out description")
 end do
end subroutine

subroutine sre_r1(hyper,ar)
class(sepfile) :: hyper
 real :: ar(:)
 if(size(ar)*4/=sreed(hyper%tag,ar,size(ar)*4)) &
  call seperr("trouble reading dataset")
end subroutine

subroutine sre_r2(hyper,ar)
class(sepfile) :: hyper
 real :: ar(:,:)
 if(size(ar)*4/=sreed(hyper%tag,ar,size(ar)*4)) &
  call seperr("trouble reading dataset")
end subroutine

subroutine sre_r3(hyper,ar)
class(sepfile) :: hyper
 real :: ar(:,:,:)
 if(size(ar)*4/=sreed(hyper%tag,ar,size(ar)*4)) &
  call seperr("trouble reading dataset")
end subroutine

subroutine sre_r4(hyper,ar)
class(sepfile) :: hyper
 real :: ar(:,:,:,:)
 if(size(ar)*4/=sreed(hyper%tag,ar,size(ar)*4)) &
  call seperr("trouble reading dataset")
end subroutine

subroutine sre_r5(hyper,ar)
class(sepfile) :: hyper
 real :: ar(:,:,:,:,:)
 if(size(ar)*4/=sreed(hyper%tag,ar,size(ar)*4)) &
  call seperr("trouble reading dataset")
end subroutine



subroutine sri_r1(hyper,ar)
class(sepfile) :: hyper
 real :: ar(:)
 if(size(ar)*4/=srite(hyper%tag,ar,size(ar)*4)) &
  call seperr("trouble reading dataset")
end subroutine

subroutine sri_r2(hyper,ar)
class(sepfile) :: hyper
 real :: ar(:,:)
 if(size(ar)*4/=srite(hyper%tag,ar,size(ar)*4)) &
  call seperr("trouble reading dataset")
end subroutine

subroutine sri_r3(hyper,ar)
class(sepfile) :: hyper
 real :: ar(:,:,:)
 if(size(ar)*4/=srite(hyper%tag,ar,size(ar)*4)) &
  call seperr("trouble reading dataset")
end subroutine

subroutine sri_r4(hyper,ar)
class(sepfile) :: hyper
 real :: ar(:,:,:,:)
 if(size(ar)*4/=srite(hyper%tag,ar,size(ar)*4)) &
  call seperr("trouble reading dataset")
end subroutine

subroutine sri_r5(hyper,ar)
class(sepfile) :: hyper
 real :: ar(:,:,:,:,:)
 if(size(ar)*4/=srite(hyper%tag,ar,size(ar)*4)) &
  call seperr("trouble reading dataset")
end subroutine






subroutine sre_i1(hyper,ar)
class(sepfile) :: hyper
 integer :: ar(:)
 if(size(ar)*4/=sreed(hyper%tag,ar,size(ar)*4)) &
  call seperr("trouble reading dataset")
end subroutine

subroutine sre_i2(hyper,ar)
class(sepfile) :: hyper
 integer :: ar(:,:)
 if(size(ar)*4/=sreed(hyper%tag,ar,size(ar)*4)) &
  call seperr("trouble reading dataset")
end subroutine

subroutine sre_i3(hyper,ar)
class(sepfile) :: hyper
 integer :: ar(:,:,:)
 if(size(ar)*4/=sreed(hyper%tag,ar,size(ar)*4)) &
  call seperr("trouble reading dataset")
end subroutine

subroutine sre_i4(hyper,ar)
class(sepfile) :: hyper
 integer :: ar(:,:,:,:)
 if(size(ar)*4/=sreed(hyper%tag,ar,size(ar)*4)) &
  call seperr("trouble reading dataset")
end subroutine

subroutine sre_i5(hyper,ar)
class(sepfile) :: hyper
 integer :: ar(:,:,:,:,:)
 if(size(ar)*4/=sreed(hyper%tag,ar,size(ar)*4)) &
  call seperr("trouble reading dataset")
end subroutine




subroutine sri_i1(hyper,ar)
class(sepfile) :: hyper
 integer :: ar(:)
 if(size(ar)*4/=srite(hyper%tag,ar,size(ar)*4)) &
  call seperr("trouble reading dataset")
end subroutine

subroutine sri_i2(hyper,ar)
class(sepfile) :: hyper
 integer :: ar(:,:)
 if(size(ar)*4/=srite(hyper%tag,ar,size(ar)*4)) &
  call seperr("trouble reading dataset")
end subroutine

subroutine sri_i3(hyper,ar)
class(sepfile) :: hyper
 integer :: ar(:,:,:)
 if(size(ar)*4/=srite(hyper%tag,ar,size(ar)*4)) &
  call seperr("trouble reading dataset")
end subroutine

subroutine sri_i4(hyper,ar)
class(sepfile) :: hyper
 integer :: ar(:,:,:,:)
 if(size(ar)*4/=srite(hyper%tag,ar,size(ar)*4)) &
  call seperr("trouble reading dataset")
end subroutine

subroutine sri_i5(hyper,ar)
class(sepfile) :: hyper
 integer :: ar(:,:,:,:,:)
 if(size(ar)*4/=srite(hyper%tag,ar,size(ar)*4)) &
  call seperr("trouble reading dataset")
end subroutine



subroutine sre_c1(hyper,ar)
class(sepfile) :: hyper
 complex :: ar(:)
 if(size(ar)*8/=sreed(hyper%tag,ar,size(ar)*8)) &
  call seperr("trouble reading dataset")
end subroutine

subroutine sre_c2(hyper,ar)
class(sepfile) :: hyper
 complex :: ar(:,:)
 if(size(ar)*8/=sreed(hyper%tag,ar,size(ar)*8)) &
  call seperr("trouble reading dataset")
end subroutine

subroutine sre_c3(hyper,ar)
class(sepfile) :: hyper
 complex :: ar(:,:,:)
 if(size(ar)*8/=sreed(hyper%tag,ar,size(ar)*8)) &
  call seperr("trouble reading dataset")
end subroutine

subroutine sre_c4(hyper,ar)
class(sepfile) :: hyper
 complex :: ar(:,:,:,:)
 if(size(ar)*8/=sreed(hyper%tag,ar,size(ar)*8)) &
  call seperr("trouble reading dataset")
end subroutine

subroutine sre_c5(hyper,ar)
class(sepfile) :: hyper
 complex :: ar(:,:,:,:,:)
 if(size(ar)*8/=sreed(hyper%tag,ar,size(ar)*8)) &
  call seperr("trouble reading dataset")
end subroutine


subroutine sri_c1(hyper,ar)
class(sepfile) :: hyper
 complex :: ar(:)
 if(size(ar)*8/=srite(hyper%tag,ar,size(ar)*8)) &
  call seperr("trouble reading dataset")
end subroutine

subroutine sri_c2(hyper,ar)
class(sepfile) :: hyper
 complex :: ar(:,:)
 if(size(ar)*8/=srite(hyper%tag,ar,size(ar)*8)) &
  call seperr("trouble reading dataset")
end subroutine

subroutine sri_c3(hyper,ar)
class(sepfile) :: hyper
 complex :: ar(:,:,:)
 if(size(ar)*8/=srite(hyper%tag,ar,size(ar)*8)) &
  call seperr("trouble reading dataset")
end subroutine

subroutine sri_c4(hyper,ar)
class(sepfile) :: hyper
 complex :: ar(:,:,:,:)
 if(size(ar)*8/=srite(hyper%tag,ar,size(ar)*8)) &
  call seperr("trouble reading dataset")
end subroutine

subroutine sri_c5(hyper,ar)
class(sepfile) :: hyper
 complex :: ar(:,:,:,:,:)
 if(size(ar)*8/=srite(hyper%tag,ar,size(ar)*8)) &
  call seperr("trouble reading dataset")
end subroutine


end module




