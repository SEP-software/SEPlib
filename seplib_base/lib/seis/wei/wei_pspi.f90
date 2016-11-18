module wei_wc_mod
  use wei_basics_mod
  use wei_slow_mod
  use wei_fft_mod
  !! fk-fx migration
  !! receive wfld at (izs,iws,ith)
  !! return  wfld downward/upward continued
  implicit none
  complex, pointer :: tmp1(:,:,:,:,:)
  complex, pointer :: tmp2(:,:,:,:,:)
  complex, pointer :: big(:,:,:,:,:,:),tin(:,:)
  real, pointer :: xamp(:),yamp(:)
  integer, allocatable :: imap(:,:,:) 
  integer, private, save :: npadx,npady


  interface weikxmig
    module procedure weikxmig_1wave
  end interface


contains



subroutine weikxmig_1wave(wfld,iws,izs,ith,KXMIGop,FKop,FXop)
    complex, dimension(:,:,:,:,:), pointer :: wfld
    integer,external,optional ::    FKop,FXop
    integer :: izs,iws,ith
    integer :: st
    interface 
       integer function KXMIGop(wfld,iws,izs,ith,FKop,FXop) result(st)
         complex, dimension(:,:,:,:,:), pointer :: wfld
         integer, intent(in)       :: iws,izs,ith
         integer,external,optional :: FKop,FXop
       end function KXMIGop
    end interface 

    st = KXMIGop(wfld,iws,izs,ith,FKop,FXop)

end subroutine weikxmig_1wave


integer function weikxmigN_combo(wfld,iws,izs,ith,FKop,FXop) result(st)
    complex, dimension(:,:,:,:,:), pointer :: wfld
    integer, intent(in)       :: iws,izs,ith
    integer                   :: ifk,isource,ierr
    interface 
       integer function FKop(iws,izs,ifk,ith,wfld) result(st)
         integer, intent(in) :: iws,izs,ifk,ith
         complex, dimension(:,:,:,:,:), pointer :: wfld
       end function FKop
       integer function FXop(iws,izs,ifk,ith,wfld) result(st)
         integer, intent(in) :: iws,izs,ifk,ith
         complex, dimension(:,:,:,:,:), pointer :: wfld
       end function FXop
    end interface 

    call store_current_s_r(.true.)
      st=weikxmigN_single(wfld,iws,izs,ith,Fkop,Fxop)
  end function weikxmigN_combo




