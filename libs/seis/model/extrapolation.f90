module extrapolation_mod
use slow_mod
use data_mod
use sep3d_struct_mod
use wavelet_mod
use kernal_mod
use wave_mod
use image_mod
use sep_io_mod
implicit none
logical, private, save :: verb
integer, parameter :: big_=selected_int_kind(11)
integer, private, save :: pct_master,pct_slave
integer, private, save :: nprint,nextprint

integer,private :: i_node,n_node
type(sep3d)::slow,data
type(extrapolation_type)::extrapolation

integer,private:: nt_sou,nt_rec 
real,private,allocatable::wave_block(:,:,:), slow_block(:,:), force_block(:) 
real, private :: hx_min, hx_max
real,private,allocatable :: shot_wave(:,:,:)
real,private :: t_delay,extrapolation_x_min, extrapolation_x_max
character(len=128) :: outtag
contains

logical function extrapolate_init()
integer ierr
logical :: restart
extrapolate_init=.true.

i_node=0
n_node=1

call extrapolation_type_init(extrapolation)

!************* morm='migration' migration, 'modeling' for modeling***********
  call from_param('restart',restart,.false.)
  call from_param('migrationormodel', extrapolation%morm, 'modeling')
  if(extrapolation%morm(1:8) =="modeling") outtag="Data"
  if(extrapolation%morm(1:9) =="migration") outtag="Image"
  if(restart)  call auxinout(outtag)
  call set_alternate_putch(outtag)
  if (extrapolation%morm(1:8)=='modeling') then
    call set_alternate_putch("Data")
    call from_param("n_source", extrapolation%nsx,   1)
    call from_param("d_source", extrapolation%dsx,   10.)
    call from_param("o_source", extrapolation%sx0,   0.)
    call from_param("dx_offset",extrapolation%dx,    10.)
    call from_param("nt_source",extrapolation%nt,1500)
    call from_param("dt",       extrapolation%dt,    0.002)  
    call from_param("hx_min",   extrapolation%hx0, -100.0)
    call from_param("n_off",    extrapolation%nhx,200)
    if ( .not. data_init(extrapolation) ) call seperr("trouble init writing data")
  else
    if (.NOT. data_init(extrapolation) ) call seperr("trouble init reading data")
    call from_param("image_nhx",extrapolation%img_nhx,1)
    call from_param("image_nhz",extrapolation%img_nhz,1)
    call from_param("image_nht",extrapolation%img_nht,1)  
  end if
  call from_param("extrapolate_oper", extrapolation%oper,'fd')
  call from_param('shotwave_in_memory',extrapolation%shot_in_memory, .false.)
  call from_param('write_wave', extrapolation%wave_write, .false.)
  call from_param('input_image',extrapolation%input_image,.false.)
  call from_param("image_dt", extrapolation%img_dt,extrapolation%dt)
  call from_param("nz_image",   extrapolation%nz,140)
  call from_param("dz_image",   extrapolation%dz,10.)
  call from_param("z_min_image",extrapolation%image_z_min,0.)
  call from_param("x_min_image",extrapolation%image_x_min,extrapolation%sx0)
  call from_param("verb", verb, .false.)
  call from_param("pct_print_master", pct_master, 2)
  call from_param("pct_print_slave", pct_slave, 10)
  call from_param("x_max_image",extrapolation%image_x_max,(extrapolation%nsx-1)* &
   extrapolation%dsx+extrapolation%sx0+extrapolation%hx0+(extrapolation%nhx-1)*extrapolation%dx)
  call from_param("z_source",extrapolation%z_sou,100.)
  call from_param("z_receiver",extrapolation%z_rec,100.0)
  ! for boundary condition for kernal, kernal.f90
  call from_param("nop",extrapolation%nop,3)
  call from_param('nx_bd_taper',extrapolation%nbtx,10)
  call from_param('nz_bd_taper',extrapolation%nbtz,10)
  call from_param('zcoe_taper',extrapolation%ztapco,0.0003)
  call from_param('xcoe_taper',extrapolation%xtapco,0.0003)
