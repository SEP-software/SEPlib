module adcig_mod
  !! offset to angle conversion

  use sep_mod
  use utilities_mod
  use pctrist_mod
  use fftwflags


  implicit none  
  integer, parameter, private:: dbl=selected_int_kind(12)

  !!----------------------------------------------------------------
  !! FFT
  real,              private :: scaleF, scaleI
  integer(kind=dbl), private, dimension(:),pointer ::  planF,  planI

  complex, dimension(:,:,:,:), allocatable, private :: cf
  complex, dimension(:,:,:),       pointer, private :: sftF !! shared
  complex, dimension(:),           pointer, private :: sftI !! shared

  !!----------------------------------------------------------------
  !! angle conversion
  real,    dimension(:),   allocatable, private :: khi,kai,kzi
  complex, dimension(:,:), allocatable, private :: model, data
  real,    dimension(:,:), allocatable, private :: str
  real,    dimension(:,:), allocatable, private :: stretch

  real,    private :: eps
  logical, private :: push
  !!----------------------------------------------------------------

contains

  !----------------------------------------------------------------
  subroutine adcig_fft_init(nth,ni)
    integer, intent(in) :: nth
    integer, dimension(3), intent(in) :: ni
    integer :: stat,i,j
    scaleF = 1./sqrt(1.*product(ni))
    scaleI = 1./sqrt(1.*ni(1))

    allocate(cf(ni(1),ni(2),ni(3),nth), stat=stat)
    if(stat /=0) call seperr("cant allocate cf")




   allocate(planF(nth),planI(nth))
!    call fftwnd_f77_create_plan(planF,3,ni   ,fFTW_FORWARD  &
!    ,    fFTW_ESTIMATE + fFTW_THREADSAFE + fFTW_IN_PLACE)
!
!    call fftwnd_f77_create_plan(planI,1,(/ni(1)/),fFTW_BACKWARD &
!    ,    fFTW_ESTIMATE + fFTW_THREADSAFE + fFTW_IN_PLACE)

do i=1,nth
    call sfftw_plan_dft(planF(i),3,ni,cf(1,1,1,i),cf(1,1,1,i),fFTW_FORWARD  &
    ,    fFTW_ESTIMATE + fFTW_THREADSAFE )

    call sfftw_plan_dft(planI(i),1,(/ni(1)/),cf(1,1,1,i),cf(1,1,1,i),fFTW_BACKWARD &
    ,    fFTW_ESTIMATE + fFTW_THREADSAFE )
end do


  end subroutine adcig_fft_init
  !----------------------------------------------------------------
  subroutine adcig_F_fft(ith,isl,f)
    integer,           intent(in) :: ith
    integer                       :: i,j,k
    integer(kind=dbl), intent(in) :: isl
    complex, dimension(:,:,:,:) :: f

    cf(:,:,:,ith) = f(:,:,:,isl)
!    call fftwnd_f77_one(planF,cf(:,:,:,ith),0) !! Xform in place
    call sfftw_execute(planF(ith))

    f(:,:,:,isl) = cf(:,:,:,ith) * scaleF

  end subroutine adcig_F_fft
  !----------------------------------------------------------------
  subroutine adcig_I_fft(ith,isl,f)
    integer,           intent(in) :: ith
    integer(kind=dbl), intent(in) :: isl
    complex, dimension(:,:,:,:) :: f
    integer :: n1,n2,n3
    integer ::    i2,i3

    n2=size(f,2)
    n3=size(f,3)

!          cf(:,:,:,ith) = f(:,:,:,isl)
    do i2=1,n2
       do i3=1,n3
          cf(:,1,1,ith) = f(:,i2,i3,isl)
!         call fftwnd_f77_one(planI,cf(:,i2,i3,ith),0) !! Xform in place
          call sfftw_execute(planI(ith)) !! Xform in place
          f(:,i2,i3,isl) = cf(:,1,1,ith) * scaleI
       end do
    end do
!          f(:,:,:,isl) = cf(:,:,:,ith) * scaleI

  end subroutine adcig_I_fft
  !----------------------------------------------------------------
  subroutine adcig_fft_close()
    integer :: stat,i
