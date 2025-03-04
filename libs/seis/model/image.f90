module image_mod
use extrapolation_types
use sep3d_struct_mod
use sep_mod

implicit none
type(sep3d), private :: image,image_x,image_z,image_t
integer,private :: image_block_size,image_block_size_x,image_block_size_z,image_block_size_t
real,private,pointer ::image_block_x(:,:,:),image_block_z(:,:,:),image_block_t(:,:,:) ! z,(hz or hx ht),x
real,private,pointer ::image_block(:,:)
integer,private :: image_nx,image_nz 
real, private:: shot_image_min_x,shot_image_max_x
integer,private::shot_image_nminx,shot_image_nmaxx,shot_image_nminz
integer,private::shot_image_block_size,shot_image_block_size_x,shot_image_block_size_z,shot_image_block_size_t
contains

subroutine image_init(extrapolation,i_node)
type(extrapolation_type)::extrapolation
integer :: i_node
integer :: ix
! integer, external :: srite
real, allocatable ::imgtmp(:)
shot_image_nminz=nint((extrapolation%image_z_min-extrapolation%z0)/extrapolation%dz)+1
image_nz=extrapolation%nz-shot_image_nminz+1
image_block_size=image_nz*4
image_block_size_x=(2*extrapolation%img_nhx-1)*image_block_size
image_block_size_z=(2*extrapolation%img_nhz-1)*image_block_size
image_block_size_t=extrapolation%img_nht*image_block_size


if (i_node == 0 ) then
  allocate(imgtmp(image_nz))
  imgtmp=0.
  !initialize image writing
  if (extrapolation%img_nhx==1 .and. extrapolation%img_nhz==1 .and. extrapolation%img_nht==1) then
    if (.NOT. extrapolation%input_image) then
      call init_sep3d(image, "OUTPUT","FLOAT", "REGULAR", ctag="Image")
      call axis_allocate(image,2)
      ! 1 is z
      image%o(1)=extrapolation%image_z_min
      image%n(1)=image_nz
      image%d(1)=extrapolation%dz
      ! 2 is x
      image%o(2)=extrapolation%image_x_min
      image%d(2)=extrapolation%dx
      image%n(2)=nint((extrapolation%image_x_max-extrapolation%image_x_min) &
             /extrapolation%dx)+1
      call sep3d_set_sep3d(image)
      call sep3d_write_description("Image",image)
      do ix=1,image%n(2)
        if(srite("Image",imgtmp(:),image_block_size)/=image_block_size)call seperr("Error initial Image")
      end do
      call sep3df_delete(image,"Image")
    end if
    call init_sep3d("Image",image,"SCRATCH")
  end if

  if (extrapolation%img_nhx >1 ) then
    if (.NOT. extrapolation%input_image) then
      call init_sep3d(image_x, "OUTPUT","FLOAT", "REGULAR", ctag="Image_X")
      call axis_allocate(image_x,3)
      ! 1 is z
      image_x%o(1)=extrapolation%image_z_min
      image_x%n(1)=image_nz
      image_x%d(1)=extrapolation%dz
      ! 3 is x
      image_x%o(3)=extrapolation%image_x_min
      image_x%d(3)=extrapolation%dx
      image_x%n(3)=nint((extrapolation%image_x_max-extrapolation%image_x_min) &
             /extrapolation%dx)+1

      ! 2 is hx
      image_x%o(2)=-(extrapolation%img_nhx-1)*extrapolation%dx
      image_x%d(2)=extrapolation%dx
      image_x%n(2)=extrapolation%img_nhx*2-1
      call sep3d_set_sep3d(image_x)
      call sep3d_write_description("Image_X",image_x)
      do ix=1,image_x%n(2)*image_x%n(3)
        if(srite("Image_X",imgtmp(:),image_block_size)/=image_block_size)call seperr("Error initial Image")
      end do
      call sep3df_delete(image_x,"Image_X")
    end if
    call init_sep3d("Image_X",image_x,"SCRATCH")  
  end if


  if (extrapolation%img_nhz >1 ) then
    if (.NOT. extrapolation%input_image) then
      call init_sep3d(image_z, "OUTPUT","FLOAT", "REGULAR", ctag="Image_Z")
      call axis_allocate(image_z,3)
      ! 1 is z
      image_z%o(1)=extrapolation%image_z_min
      image_z%n(1)=image_nz
      image_z%d(1)=extrapolation%dz
      ! 3 is x
      image_z%o(3)=extrapolation%image_x_min
      image_z%d(3)=extrapolation%dx
      image_z%n(3)=nint((extrapolation%image_x_max-extrapolation%image_x_min) &
             /extrapolation%dx)+1
      ! 2 is hz
      image_z%o(2)=-(extrapolation%img_nhz-1)*extrapolation%dz
      image_z%d(2)=extrapolation%dz
      image_z%n(2)=extrapolation%img_nhz*2-1

      call sep3d_set_sep3d(image_z)
      call sep3d_write_description("Image_Z",image_z)
      do ix=1,image_z%n(2)*image_z%n(3)
        if(srite("Image_Z",imgtmp(:),image_block_size)/=image_block_size)call seperr("Error initial Image")
      end do
      call sep3df_delete(image_z,"Image_Z")
    end if
    call init_sep3d("Image_Z",image_z,"SCRATCH")  
  end if


  if (extrapolation%img_nht >1 ) then
    if (.NOT. extrapolation%input_image) then
      call init_sep3d(image_t, "OUTPUT","FLOAT", "REGULAR", ctag="Image_T")
      call axis_allocate(image_t,3)
      ! 1 is z
      image_t%o(1)=extrapolation%image_z_min
      image_t%n(1)=image_nz
      image_t%d(1)=extrapolation%dz
      ! 3 is x
      image_t%o(3)=extrapolation%image_x_min
      image_t%d(3)=extrapolation%dx
      image_t%n(3)=nint((extrapolation%image_x_max-extrapolation%image_x_min) &
             /extrapolation%dx)+1
      ! 2 is hx
      image_t%o(2)=0
      image_t%d(2)=extrapolation%dt
      image_t%n(2)=extrapolation%img_nht

      call sep3d_set_sep3d(image_t)
      call sep3d_write_description("Image_T",image_t)
      do ix=1,image_t%n(2)*image_t%n(3)
        if(srite("Image_T",imgtmp(:),image_block_size)/=image_block_size)call seperr("Error initial Image")
      end do
      call sep3df_delete(image_t,"Image_T")
    end if
      call init_sep3d("Image_T",image_t,"SCRATCH")  
  end if

  deallocate(imgtmp)