! end boundary condition parameter
  call from_param("x_min_wave", extrapolation%x_min, 999999999999999.0)
  call from_param("x_max_wave", extrapolation%x_max, -999999999999999.0)

if ( .NOT. wavelet_init(extrapolation,i_node)) then
  extrapolate_init=.false.
  write(0,*) "trouble reading wavelet"
  return
end if
!***************read slowness ************************************************
if (.NOT. slow_init(i_node)) then
  extrapolate_init=.false.
  write(0,*) "trouble init reading slowness"
  return
end if

!************ get parameters ************************************************
  !****************************************************************************
  ! seems something wrong with fft when nz is odd
  if(mod(extrapolation%nz,2)==1) then
     extrapolation%nz=extrapolation%nz+1
  end if
  !!***********************************************

  if (extrapolation%oper(1:2) == 'fd' ) then
      extrapolation%nbdz=extrapolation%nop
      extrapolation%nbdx=extrapolation%nop
  else
    if (extrapolation%nbtz > extrapolation%nop) then
      extrapolation%nbdz=extrapolation%nbtz
    else
      extrapolation%nbdz=extrapolation%nop
    end if
    if (extrapolation%nbtx > extrapolation%nop) then
      extrapolation%nbdx=extrapolation%nbtx 
    else
      extrapolation%nbdx=extrapolation%nop
    end if
  end if
  extrapolation%z0=-extrapolation%nbdz*extrapolation%dz
  extrapolation%iz_sou=(extrapolation%z_sou-extrapolation%z0)/extrapolation%dz+1
  extrapolation%iz_rec=(extrapolation%z_rec-extrapolation%z0)/extrapolation%dz+1
  if (extrapolation%nbdz > extrapolation%iz_sou .OR.extrapolation%nbdz > extrapolation%iz_rec ) then
    write(0,*) "source or Receiver in absorbing boundary"
    extrapolate_init=.false.
    return
  end if 
  if (extrapolation%nop>extrapolation%iz_sou .OR. extrapolation%nop>extrapolation%iz_rec) then
    write(0,*) "source or Receiver in absorbing boundary"
    extrapolate_init=.false.
    return
  end if

! Broadcast extrapolation
!call MPI_BCAST(extrapolation,extrapolation%MPI_extrapolation_type_Size,MPI_BYTE,0,MPI_COMM_WORLD,ierr)
if (extrapolation%morm(1:9)=='migration') call image_init(extrapolation,i_node)
nt_sou=extrapolation%nt;  nt_rec=extrapolation%nt
hx_min=extrapolation%hx0; hx_max=extrapolation%hx0+(extrapolation%nhx-1)*extrapolation%dx
extrapolation_x_min=extrapolation%x_min
extrapolation_x_max=extrapolation%x_max



!************ read wavelet and prepare for add_source ***********************
extrapolate_init=.true.
end function extrapolate_init


!--------------------------------------------------------------------------

subroutine get_x_min_max(x_min_max,isx)
real x_min_max(2)
integer isx
real :: sx,x_min,x_max
sx=extrapolation%sx0+(isx-1)*extrapolation%dsx
x_min=sx+hx_min
if (x_min < extrapolation_x_min) then
 x_min_max(1)=x_min
else
 x_min_max(1)=extrapolation_x_min
end if
if (sx-(extrapolation%nbdx+1)*extrapolation%dx < x_min_max(1) ) then
  x_min_max(1)=sx-(extrapolation%nbdx+1)*extrapolation%dx
end if
x_max=sx+hx_max
if (x_max > extrapolation_x_max) then
 x_min_max(2)=x_max
else
 x_min_max(2)=extrapolation_x_max
end if

end subroutine get_x_min_max



