
subroutine synmarine ( data, nt,nh,ny, nz)
integer                      nt,nh,ny, nz,    it,ih,iy,is,iz, ns,&
  & iseed
real         data( nt,nh,ny),       layer, rand01
real                          refl(nz,ny), depth(nz)
iseed= 1992
ns = ny
do iz= 1, nz  
! 0 < rand01() < 1
  depth( iz) =  nt * rand01(iseed)        ! Reflector depth
  layer      =  2. * rand01(iseed) - 1.   ! Reflector strength
  do iy= 1, ny  
! Impose texture on layer
    refl(iz,iy) = layer * (1. + rand01(iseed))
  end do
end do 
call null(             data, nt*nh*ny)          ! erase data space
do is= 1, ns     
! shots
  do ih= 1, nh     
! down cable h = (g-s)/2
    do iz= 1, nz     
! Add hyperbola for each layer
      iy = (ns-is)+(ih-1)                     ! y = midpoint
      iy = 1 + (iy-ny*(iy/ny))                
      ! periodic with midpoint
      it = 1 + sqrt( depth(iz)**2 + 25.*(ih-1)**2 )   
      if ( it <= nt) then
        data(it,ih,is) = data(it,ih,is) + refl(iz,iy)
      end if
    end do
  end do
end do 
return
end  