end if
end subroutine image_init

! get image-nminx nmaxx
subroutine image_shot_init(extrapolation)
type(extrapolation_type) :: extrapolation
! extrapolation%nbdx is the boundary width. The image in the A-boundary is useless
shot_image_min_x=extrapolation%x_min+(extrapolation%nbdx+1)*extrapolation%dx
if (shot_image_min_x < extrapolation%image_x_min) then
  shot_image_min_x=extrapolation%image_x_min
end if
shot_image_max_x=extrapolation%x_max-(extrapolation%nbdx+1)*extrapolation%dx
if (shot_image_max_x > extrapolation%image_x_max) then
  shot_image_max_x=extrapolation%image_x_max
end if
shot_image_nminx=nint((shot_image_min_x-extrapolation%x_min)/extrapolation%dx)+1
shot_image_nmaxx=nint((shot_image_max_x-extrapolation%x_min)/extrapolation%dx)+1

if (extrapolation%img_nhx==1 .and. extrapolation%img_nhz==1 .and. extrapolation%img_nht==1) then
  allocate(image_block(image_nz,shot_image_nmaxx-shot_image_nminx+1))
  image_block=0.0 
end if
if (extrapolation%img_nhx > 1) then
  allocate(image_block_x(image_nz,extrapolation%img_nhx*2-1,shot_image_nmaxx-shot_image_nminx+1))
  image_block_x=0.0
end if

if (extrapolation%img_nhz > 1) then
  allocate(image_block_z(image_nz,extrapolation%img_nhz*2-1,shot_image_nmaxx-shot_image_nminx+1))
  image_block_z=0.0
end if

if (extrapolation%img_nht > 1) then
  allocate(image_block_t(image_nz,extrapolation%img_nht,shot_image_nmaxx-shot_image_nminx+1))
  image_block_t=0.0
end if
end subroutine image_shot_init

