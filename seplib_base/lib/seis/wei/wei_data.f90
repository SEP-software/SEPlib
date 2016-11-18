module wei_data_mod
use wei_wavespace_mod
use sep_param_mod
implicit none
type(sep3d),private,save :: dsep,down_sep
character(len=128),private,save :: dtag,down_tag


contains

!-------------------------------------------------!
!                                                 !
!         INITIALIZATION ROUTINES                 !
!                                                 !
!-------------------------------------------------!
logical function init_data(erase,tag,mydsep,created)
logical :: created,erase
type(sep3d) :: mydsep
character(len=*) :: tag

init_data=.false.

if(sep3d_file_exist(tag) .and. .not. erase) then
  if(.not. init_data_tag(tag,mydsep)) then
    write(0,*) "trouble initializing tag"
    return
  end if
  created=.false.
else
  if(.not. init_data_struct(tag,mydsep)) then
    write(0,*) "trouble initializing struct data"
    return
  end if
  created=.true.
end if
init_data=.true.

end function



logical function init_data_struct(tag,mydsep)
character(len=*) :: tag
type(sep3d) :: mydsep,wsep
logical :: myre

init_data_struct=.false.

call  grab_current_wave_space(wsep)
call init_sep3d(mydsep,"SCRATCH","COMPLEX","REGULAR",(/1,1,1,1,1/))
mydsep%n(1:4)=wsep%n(1:4)
mydsep%o(1:4)=wsep%o(1:4)
mydsep%d(1:4)=wsep%d(1:4)
mydsep%label(1)="CMP_X";mydsep%label(2)="CMP_Y"
mydsep%label(3)="H_X";mydsep%label(4)="H_Y"
mydsep%n(5)=wsep%n(6);mydsep%o(5)=wsep%o(6)
mydsep%d(5)=wsep%d(6);mydsep%label(5)="FREQ"
call sep3d_set_sep3d(mydsep)

call auxout(tag)
call auxclose(tag)
call auxinout(tag)
call sep3d_write_description(tag,mydsep)
!if(.not. zero_data(tag,mydsep)) then
!  write(0,*) "trouble zeroing data"
!  return
!end if

init_data_struct=.true.
end function

logical function init_data_tag(tag,mydsep)
character(len=*) :: tag
integer :: ndim
type(sep3d) :: mydsep,wsep
init_data_tag=.false.

call init_sep3d(tag,mydsep,"SCRATCH")
ndim=sep3d_ndims(mydsep)
if(sep3d_ndims(mydsep)/=5) then
  call  grab_current_wave_space(wsep)
!  if(ndim==1) call sep3d_reshape(mydsep,(/1,1,1,1,1/))
!  if(ndim==2) call sep3d_reshape(mydsep,(/1,2,2,2,2/))
!  if(ndim==3) call sep3d_reshape(mydsep,(/1,2,3,3,3/))
!  if(ndim==4) call sep3d_reshape(mydsep,(/1,2,3,4,4/))

  mydsep%n(ndim+1:4)=wsep%n(ndim+1:4)
  mydsep%o(ndim+1:4)=wsep%o(ndim+1:4)
  mydsep%d(ndim+1:4)=wsep%d(ndim+1:4)
  mydsep%o(5)=wsep%o(6)
  mydsep%d(5)=wsep%d(6)
  mydsep%n(5)=1
  call sep3d_set_sep3d(mydsep)
end if
  
  

init_data_tag=.true.

end function

!-------------------------------------------------!
!                                                 !
!                   IO ROUTINES                   !
!                                                 !
!-------------------------------------------------!

logical function read_data_if(tag,mydsep,i_f,ielem,wfld)
type(sep3d) :: mydsep
character(len=*) :: tag
complex :: wfld(:,:,:,:,:)
integer ::i3,i4,i5,nw(5),fw(5),ndim,nalloc,nloop,i_f,nh,ielem,nuse(5)
complex, allocatable :: junkc(:,:)
logical :: ddd,big
integer :: npadx,npady
read_data_if=.false.
 
call sep_open_lock(tag)

npadx=grab_current_npadx()
npady=grab_current_npady()

nw=1
nw(1:2)=mydsep%n;  nw(5)=1; fw=0
if(mydsep%n(1)*mydsep%n(2) *mydsep%n(3)< 1000000) then
   big=.true.
   nalloc=mydsep%n(2)*mydsep%n(3)
   nw(3)=mydsep%n(3)
   nloop=1
else
   nalloc=mydsep%n(2)
   nloop=mydsep%n(3)
end if
                                                                                           
allocate(junkc(mydsep%n(1),nalloc))
call add_mem(size(junkc))

nuse=1
nuse(1:size(mydsep%n))=mydsep%n