logical function extrapolate()
integer isx,it
logical stat,restart
real :: x_min, x_max
integer :: nx, nt_delay,ix0_rec,img_jt,status,idone
integer :: node_nsx,i_processor,node_isx,ierr,iown,ic,nsteps
real,pointer :: shot_block(:,:),wave_x_min_max(:,:),tmp_shot_block(:,:)
type(sep3d) :: wave_s
integer,allocatable :: ndone(:)
! integer,external :: sep_thread_num


img_jt=nint(extrapolation%img_dt/extrapolation%dt)
!write(*,*) img_jt

nt_delay=nint(extrapolation%t_delay/extrapolation%dt)
allocate(shot_block(extrapolation%nhx,extrapolation%nt)) !????? wait
allocate(wave_x_min_max(n_node,2))


call grab_data(data)

iown=0
iown=data%n(3)
nsteps=(nint(extrapolation%t_delay/extrapolation%dt)+ extrapolation%nt)*iown

  if(verb) then
    nprint=(real(pct_slave)/100.)*nsteps
    if(sep_thread_num()==0)  nprint=(real(pct_master)/100.)*nsteps
    nextprint=0
  else
    nextprint=nsteps+1
  end if


idone=0
if (extrapolation%morm(1:8)=='modeling' ) then !{
  allocate(ndone(data%n(3)))
  ndone=0
  call from_param("restart",restart,.false.)

  do isx=1,data%n(3) !{
     
      call get_x_min_max(wave_x_min_max(1,:),isx) !get min max from this location

      extrapolation%isx=isx;
      extrapolation%sx=extrapolation%sx0+(extrapolation%isx-1)*extrapolation%dsx
      extrapolation%x_min=wave_x_min_max(1,1)
      extrapolation%x_max=wave_x_min_max(1,2)

      extrapolation%nx=nint((extrapolation%x_max-extrapolation%x_min)/extrapolation%dx)+1
      if (mod(extrapolation%nx,2)==1) then
        extrapolation%nx=extrapolation%nx+1
      end if
      extrapolation%nx=nint((extrapolation%x_max-extrapolation%x_min)/extrapolation%dx)+1
      if (mod(extrapolation%nx,2)==1) then
        extrapolation%nx=extrapolation%nx+1
      end if
      call kernal_init(extrapolation)
      allocate(wave_block(3,extrapolation%nz,extrapolation%nx))
      allocate(force_block(extrapolation%nx))
      allocate(slow_block(extrapolation%nz,extrapolation%nx))

      if (extrapolation%shot_in_memory) then
        allocate(shot_wave(nt_sou/img_jt,extrapolation%nz,extrapolation%nx))
        shot_wave=0.
      end if
  
        !Disable for now -RGC
      if (extrapolation%wave_write) then
        call wave_init(extrapolation,n_node) 
        call grab_wave_block(wave_s)
      end if  
      wave_block=0.0
      force_block=0.0
      call kernal_auxwave_init
      call slow_read(extrapolation,slow_block)
      extrapolation%shot_or_rec='shot'



      do it=-nt_delay+1,nt_sou !{
        extrapolation%it=it
        extrapolation%t=(it-1)*extrapolation%dt
        call wavelet_addsource(extrapolation,force_block)
!   if(sep_thread_num()==3) write(*,*) "CHECK ADD",sum(force_block),extrapolation%t
        stat=extrapolate_onestep(force_block,wave_block,slow_block)
        if( it >0) then!{
          if (extrapolation%shot_in_memory) then
            if (mod(it,img_jt)==0 ) then
              shot_wave(it/img_jt,:,:)=wave_block(3,:,:)
            end if
          end if

           !Disable for now -RGC
            if (extrapolation%wave_write .and.mod(it,img_jt)==0 ) then
              if(.not.sep3d_write_data("ShotWave",wave_s,wave_block(3,:,:),&
                nwind=(/size(wave_block,1),size(wave_block,2),1,1,1,1/),&
                 fwind=(/0,0,it/img_jt-1,isx-1,1/))) &
                call seperr("trouble writing data")
              call wave_output(extrapolation,wave_block(3,:,:)) !ShotWave
            end if
        
          ix0_rec=nint((extrapolation%sx+extrapolation%hx0-extrapolation%x_min)/extrapolation%dx)+1
          shot_block(:,it)=wave_block(3,extrapolation%iz_rec,ix0_rec:ix0_rec+extrapolation%nhx-1)
        end if !}
        idone=idone+1
        if(idone > nextprint) then
          write(0,*) "Thread",sep_thread_num()," finished ",&
            nint(real(idone)*100./real(nsteps)),"% of computation"
          nextprint=nextprint+nprint
        end if
      end do !it=1,nt_sou !}

     if(.not. sep3d_write_data("Data",data,shot_block,&
       nwind=(/size(shot_block,1),size(shot_block,2),1/),&
        fwind=(/0,0,isx-1/))) &
       call seperr("trouble writing data")


      wave_block=0.
      force_block=0.
      call kernal_auxwave_init

      if (allocated(wave_block)) deallocate(wave_block)
      if (allocated(slow_block)) deallocate(slow_block)
      if (allocated(force_block)) deallocate(force_block)
      if (extrapolation%shot_in_memory) then
        deallocate(shot_wave)
      end if
      call kernal_clean 
  end do!}
!}
  !NOT DEALING WITH MIGRATION FOR NOW leave unchanged