subroutine get_i_processor_img_min_max(extrapolation,x_min_max,n_block,tmp_shot_image_nminx,tmp_shot_image_nmaxx)
type(extrapolation_type) :: extrapolation
real :: x_min_max(2)
integer :: n_block,tmp_shot_image_nminx,tmp_shot_image_nmaxx
real ::tmp_shot_image_min_x,tmp_shot_image_max_x

tmp_shot_image_min_x=x_min_max(1)+(extrapolation%nbdx+1)*extrapolation%dx
if (tmp_shot_image_min_x < extrapolation%image_x_min) then
  tmp_shot_image_min_x=extrapolation%image_x_min
end if
tmp_shot_image_max_x=x_min_max(2)-(extrapolation%nbdx+1)*extrapolation%dx
if (tmp_shot_image_max_x > extrapolation%image_x_max) then
  tmp_shot_image_max_x=extrapolation%image_x_max
end if
tmp_shot_image_nminx=nint((tmp_shot_image_min_x-x_min_max(1))/extrapolation%dx)+1
tmp_shot_image_nmaxx=nint((tmp_shot_image_max_x-x_min_max(1))/extrapolation%dx)+1
n_block=(tmp_shot_image_min_x-extrapolation%image_x_min)/extrapolation%dx
end subroutine get_i_processor_img_min_max


subroutine image_stack(extrapolation,shot_wave,rec_wave)
type(extrapolation_type) :: extrapolation
real :: shot_wave(:,:,:),rec_wave(:,:)
integer :: ihx,ihz,iht,iz,ix
integer :: img_jt

img_jt=nint(extrapolation%img_dt/extrapolation%dt)
if (shot_image_nmaxx > shot_image_nminx ) then

  if (extrapolation%img_nhx==1 .and. extrapolation%img_nhz==1 .and. extrapolation%img_nht==1 ) then
    do ix=shot_image_nminx,shot_image_nmaxx 
      do iz=shot_image_nminz,extrapolation%nz
        image_block(iz-shot_image_nminz+1,ix-shot_image_nminx+1)= &
         image_block(iz-shot_image_nminz+1,ix-shot_image_nminx+1)+&
         rec_wave(iz,ix)*shot_wave(extrapolation%it/img_jt,iz,ix)
      end do
    end do
  end if

  if (extrapolation%img_nhx > 1) then
    do ix=shot_image_nminx,shot_image_nmaxx
      do ihx=1,extrapolation%img_nhx
        do iz=shot_image_nminz,extrapolation%nz
          image_block_x(iz-shot_image_nminz+1,extrapolation%img_nhx-1+ihx,ix-shot_image_nminx+1)=&
          image_block_x(iz-shot_image_nminz+1,extrapolation%img_nhx-1+ihx,ix-shot_image_nminx+1) &
           +rec_wave(iz,ix-ihx+1)*shot_wave(extrapolation%it/img_jt,iz,ix+ihx-1)
          image_block_x(iz-shot_image_nminz+1,extrapolation%img_nhx+1-ihx,ix-shot_image_nminx+1)=&
          image_block_x(iz-shot_image_nminz+1,extrapolation%img_nhx+1-ihx,ix-shot_image_nminx+1) &
           +rec_wave(iz,ix+ihx-1)*shot_wave(extrapolation%it/img_jt,iz,ix-ihx+1)
        end do
      end do
    end do
  end if

  if (extrapolation%img_nhz > 1) then
    do ix=shot_image_nminx,shot_image_nmaxx
      do ihz=1,extrapolation%img_nhz
        do iz=shot_image_nminz,extrapolation%nz
          image_block_z(iz-shot_image_nminz+1,extrapolation%img_nhz-1+ihz,ix-shot_image_nminx+1)=&
          image_block_z(iz-shot_image_nminz+1,extrapolation%img_nhz-1+ihz,ix-shot_image_nminx+1) &
           +rec_wave(iz-ihz+1,ix)*shot_wave(extrapolation%it/img_jt,iz+ihz-1,ix)
          image_block_z(iz-shot_image_nminz+1,extrapolation%img_nhz+1-ihz,ix-shot_image_nminx+1)=&
          image_block_z(iz-shot_image_nminz+1,extrapolation%img_nhz+1-ihz,ix-shot_image_nminx+1) &
           +rec_wave(iz+ihz-1,ix)*shot_wave(extrapolation%it/img_jt,iz-ihz+1,ix)
        end do
      end do
    end do
  end if

  if (extrapolation%img_nht >1 ) then
    do ix=shot_image_nminx,shot_image_nmaxx
      do iht=1,extrapolation%img_nht
        do iz=shot_image_nminz,extrapolation%nz
          image_block_t(iz-shot_image_nminz+1,iht,ix-shot_image_nminx+1)=&
          image_block_t(iz-shot_image_nminz+1,iht,ix-shot_image_nminx+1) &
           +rec_wave(iz,ix)*shot_wave(extrapolation%it/img_jt+iht-1,iz,ix)
        end do
      end do
    end do
  end if