integer function weikxmigN_mid(wfld,iws,izs,ith,FKop,FXop) result(st)
    complex, dimension(:,:,:,:,:), pointer :: wfld
    integer, intent(in)       :: iws,izs,ith
    integer                   :: ifk,isource,ierr,ib,ie
    interface 
       integer function FKop(iws,izs,ifk,ith,wfld) result(st)
         integer, intent(in) :: iws,izs,ifk,ith
         complex, dimension(:,:,:,:,:), pointer :: wfld
       end function FKop
       integer function FXop(iws,izs,ifk,ith,wfld) result(st)
         integer, intent(in) :: iws,izs,ifk,ith
         complex, dimension(:,:,:,:,:), pointer :: wfld
       end function FXop
    end interface 

  !LOOP OVER SOURCES
  call assign_wc_space(tmp1,tmp2)

  allocate(tin(size(tmp1,1),size(tmp1,2)))


  do isource=1,2 !{
    call store_current_s_r(isource==1)
      st=weikxmigN_single(wfld,iws,izs,ith,Fkop,Fxop)
  end do
  call clear_wc_space()
end function weikxmigN_mid


integer function weikxmigN_init() result(st)
    integer :: er,i,padit
    type(sep3d) :: wsep
     call grab_current_wave_space_pad(wsep)
     allocate(imap(wsep%n(1),wsep%n(2),my_nomp()))
     call  set_wc_space(2)
     allocate(xamp(wsep%n(1)))
     allocate(yamp(wsep%n(2)))
     npadx=grab_current_npadx()
     npady=grab_current_npady()
     call build_amp(wsep%n(1),npadx,xamp) 
     call build_amp(wsep%n(2),npady,yamp) 
     
    st=OK
end function weikxmigN_init

subroutine build_amp(nlen,npad,amp)
integer :: i,nlen,npad,n2
real :: amp(:),f

amp=1.
if(nlen/=1 .and. npad/=0) then
  do i=1,npad
     f=real(npad+1-i)/real(npad)
     amp(i)=cos(f*atan(1.)*2)
     amp(nlen-i+1)=cos(f*atan(1.)*2)**2
!     amp(i)=0.
!     amp(nlen-i+1)=0.
  end do
end if
end subroutine


integer function weikxmigN_single(wfld,iws,izs,ith,FKop,FXop) result(st)
    complex, dimension(:,:,:,:,:), pointer :: wfld
    integer, intent(in)       :: iws,izs,ith
    integer                   :: ifk,isource,ierr,nref,i1,i2,i3,i4
    logical                   :: adj
    interface 
       integer function FKop(iws,izs,ifk,ith,wfld) result(st)
         integer, intent(in) :: iws,izs,ifk,ith
         complex, dimension(:,:,:,:,:), pointer :: wfld
       end function FKop
       integer function FXop(iws,izs,ifk,ith,wfld) result(st)
         integer, intent(in) :: iws,izs,ifk,ith
         complex, dimension(:,:,:,:,:), pointer :: wfld
       end function FXop
    end interface 


    
   
   adj= grab_current_adj()
   call grab_current_nref(nref)

    if(adj) then !! MIGRATION {
          call store_wavefield(wfld,ith,iws,.true.) !STORE THE CURRENT WAVEFIELD
          do ifk=1,nref!{
             call store_current_iref(ifk)
             call grab_part_wvfld(wfld,ifk,ith,iws,izs)!GRAB PORTION OF THE WFLD
             st   = FXop(iws,izs,ifk,ith,wfld) !! f-x op
             call weiift(iws,izs,    ith,wfld)
             st   = FKop(iws,izs,ifk,ith,wfld) !! f-k op
!          call weifft(iws,izs,    ith,wfld)
             call add_wavefield(wfld,ith,iws)
          end do !}
          call grab_wavefield(wfld,iws,ith,.true.) !GRAB THE ENTIRE WAVEFIELD
          call weifft(iws,izs,    ith,wfld)
          call damp_wave(wfld,iws)
    else             !!} MODELLING {
          call damp_wave(wfld,iws) !damp the stored wavefield
          call weifft(iws,izs,    ith,wfld)         !transform into fk 
          call store_wavefield(wfld,ith,iws,.false.) !store fx wfld
          do ifk=1,nref!{
             call grab_wavefield(wfld,iws,ith,.true.)
             call store_current_iref(ifk)
!          call weifft(iws,izs,    ith,wfld)
             st   = FKop(iws,izs,ifk,ith,wfld) !! f-k op  !do fk op
             call weiift(iws,izs,    ith,wfld)             !transform into fx
             st   = FXop(iws,izs,ifk,ith,wfld) !! f-x op   !do fx op
             call store_part_wavefield(wfld,ifk,ith,iws,izs)  !add fx
          end do !}
!grab main
!           grab unpadded
          call grab_wavefield(wfld,iws,ith,.false.);
   end if!}



    st=OK
end function weikxmigN_single

subroutine damp_wave(wfld,iws)
integer :: i1,i2,i3,i4,iws
complex :: wfld(:,:,:,:,:)
  if (npadx /=0 .or. npady/=0) then
       do i4=1,size(wfld,4)
       do i3=1,size(wfld,3)
         do i2=1,size(wfld,2)
           do i1=1,size(wfld,1)
             wfld(i1,i2,i3,i4,iws)=wfld(i1,i2,i3,i4,iws)*xamp(i1)*yamp(i2)
           end do 
         end do 
       end do 
     end do 
  end if
end subroutine

integer function weikxmig1(wfld,iws,izs,ith,FKop,FXop) result(st)
    complex, dimension(:,:,:,:,:), pointer :: wfld
    integer, intent(in)       :: iws,izs,ith
    integer                   :: ifk,isource,ierr
    logical                   :: adj
    interface 
       integer function FKop(iws,izs,ifk,ith,wfld) result(st)
         integer, intent(in) :: iws,izs,ifk,ith
         complex, dimension(:,:,:,:,:), pointer :: wfld
       end function FKop
       integer function FXop(iws,izs,ifk,ith,wfld) result(st)
         integer, intent(in) :: iws,izs,ifk,ith
         complex, dimension(:,:,:,:,:), pointer :: wfld
       end function FXop
    end interface 

    adj= grab_current_adj()
    !REDO THE KMAPS IN CASE WE HAVE CHANGED THE OFFSET RANGE
    if(adj) then !! MIGRATION {
         call store_current_s_r(.true.)
         st   = FXop(iws,izs,ifk,ith,wfld) !! f-x op
         call store_current_s_r(.false.)
         st   = FXop(iws,izs,ifk,ith,wfld) !! f-x op
         call weiift(iws,izs,    ith,wfld)
         st   = FKop(iws,izs,ifk,ith,wfld) !! f-k op
         call store_current_s_r(.true.)
         st   = FKop(iws,izs,ifk,ith,wfld) !! f-x op
         call weifft(iws,izs,    ith,wfld)
    else             !!} MODELLING {
         call weiift(iws,izs,    ith,wfld)
         call store_current_s_r(.true.)
         st   = FKop(iws,izs,ifk,ith,wfld) !! f-k op
         call store_current_s_r(.false.)
         st   = FKop(iws,izs,ifk,ith,wfld) !! f-k op
         call weifft(iws,izs,    ith,wfld)
         st   = FXop(iws,izs,ifk,ith,wfld) !! f-x op
         call store_current_s_r(.true.)
         st   = FXop(iws,izs,ifk,ith,wfld) !! f-x op
    end if!}

    st=OK
end function weikxmig1

subroutine store_wavefield(wfld,ith,iws,zero1)
 complex :: wfld(:,:,:,:,:)
 logical :: zero1
 integer :: ierr,iws,ith,i1,i2,i3,i4
  
  if(zero1) then
    tmp1(:,:,:,:,ith) = 0.
!  tmp2(:,:,:,;,ith) =wfld(:,:,:,:,iws)
do i4=1,size(wfld,4)
do i3=1,size(wfld,3)
  tin=wfld(:,:,i3,i4,iws)
  tmp2(:,:,i3,i4,ith) =tin
end do
end do
  else
    tmp1(:,:,:,:,ith) = wfld(:,:,:,:,iws)
    tmp2(:,:,:,:,ith) = 0.
  end if
end subroutine

subroutine grab_part_wvfld(wfld,ifk,ith,iws,izs)
  integer :: ith,iws,ifk,ierr,izs,iref,iomp,i3,i4,i
  complex :: wfld(:,:,:,:,:)
  logical :: source 

  iomp=my_iomp()
  call grab_current_iref(iref)
  do i4=1,size(wfld,4)
    do i3=1,size(wfld,3)
    call store_current_ihx_ihy(i3,i4)
     call  grab_iref_mid_map(imap(:,:,iomp))
     where(imap(:,:,iomp)==iref)
       wfld(:,:,i3,i4,iws) = tmp2(:,:,i3,i4,ith)
     elsewhere
         wfld(:,:,i3,i4,iws) = 0.
     end where
   end do
 end do
end subroutine

subroutine add_wavefield(wfld,ith,iws)
  complex :: wfld(:,:,:,:,:)
  integer :: ith,iws,i1,i2,ierr
  tmp1(:,:,:,:,ith) = tmp1(:,:,:,:,ith) +  wfld(:,:,:,:,iws)
end subroutine

subroutine grab_wavefield(wfld,iws,ith,first)
  complex :: wfld(:,:,:,:,:)
        logical :: first
        integer :: ith,iws,i1,i2,ierr
        if(first) then 
           wfld(:,:,:,:,iws) = tmp1(:,:,:,:,ith)
        else
           wfld(:,:,:,:,iws) = tmp2(:,:,:,:,ith)
        end if
end subroutine

subroutine store_part_wavefield(wfld,ifk,ith,iws,izs)
 complex wfld(:,:,:,:,:)
  integer :: ifk,ith,iws,ierr,izs,i1,i2,i3,i4
  integer   ::iref,iomp

  iomp=my_iomp()
  call grab_current_iref(iref)
  do i4=1,size(wfld,4)
    do i3=1,size(wfld,3)
      call store_current_ihx_ihy(i3,i4)
      call  grab_iref_mid_map(imap(:,:,my_iomp()))
      do i2=1,size(wfld,2)
        do i1=1,size(wfld,1)
          if(imap(i1,i2,iomp)==iref) then
            tmp2(i1,i2,i3,i4,ith)=tmp2(i1,i2,i3,i4,ith)+wfld(i1,i2,i3,i4,iws)
          end if
        end do
      end do
    end do
  end do
end subroutine

end module
