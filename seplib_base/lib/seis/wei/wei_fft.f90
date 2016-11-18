!HANDLE FFTS
module wei_fft_mod
  use wei_flags
  use wei_wavespace_mod
  implicit none
  integer*8,pointer,private,save :: planF(:),planI(:),extraF(:),extraI(:)
  real, private,save :: in123
contains
  !----------------------------------------------------------------
  !INITIALIZE THE FFT
  subroutine weifft_init(wfld)
    complex :: wfld(:,:,:,:,:)
    integer :: i,j,k
    type(sep3d) :: wsep 
    integer :: ierr
   call grab_current_wave_space_pad(wsep)
   in123=sqrt(1./real(product(wsep%n(1:4))))

   allocate(planF(size(wfld,5)))
   allocate(planI(size(wfld,5)))
   call add_mem(size(planF)+size(planI))



   do i=1,size(wfld,5)
     call sfftw_plan_dft(planF(i),4,wsep%n,wfld(1,1,1,1,i),wfld(1,1,1,1,i),&
       ffTW_FORWARD,fftW_PATIENT)
     call sfftw_plan_dft(planI(i),4,wsep%n,wfld(1,1,1,1,i),wfld(1,1,1,1,i),&
       ffTW_BACKWARD,fftW_PATIENT)
   end do

!   if(nextra_fft() >0) then
!     allocate(extraF(my_nomp()*nextra_fft()))
!     allocate(extraI(my_nomp()*nextra_fft()))
!     call add_mem(size(extraF)+size(extraI))
!     do k=1,nextra_fft()
!       do j=1,my_nomp()
!          i=size(tmp_on,5)-k*my_nomp()+j
!          call sfftw_plan_dft(extraI(j+(k-1)*my_nomp()),4,n,tmp_on(1,1,1,1,i),&
!            tmp_on(1,1,1,1,i),FFTW_BACKWARD,FFTW_PATIENT)
!        end do
!     end do 
!   end if

  end subroutine weifft_init





  !----------------------------------------------------------------
  !! forward extra FFT
  subroutine weifft_e(ith,ipart,data)
    integer, intent(in) :: ith,ipart
    complex, dimension(:,:,:,:,:) :: data
    integer :: imx,imy,ndim
    integer :: iplan,i3,i1,n1,n2,i2,i4
    integer :: nd(4),nf(4)
    iplan=ith+(ipart-1)*my_nomp()
    
  data(:,:,:,:,ith)=data(:,:,:,:,ith)*in123
 end subroutine


  !----------------------------------------------------------------
  !! inverse FFT
  subroutine weiift_e(ith,ipart,data)
    integer, intent(in) ::  ith,ipart
    complex, dimension(:,:,:,:,:), pointer :: data
    integer :: imx,imy,iplan,nd(4),i1,i2,i3,i4

    iplan=ith+(ipart-1)*my_nomp()
    call sfftw_execute(extraI(iplan))
   data(:,:,:,:,ith)=data(:,:,:,:,ith)*in123
  end subroutine weiift_e




  !----------------------------------------------------------------
  !! forward FFT
  subroutine weifft(iws,izs,ith,data)
    integer, intent(in) :: iws,ith,izs
    complex, dimension(:,:,:,:,:) :: data
    integer :: imx,imy,ndim
    integer :: iplan,i3,i1,n1,n2,i2,i4,ierr
    integer :: nd(4),nf(4)
    call sfftw_execute(planF(iws))
  data(:,:,:,:,iws)=data(:,:,:,:,iws)*in123
 end subroutine


  !----------------------------------------------------------------
  !! inverse FFT
  subroutine weiift(iws,izs,ith,data)
    integer, intent(in) :: iws, ith,izs
    complex, dimension(:,:,:,:,:), pointer :: data
    integer :: imx,imy,iplan,nd(4),i1,i2,i3,i4,ierr

   call sfftw_execute(planI(iws))
   data(:,:,:,:,iws)=data(:,:,:,:,iws)*in123

  end subroutine weiift


end module wei_fft_mod