end if
end subroutine image_stack

subroutine image_shot_write(extrapolation,wave_x_min_max,i_node,n_node,node_isx,node_nsx)
type(extrapolation_type) :: extrapolation
real ::wave_x_min_max(:,:)
integer ::i_node,n_node,node_isx,node_nsx
integer :: n_block,tmp_shot_image_nminx,tmp_shot_image_nmaxx
integer :: i_processor,ierr
integer :: tmp_shot_image_block_size,tmp_shot_image_block_size_x,tmp_shot_image_block_size_z
integer :: tmp_shot_image_block_size_t,send_block_size
! integer, external :: srite,sreed,sseek_block
real,pointer :: tmp_img(:,:,:)

integer :: i_n_block

if (i_node == 0 ) then
  if (shot_image_nmaxx >shot_image_nminx) then
    n_block=(shot_image_min_x-extrapolation%image_x_min)/extrapolation%dx

    if (extrapolation%img_nhx==1 .and. extrapolation%img_nhz==1 .and. extrapolation%img_nht==1) then
      shot_image_block_size=(shot_image_nmaxx-shot_image_nminx+1)*image_block_size
      allocate(tmp_img(image_nz,shot_image_nmaxx-shot_image_nminx+1,1))
      tmp_img=0.0
      if (sseek_block("Image",n_block,image_block_size,0) /=n_block) &
       write(*,*)"Error seeking Image1"
      if (sreed("Image",tmp_img,shot_image_block_size)/=shot_image_block_size)&
       write(*,*) 'problem reading Image'
      if (sseek_block("Image",-(shot_image_nmaxx-shot_image_nminx+1),image_block_size,1)/=n_block)&
      image_block(:,:)=image_block(:,:)+tmp_img(:,:,1)
      if ( srite("Image",image_block,shot_image_block_size) /= shot_image_block_size ) &
       write(*,*) "trouble in writing image"
      deallocate(tmp_img)
    end if

    if (extrapolation%img_nhx >1 ) then
      shot_image_block_size_x=(shot_image_nmaxx-shot_image_nminx+1)*image_block_size_x
      allocate(tmp_img(image_nz,2*extrapolation%img_nhx-1,shot_image_nmaxx-shot_image_nminx+1))
      tmp_img=0.0
      if (sseek_block("Image_X",n_block,image_block_size_x,0) /=n_block) call seperr("wrongseek X")
      if (sreed("Image_X",tmp_img,shot_image_block_size_x)/=shot_image_block_size_x)&
        call seperr("readX")
      if(sseek_block("Image_X",-(shot_image_nmaxx-shot_image_nminx+1),&
         image_block_size_x,1)/=n_block)call seperr("seek X2")
      image_block_x=image_block_x+tmp_img 
      if(srite("Image_X",image_block_x,shot_image_block_size_x)/=shot_image_block_size_x)call seperr("writing X")
      deallocate(tmp_img)
    end if    

    if (extrapolation%img_nhz>1) then
      shot_image_block_size_z=(shot_image_nmaxx-shot_image_nminx+1)*image_block_size_z
      allocate(tmp_img(image_nz,2*extrapolation%img_nhz-1,shot_image_nmaxx-shot_image_nminx+1))
      tmp_img=0.0
      if(sseek_block("Image_Z",n_block,image_block_size_z,0)/=n_block) call seperr("seek Z")
      if(sreed("Image_Z",tmp_img,shot_image_block_size_z)/=shot_image_block_size_z) call seperr("readZ")
      if(sseek_block("Image_Z",-(shot_image_nmaxx-shot_image_nminx+1),image_block_size_z,1)/=n_block)&
       call seperr("seek Z2")
      image_block_z=image_block_z+tmp_img
      if(srite("Image_Z",image_block_z,shot_image_block_size_z)/=shot_image_block_size_z)call seperr("writZ")
      deallocate(tmp_img)
    end if

    if (extrapolation%img_nht>1) then
      shot_image_block_size_t=(shot_image_nmaxx-shot_image_nminx+1)*image_block_size_t
      allocate(tmp_img(image_nz,extrapolation%img_nht,shot_image_nmaxx-shot_image_nminx+1))
      tmp_img=0.0
      if (sseek_block("Image_T",n_block,image_block_size_t,0)/=n_block)call seperr("seek T")
      if (sreed("Image_T",tmp_img,shot_image_block_size_t)/=shot_image_block_size_t)call seperr("readT")
      if(sseek_block("Image_T",-(shot_image_nmaxx-shot_image_nminx+1),image_block_size_t,1)/=n_block)&
       call seperr("seekT2")
      image_block_t=image_block_t+tmp_img
      if(srite("Image_T",image_block_t,shot_image_block_size_t)/=shot_image_block_size_t)call seperr("writT")
      deallocate(tmp_img)
    end if

  end if

  do i_processor=1,n_node-1
    call get_i_processor_img_min_max(extrapolation,wave_x_min_max(i_processor,:), &
     n_block,tmp_shot_image_nminx,tmp_shot_image_nmaxx)
    if (tmp_shot_image_nmaxx >tmp_shot_image_nminx ) then
      if (extrapolation%img_nhx==1 .and.extrapolation%img_nhz==1 .and. extrapolation%img_nht==1 ) then 
        send_block_size=image_nz*(tmp_shot_image_nmaxx-tmp_shot_image_nminx+1)
        tmp_shot_image_block_size=(tmp_shot_image_nmaxx-tmp_shot_image_nminx+1)*image_block_size 
        allocate(tmp_img(image_nz,tmp_shot_image_nmaxx-tmp_shot_image_nminx+1,1))
        deallocate(image_block)
        allocate(image_block(image_nz,tmp_shot_image_nmaxx-tmp_shot_image_nminx+1))
        if (sseek_block("Image",n_block,image_block_size,0) /=n_block) call seperr("Error seeking Image1")
        if (sreed("Image",image_block,tmp_shot_image_block_size)/=tmp_shot_image_block_size)& 
         call seperr('problem reading Image') 
        if (sseek_block("Image",-(tmp_shot_image_nmaxx-tmp_shot_image_nminx+1),image_block_size,1)/=n_block)&
         call seperr("problem seeking Image2")
        tmp_img(:,:,1)=tmp_img(:,:,1)+image_block(:,:)
        if (srite("Image",tmp_img,tmp_shot_image_block_size)/=tmp_shot_image_block_size)call seperr('Irit')
        deallocate(tmp_img)  
      end if ! if zero offset image
      
      if (extrapolation%img_nhx>1)then
        write(*,*) "changed"
        send_block_size=image_nz*(extrapolation%img_nhx*2-1)*(tmp_shot_image_nmaxx-tmp_shot_image_nminx+1)
        tmp_shot_image_block_size_x=(tmp_shot_image_nmaxx-tmp_shot_image_nminx+1)*image_block_size_x
        allocate(tmp_img(image_nz,extrapolation%img_nhx*2-1,tmp_shot_image_nmaxx-tmp_shot_image_nminx+1))
        deallocate(image_block_x)
        allocate(image_block_x(image_nz,extrapolation%img_nhx*2-1,tmp_shot_image_nmaxx-tmp_shot_image_nminx+1))
        if(sseek_block("Image_X",n_block,image_block_size_x,0)/=n_block) call seperr("o_seek_x")
        if(sreed("Image_X",image_block_x,tmp_shot_image_block_size_x)/=&
      tmp_shot_image_block_size_x)call seperr("o_reed_x")
        if(sseek_block("Image_X",-(tmp_shot_image_nmaxx-tmp_shot_image_nminx+1),&
    image_block_size_x,1)/=n_block) call seperr("o_seek_x2")
        tmp_img=tmp_img+image_block_x
        if(srite("Image_X",tmp_img,tmp_shot_image_block_size_x)/=tmp_shot_image_block_size_x)call seperr('o_x_write')
        deallocate(tmp_img)
      end if !if horizontal CIG
 
      if (extrapolation%img_nhz>1)then
        send_block_size=image_nz*(extrapolation%img_nhz*2-1)*(tmp_shot_image_nmaxx-tmp_shot_image_nminx+1)
        tmp_shot_image_block_size_z=(tmp_shot_image_nmaxx-tmp_shot_image_nminx+1)*image_block_size_z
        allocate(tmp_img(image_nz,extrapolation%img_nhz*2-1,tmp_shot_image_nmaxx-tmp_shot_image_nminx+1))
        deallocate(image_block_z)
        allocate(image_block_z(image_nz,extrapolation%img_nhz*2-1,tmp_shot_image_nmaxx-tmp_shot_image_nminx+1))
        if(sseek_block("Image_Z",n_block,image_block_size_z,0)/=n_block) call seperr("o_seek_z")
        if(sreed("Image_Z",image_block_z,tmp_shot_image_block_size_z)/=&
      tmp_shot_image_block_size_z)call seperr("o_reed_z")
        if(sseek_block("Image_Z",-(tmp_shot_image_nmaxx-tmp_shot_image_nminx+1),&
     image_block_size_z,1)/=n_block) call seperr("o_seek_z2")
        tmp_img=tmp_img+image_block_z
        if(srite("Image_Z",tmp_img,tmp_shot_image_block_size_z)/=tmp_shot_image_block_size_z)call seperr('o_z_write')  
        deallocate(tmp_img)
      end if !if vertical CIG

      if (extrapolation%img_nht>1)then
        send_block_size=image_nz*extrapolation%img_nht*(tmp_shot_image_nmaxx-tmp_shot_image_nminx+1)
        tmp_shot_image_block_size_t=(tmp_shot_image_nmaxx-tmp_shot_image_nminx+1)*image_block_size_t
        allocate(tmp_img(image_nz,extrapolation%img_nht,tmp_shot_image_nmaxx-tmp_shot_image_nminx+1))
        deallocate(image_block_t)
        allocate(image_block_t(image_nz,extrapolation%img_nht,tmp_shot_image_nmaxx-tmp_shot_image_nminx+1))
        if(sseek_block("Image_T",n_block,image_block_size_t,0)/=n_block) call seperr("o_seek_t")
        if(sreed("Image_T",image_block_t,tmp_shot_image_block_size_t)/=tmp_shot_image_block_size_t)call seperr("o_reed_t")
        if(sseek_block("Image_T",-(tmp_shot_image_nmaxx-tmp_shot_image_nminx+1),&
         image_block_size_t,1)/=n_block) call seperr("o_seek_t2")
        tmp_img=tmp_img+image_block_t
        if(srite("Image_T",tmp_img,tmp_shot_image_block_size_t)/=tmp_shot_image_block_size_t)call seperr('o_t_write')  
        deallocate(tmp_img)
      end if !if imge time_shift

    end if ! if tmp_shot_image_nmaxx>tmp_shot_image_nminx
  end do ! do i_processor
  