fw=0; fw(5)=i_f-1
    do i4=1,nuse(4)
      fw(4)=i4-1
      do i3=1,nloop
        fw(3)=i3-1
        call sep3d_grab_headers(tag,mydsep,nh,nwind=nw(2:),fwind=fw(2:))
        if(.not.sep3d_read_data(tag,mydsep,junkc)) then
          write(0,*) "trouble reading i_f",i_f,sep_thread_num()
          return
        end if
        if(big) then
          wfld(npadx+1:npadx+nw(1),npady+1:npady+nw(2),:,i4,ielem)=&
            reshape(junkc,(/nw(1),nw(2),size(wfld,3)/))
        else
          wfld(npadx+1:npadx+nw(1),npady+1:npady+nw(2),i3,i4,ielem)=junkc
        end if
      end do
    end do
call del_mem(size(junkc))
deallocate(junkc)
call sep_close_lock(tag)
read_data_if=.true.
end function


logical function zero_data(tag,mydsep)
type(sep3d) :: mydsep
character(len=*) :: tag
complex, allocatable :: junkc(:,:)
integer ::i3,i4,i5,nw(5),fw(5),ndim,nalloc,nloop,i_f
logical :: ddd,big
zero_data=.false.

                                                                                           
if(mydsep%n(1)*mydsep%n(2)< 1000000) then
   big=.true.
   nalloc=mydsep%n(2)*mydsep%n(3)
   nw(3)=mydsep%n(3)
   nloop=1
else
   nalloc=mydsep%n(2)
   nloop=mydsep%n(3)
end if
                                                                                           
allocate(junkc(mydsep%n(1),nalloc))
call add_mem(size(junkc))
junkc=cmplx(0.,0.)
 

nw=mydsep%n;  nw(5)=1
fw=0;

do i5=1,mydsep%n(5)
  fw(5)=i5-1
    do i4=1,mydsep%n(4)
      fw(4)=i4-1
      do i3=1,nloop
        fw(3)=i3-1
        if(.not.sep3d_write_data(tag,mydsep,junkc,nwind=nw,fwind=fw)) then
          write(0,*) "trouble writing i_f",i_f,sep_thread_num()
          return
        end if
      end do
    end do
end do
call del_mem(size(junkc))
deallocate(junkc);
zero_data=.true.
end function


logical function write_data_if(tag,mydsep,i_f,ielem,wfld)
type(sep3d) :: mydsep
character(len=*) :: tag
complex :: wfld(:,:,:,:,:)
complex, allocatable :: junkc(:,:)
integer ::i3,i4,i5,nw(5),fw(5),ndim,nalloc,nloop,i_f,nh,ielem,npadx,npady
logical :: ddd,big,add
write_data_if=.false.

                                                                                           
nw=mydsep%n;  nw(5)=1
if(mydsep%n(1)*mydsep%n(2)*mydsep%n(3)< 1000000) then
   big=.true.
   nalloc=mydsep%n(2)*mydsep%n(3)
   nw(3)=mydsep%n(3)
   nloop=1
else
   nalloc=mydsep%n(2)
   nloop=mydsep%n(3)
   nw(3)=1
end if
                                                                                           
allocate(junkc(mydsep%n(1),nalloc))
call add_mem(size(junkc))

npadx=grab_current_npadx()
npady=grab_current_npady()
 

add=grab_current_add()
fw=0; fw(5)=i_f-1
    do i4=1,mydsep%n(4)
      fw(4)=i4-1
      do i3=1,nloop
        fw(3)=i3-1
        call sep3d_grab_headers(tag,mydsep,nh,nwind=nw(2:),fwind=fw(2:))
        if(add) then
          if(.not.sep3d_read_data(tag,mydsep,junkc)) then
            write(0,*) "trouble reading  i_f",i_f,sep_thread_num()
            return
          end if
        else 
          junkc=cmplx(0.,0.)
        end if
        if(big) then
          junkc=junkc+reshape(wfld(npadx+1:npadx+nw(1),npady+1:npady+nw(2),:,i4,ielem),(/size(junkc,1),size(junkc,2)/))
        else
          junkc=junkc+wfld(npadx+1:npadx+nw(1),npady+1:npady+nw(2),i3,i4,ielem)
        end if
        if(.not.sep3d_write_data(tag,mydsep,junkc,nwind=nw,fwind=fw)) then
          write(0,*) "trouble writing i_f",i_f,sep_thread_num()
          return
        end if
      end do
    end do
call del_mem(size(junkc))
deallocate(junkc);
write_data_if=.true.
end function



!-------------------------------------------------!
!                                                 !
!            GRAB/STORE ROUTINES                  !
!                                                 !
!-------------------------------------------------!

subroutine store_current_down_space(d)
type(sep3d) :: d
down_sep=d
end subroutine

subroutine grab_current_down_space(d)
type(sep3d) :: d
d=down_sep
end subroutine

subroutine grab_current_down_tag(d)
character(len=*) :: d
d=down_tag
end subroutine

subroutine store_current_down_tag(d)
character(len=*) :: d
down_tag=d
end subroutine







subroutine store_current_data_space(d)
type(sep3d) :: d
dsep=d
end subroutine

subroutine grab_current_data_space(d)
type(sep3d) :: d
d=dsep
end subroutine

subroutine grab_current_data_tag(d)
character(len=*) :: d
d=dtag
end subroutine

subroutine store_current_data_tag(d)
character(len=*) :: d
dtag=d
end subroutine












end module