!    call fftwnd_f77_destroy_plan(planF)
!    call fftwnd_f77_destroy_plan(planI)
    do i=1,size(cf,4)
      call sfftw_destroy_plan(planF(i))
      call sfftw_destroy_plan(planI(i))
    end do

    deallocate(cf,planF,planI,stat=stat)
    if(stat /=0) call seperr("cant deallocate cf")
  end subroutine adcig_fft_close
  !----------------------------------------------------------------
  subroutine adcig_shift_init(a1,a2,a3)
    type(paxis), intent(in):: a1,a2,a3

    integer             :: i1,i2,i3
    real                :: pi, argF, argI
    integer             :: stat

    allocate(sftF(a1%n,a2%n,a3%n), stat=stat)
    if(stat /=0) call seperr("cant allocate sftF")
    allocate(sftI(a1%n), stat=stat)
    if(stat /=0) call seperr("cant allocate sftI")

    sftF=cmplx(1.,0.)
    sftI=cmplx(1.,0.)

    if(a1%o/=0. .or. a2%o/=0. .or. a3%o/=0 ) then

       pi = acos(-1.)
       do i1=1,a1%n
          do i2=1,a2%n
             do i3=1,a3%n

                argF = 2*pi &
                * ( (i1-1.)/a1%n * a1%o/a1%d &
                +   (i2-1.)/a2%n * a2%o/a2%d &
                +   (i3-1.)/a3%n * a3%o/a3%d )

                argI = 2*pi &
                * ( (i1-1.)/a1%n * a1%o/a1%d )

                sftF(i1,i2,i3) = cmplx(cos(argF),-(+1)*sin(argF))
                sftI(i1      ) = cmplx(cos(argI),-(-1)*sin(argI))

             end do
          end do
       end do

    end if

  end subroutine adcig_shift_init
  !----------------------------------------------------------------
  subroutine adcig_F_shift(isl,f)
    integer(kind=dbl), intent(in) :: isl
    complex, dimension(:,:,:,:) :: f
    f(:,:,:,isl) = f(:,:,:,isl) * sftF
  end subroutine adcig_F_shift
  !----------------------------------------------------------------
  subroutine adcig_I_shift(isl,f)
    integer(kind=dbl), intent(in) :: isl
    complex, dimension(:,:,:,:) :: f
    integer :: n2,n3
    integer :: i2,i3

    n2=size(f,2)
    n3=size(f,3)
    do i2=1,n2
       do i3=1,n3
          f(:,i2,i3,isl) = f(:,i2,i3,isl) * sftI
       end do
    end do
  end subroutine adcig_I_shift
  !----------------------------------------------------------------
  subroutine adcig_shift_close()
    integer :: stat
    deallocate(sftI, stat=stat)
    if(stat /=0) call seperr("cant deallocate sftI")
    deallocate(sftF, stat=stat)
    if(stat /=0) call seperr("cant deallocate sftF")
  end subroutine adcig_shift_close
  !----------------------------------------------------------------  

  !----------------------------------------------------------------
  subroutine adcig_ang_init(nth,az,ah,aa,eps_in,push_in)
    integer,     intent(in) :: nth
    type(paxis), intent(in) :: az,ah,aa
    real,        intent(in) :: eps_in
    logical,     intent(in) :: push_in
    type(paxis)             :: akh
    integer :: iz,ih,ia
    real    :: kz,kh,ka
    real    :: pi
    integer :: stat

    push  = push_in
    eps   = eps_in

    pi = acos(-1.)

    allocate( data(nth,ah%n), stat=stat)
    if(stat /=0) call seperr("cant allocate data")
    allocate(model(nth,aa%n), stat=stat)
    if(stat /=0) call seperr("cant allocate model")
    allocate(  str(nth,ah%n), stat=stat)
    if(stat /=0) call seperr("cant allocate str")

    allocate(khi(ah%n), stat=stat)
    if(stat /=0) call seperr("cant allocate khi")
    allocate(kai(aa%n), stat=stat)
    if(stat /=0) call seperr("cant allocate kai")
    allocate(kzi(az%n), stat=stat)
    if(stat /=0) call seperr("cant allocate kzi")

    !! kz
    do iz = 1,az%n/2
       kzi(iz       ) = (        iz-1)
       kzi(iz+az%n/2) = (-az%n/2+iz-1)
    end do
    kzi = 2*pi* kzi / (az%n*az%d)

    !! ka
    do ia = 1,aa%n
       kai(ia) =  aa%o + (ia-1) * aa%d
    end do

    !! kh
    do ih = 1,ah%n
       khi(ih) = (-ah%n/2+ih-1)
    end do
    khi = 2*pi* khi / (ah%n*ah%d)
    !! akh
    akh%o = khi(1)
    akh%d = 2*pi / (ah%n*ah%d)
    akh%n = ah%n

    if(     push) then !! push
       allocate(stretch(az%n,ah%n), stat=stat)
       if(stat /=0) call seperr("cant allocate stretch")

       stretch=0.
       do iz=1,az%n
          kz = kzi(iz)
          if (kz/=0.) then
             do ih = 1,ah%n
                kh = khi(ih)
                ka = - 180* atan(kh/kz) /pi
                stretch(iz,ih) = ka
             end do
          else
             stretch(iz,:) = 90.
          end if
       end do
    else               !! pull
       allocate(stretch(az%n,aa%n), stat=stat)
       if(stat /=0) call seperr("cant allocate stretch")

       stretch=0.
       do iz=1,az%n
          kz = kzi(iz)
          do ia = 1,aa%n
             ka = pi* kai(ia) /180
             kh = - kz * tan(ka)
             stretch(iz,ia) = kh
          end do
       end do
    end if

    call pctrist_init(nth,akh,aa,push,eps)
  end subroutine adcig_ang_init
  !----------------------------------------------------------------
  subroutine adcig_ang_x(ith,isl,f,az,ahx,aax,ahy)
    integer,           intent(in) :: ith
    integer(kind=dbl), intent(in) :: isl
    type(paxis), intent(in) :: az,ahx,aax,ahy
    complex, dimension(:,:,:,:) :: f

    integer :: ihx,iax,ihy,iz
    real    :: khx,kax,    kz
    integer :: jhx

    jhx = ahx%n/2

    do iz=1,az%n
       str(ith,:) = stretch(iz,:)
       call pctrist_define(ith,str)

       do ihy = 1,ahy%n
          data(ith,1    :jhx    )=f(iz,1+jhx:jhx+jhx,ihy,isl)
          data(ith,1+jhx:jhx+jhx)=f(iz,1    :jhx    ,ihy,isl)

          call pctrist_apply(ith,model,data)

          f(iz,:,ihy,isl) = model(ith,:)

       end do
    end do

  end subroutine adcig_ang_x
  !----------------------------------------------------------------
  subroutine adcig_ang_y(ith,isl,f,az,ahy,aay,ahx)
    integer,           intent(in) :: ith
    integer(kind=dbl), intent(in) :: isl
    type(paxis), intent(in) :: az,ahy,aay,ahx
    complex, dimension(:,:,:,:) :: f

    integer :: ihy,iay,ihx,iz
    real    :: khy,kay,    kz
    integer :: jhy

    jhy = ahy%n/2

    do iz=1,az%n
       str(ith,:) = stretch(iz,:)
       call pctrist_define(ith,str)

       do ihx = 1,ahx%n
          data(ith,1    :jhy    )=f(iz,ihx,1+jhy:jhy+jhy,isl)
          data(ith,1+jhy:jhy+jhy)=f(iz,ihx,1    :jhy    ,isl)

          call pctrist_apply(ith,model,data)

          f(iz,ihx,:,isl) = model(ith,:)

       end do
    end do

  end subroutine adcig_ang_y
  !----------------------------------------------------------------  
  subroutine adcig_ang_close()
    integer :: stat
    call pctrist_close()

    deallocate(khi, stat=stat)
    if(stat /=0) call seperr("cant deallocate khi")
    deallocate(kzi, stat=stat)
    if(stat /=0) call seperr("cant deallocate kzi")
    deallocate(kai, stat=stat)
    if(stat /=0) call seperr("cant deallocate kai")

    deallocate(data, stat=stat)
    if(stat /=0) call seperr("cant deallocate data")
    deallocate(model, stat=stat)
    if(stat /=0) call seperr("cant deallocate model")
    deallocate(str, stat=stat)
    if(stat /=0) call seperr("cant deallocate str")
    deallocate(stretch, stat=stat)
    if(stat /=0) call seperr("cant deallocate stretch")

  end subroutine adcig_ang_close
  !----------------------------------------------------------------
end module adcig_mod