else ! for other nodes
  if (shot_image_nmaxx > shot_image_nminx) then
    if (extrapolation%img_nhx==1 .and.extrapolation%img_nhz==1 .and. extrapolation%img_nht==1 ) then
      send_block_size=(shot_image_nmaxx-shot_image_nminx+1)*image_nz
    end if
    if (extrapolation%img_nhx >1) then 
      send_block_size=(shot_image_nmaxx-shot_image_nminx+1)*image_nz*(2*extrapolation%img_nhx-1)
    end if

    if (extrapolation%img_nhz >1) then
      send_block_size=(shot_image_nmaxx-shot_image_nminx+1)*image_nz*(2*extrapolation%img_nhz-1)
    end if
    if (extrapolation%img_nht >1) then
      send_block_size=(shot_image_nmaxx-shot_image_nminx+1)*image_nz*extrapolation%img_nht
    end if
  end if
end if

if (extrapolation%img_nhx==1 .and. extrapolation%img_nhz==1 .and. extrapolation%img_nht==1) deallocate(image_block)
if (extrapolation%img_nhx >1) deallocate(image_block_x)
if (extrapolation%img_nhz >1) deallocate(image_block_z)
if (extrapolation%img_nht >1) deallocate(image_block_t)

end subroutine image_shot_write

subroutine image_clean()
end subroutine image_clean

end module 