else !{
  node_nsx=extrapolation%nsx/n_node
  do node_isx=1,node_nsx !loop over my stuff {
    do i_processor=1,n_node   !loop over all the processor
      isx=(node_isx-1)*n_node+i_processor  !get my slour location
      call get_x_min_max(wave_x_min_max(i_processor,:),isx) !get min max from this location
    end do

    if (extrapolation%morm(1:9)=='migration') then
      if (i_node == 0) then  !if i am loop 0
        do i_processor=1,n_node-1
          call data_read((node_isx-1)*n_node+i_processor,shot_block)   !read the data
        end do
        call data_read((node_isx-1)*n_node+n_node,shot_block)  !read the data
      else
      end if
    end if  
    if (i_node == 0) then
      extrapolation%isx=(node_isx-1)*n_node+n_node
      extrapolation%sx=extrapolation%sx0+(extrapolation%isx-1)*extrapolation%dsx
      extrapolation%x_min=wave_x_min_max(n_node,1)
      extrapolation%x_max=wave_x_min_max(n_node,2)
    else
      extrapolation%isx=(node_isx-1)*n_node+i_node
      extrapolation%sx=extrapolation%sx0+(extrapolation%isx-1)*extrapolation%dsx
      extrapolation%x_min=wave_x_min_max(i_node,1)
      extrapolation%x_max=wave_x_min_max(i_node,2)
    end if

    extrapolation%nx=nint((extrapolation%x_max-extrapolation%x_min)/extrapolation%dx)+1
    if (mod(extrapolation%nx,2)==1) then
      extrapolation%nx=extrapolation%nx+1
    end if
    extrapolation%nx=nint((extrapolation%x_max-extrapolation%x_min)/extrapolation%dx)+1
    if (mod(extrapolation%nx,2)==1) then
      extrapolation%nx=extrapolation%nx+1
    end if
    call kernal_init(extrapolation)
    allocate(wave_block(3,extrapolation%nz,extrapolation%nx), &
     force_block(extrapolation%nx),slow_block(extrapolation%nz,extrapolation%nx))
    if (extrapolation%shot_in_memory) then
      allocate(shot_wave(nt_sou/img_jt,extrapolation%nz,extrapolation%nx))
      shot_wave=0.
    end if
  
    if (i_node==0) then
      if (extrapolation%wave_write) then
        call wave_init(extrapolation,n_node) 
      end if  
    end if
    wave_block=0.0
    force_block=0.0
    call kernal_auxwave_init
    call slow_read(extrapolation,slow_block)
    extrapolation%shot_or_rec='shot'


    if (i_node==0) then
      if (extrapolation%wave_write) then
        call wave_seek(extrapolation,n_node)
      end if
    end if

    do it=-nt_delay+1,nt_sou !{
      extrapolation%it=it
      extrapolation%t=(it-1)*extrapolation%dt
      call wavelet_addsource(extrapolation,force_block)
      stat=extrapolate_onestep(force_block,wave_block,slow_block)
      if( it >0) then
        if (extrapolation%shot_in_memory) then
          if (mod(it,img_jt)==0 ) then
            shot_wave(it/img_jt,:,:)=wave_block(3,:,:)
          end if
        end if
        if (i_node==0) then
          if (extrapolation%wave_write .and.mod(it,img_jt)==0 ) then
            call wave_output(extrapolation,wave_block(3,:,:)) !ShotWave
          end if
        end if
        
        if (extrapolation%morm(1:8)=='modeling') then
          ix0_rec=nint((extrapolation%sx+extrapolation%hx0-extrapolation%x_min)/extrapolation%dx)+1
          shot_block(:,it)=wave_block(3,extrapolation%iz_rec,ix0_rec:ix0_rec+extrapolation%nhx-1)
        end if
      end if
    end do !it=1,nt_sou !}


    if (extrapolation%morm(1:8)=='modeling') then !{
      if (i_node == 0 ) then
        allocate(tmp_shot_block(extrapolation%nhx,extrapolation%nt))
        do i_processor=1,n_node-1
          call data_write((node_isx-1)*n_node+i_processor,tmp_shot_block)
        end do    
        deallocate(tmp_shot_block) 
        call data_write((node_isx-1)*n_node+n_node,shot_block)
      else
      end if
    end if  !}

    wave_block=0.
    force_block=0.
    call kernal_auxwave_init
    if (extrapolation%morm(1:9)=='migration') then !{
      call image_shot_init(extrapolation)
      !!******* receiver******************
      extrapolation%shot_or_rec='receiver'
      if (i_node==0) then
        if (extrapolation%wave_write) then
          call wave_seek(extrapolation,n_node)
        end if
      end if
      do it=nt_rec,1,-1 !????????????
        extrapolation%it=it
        extrapolation%t=(it-1)*extrapolation%dt
        ix0_rec=nint((extrapolation%sx+extrapolation%hx0-extrapolation%x_min)/extrapolation%dx)+1
        wave_block(3,extrapolation%iz_rec,ix0_rec:ix0_rec+extrapolation%nhx-1)=shot_block(:,it)
        stat=extrapolate_onestep(force_block,wave_block,slow_block)
        if (i_node==0) then
          if (extrapolation%wave_write .and.mod(it,img_jt)==0 ) then
            call wave_output(extrapolation,wave_block(3,:,:)) ! RecWave
          end if
        end if
        if (extrapolation%shot_in_memory) then
          if (mod(it,img_jt)==0) then
            call image_stack(extrapolation,shot_wave,wave_block(3,:,:))
          end if
        end if
        write(*,*)node_isx,'node',i_node, it, maxval(wave_block), "min", minval(wave_block)
      end do !it=nt_rec,1
      !******* end receiver*****************
      call image_shot_write(extrapolation,wave_x_min_max,i_node,n_node,node_isx,node_nsx)
    end if !}

    if (allocated(wave_block)) deallocate(wave_block)
    if (allocated(slow_block)) deallocate(slow_block)
    if (allocated(force_block)) deallocate(force_block)
    if (extrapolation%shot_in_memory) then
      deallocate(shot_wave)
    end if
    call kernal_clean 

  end do !}
end if!}
  extrapolate=.true.
end function extrapolate

subroutine extrapolation_clean
integer ierr
call wavelet_clean
call image_clean
end subroutine

end module 
