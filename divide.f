      program main readlist
      implicit none

      include 'fdvsg3d_dc.par'
      
      character*80 modifiedfilename
      
      integer alldone, order
      integer numuserhd
      integer ndims, dims(3), nn, ii, jj, kk, ll, px, py, pz
      integer ixlo, ixhi, iylo, iyhi, izlo, izhi
      integer nxtotal, nytotal, nztotal
      double precision xshift, yshift, zshift
      character*80 rootfile, newroot 
      character*80 userhead(MAXUSRHD)
      
c...  get namelist input
      namelist /in0/jobid,
     $     fpeak,xlambda,
     $     nx,ny,nz,nt,dxmin,dxmax,
     $     dymin,dymax,dz,dt,
     $     nrec,ixrec,iyrec,izrec,
     $     nstep,nout,outfile,
     $     ixsrc,iysrc,izsrc,isrctype,imode,
     $     nblks,nmats,vp,vs,rho,ijllur,iprntmap,
     $     snap3d,snap2dx,snap2dy,snap2dz,
     $     ixsnap,iysnap,izsnap,
     $     vxsnap3d,vysnap3d,vzsnap3d,
     $     txxsnap3d,tzzsnap3d,tyysnap3d,
     $     txysnap3d,txzsnap3d,tyzsnap3d,
     $     presnap3d,
     $     vxsnap2dx,vysnap2dx,vzsnap2dx,
     $     txxsnap2dx,tzzsnap2dx,tyysnap2dx,
     $     txysnap2dx,txzsnap2dx,tyzsnap2dx,
     $     presnap2dx,
     $     vxsnap2dy,vysnap2dy,vzsnap2dy,
     $     txxsnap2dy,tzzsnap2dy,tyysnap2dy,
     $     txysnap2dy,txzsnap2dy,tyzsnap2dy,
     $     presnap2dy,
     $     vxsnap2dz,vysnap2dz,vzsnap2dz,
     $     txxsnap2dz,tzzsnap2dz,tyysnap2dz,
     $     txysnap2dz,txzsnap2dz,tyzsnap2dz,
     $     presnap2dz, 
     $     tplot0,tplot1,alldone
      
      namelist /in1/ ndims, dims, order
      
      write(*,*) "Enter the root file name:"
      read(*,*)  rootfile
      
      
c...  Seting the dimensions of the cartesian topology and its extent
      
      write(*,*) "Enter the process distribution"
      write(*,*) "px="
      read(*,*) dims(1)
      write(*,*) "py="
      read(*,*) dims(2)
      write(*,*) "pz="
      read(*,*) dims(3)

      ndims = 3
      order = 4

      open(unit=42, file="pll.dat", status='unknown')
      write(42, in1)
      close(42)

      px = dims(1)
      py = dims(2)
      pz = dims(3)
      
      open(84,file="recv.dat",status='unknown')
      write(84,*) px, py, pz

      write(*,*) "Dividing the domain as ", px, "* ", py, "* ", pz
      
      
c...  Read the global data from the root file
      
      open(unit=1, file='i'// rootfile, status='old')
      
c...  Read beginning comment lines
      read (1,*) numusrhd
      if (numusrhd .gt. MAXUSRHD) then
         write (*,*)'The maximum number of user header lines is ',
     $        MAXUSRHD,'.'
         stop
      endif
      
      do ii=1,numusrhd
         read(1,'(a)') userhead(ii)
         write(*,'(a)') userhead(ii)
      end do
      
      call fdvsg3d_paramset
      read (1, in0)
      close(1)
      
      nxtotal = nx
      nytotal = ny
      nztotal = nz
      
c...  Do i need to read other files also??????
c...  If yes then read them as well (like dx//root file)
      
      if ( dxmin .ne. dxmax ) then
         open(79, file = 'dx'// rootfile, status='old')
         do ll = 1, nxtotal-1
            read(79,*) dx(ll)
         end do
         close(79)
      end if

      if ( dymin .ne. dymax ) then
         open(79, file = 'dy'// rootfile, status='old')
         do ll = 1, nytotal-1
            read(79,*) dy(ll)
         end do
         close(79)
      end if

      if(imode .eq. 2) then
         kfile='map'// rootfile
         open(unit=50,file=kfile,status='old')
      endif
     
 
c...  Convert the global data into local data
c...  pertaining to the sub-domain  (ii, jj, kk)
c...  Also write down the partitioing data in part.dat
      open(42,file="part.dat",status="unknown")
      write(42,*) px, py, pz
      
      do  ii = 0, px-1
         do jj = 0, py-1
            do  kk = 0, pz-1
               newroot =  modifiedfilename(rootfile, ii, jj, kk)

               call MyBasicDomain(ii, jj, kk, nx, ny, nz, px, py, pz, 
     $              ixlo, ixhi, iylo, iyhi, izlo, izhi)
            
            
               call MyReceivers(nrec, ixrec, iyrec, izrec,
     $              ixlo, ixhi, iylo, iyhi, izlo, izhi)
            
            
               call MyComputationalDomain(ii, jj, kk, nx, ny, nz, 
     $              nxtotal, nytotal, nztotal,
     $              ixlo, ixhi, iylo, iyhi, izlo, izhi)
            
               call MySource(ixsrc, iysrc, izsrc, 
     $              ixlo, ixhi, iylo, iyhi, izlo, izhi)
               
               
               call AddHalo(ii, jj, kk, nx, ny, nz, 
     $              nxtotal, nytotal, nztotal, 
     $              ixlo, ixhi, iylo, iyhi, izlo, izhi, order)
               

               call MyMaterials(ixlo, ixhi, iylo, iyhi, izlo, izhi,
     $              nxtotal, nytotal, nztotal, rootfile, newroot)
               
               call MyShift(ixlo, ixhi, iylo, iyhi, izlo, izhi, 
     $              xshift, yshift, zshift)
               
               write(*,*) "(",ii, jj, kk, ")",
     $              " [", ixlo, ixhi,
     $              " ]*[", iylo, iyhi,
     $              " ]*[", izlo, izhi,
     $              "] src=[", ixsrc, iysrc, izsrc,
     $              "] nr=",nrec, " xr=[", ixrec(1), ixrec(2),
     $              "]  yr=[", iyrec(1), iyrec(2),"]", 
     $              "]  zr=[", izrec(1), izrec(2),"]" 
               write(42,*) ii, jj, kk, 
     $              ixlo, ixhi, iylo, iyhi, izlo, izhi, 
     $              xshift, yshift, zshift

c..   converting from the global to local coordinates
c..   right now they are in the indices of original domain             
               if (nrec .ne. 0) then
                  ixrec(1) = ixrec(1) - ixlo + 1 
                  ixrec(2) = ixrec(2) - ixlo + 1
                  iyrec(1) = iyrec(1) - iylo + 1 
                  iyrec(2) = iyrec(2) - iylo + 1
                  izrec(1) = izrec(1) - izlo + 1
                  izrec(2) = izrec(2) - izlo + 1
               end if
               
               if (ixsrc .ne. -1 .and. iysrc .ne. -1 
     $              .and. izsrc .ne. -1) then
                  ixsrc = ixsrc - ixlo + 1
                  iysrc = iysrc - iylo + 1
                  izsrc = izsrc - izlo + 1
               end if
               
               
               write(*,*) "(",ii, jj, kk, ")",
     $              " [", 1, ixhi - ixlo + 1,
     $              " ]*[", 1, iyhi - iylo + 1,   
     $              " ]*[", 1, izhi - izlo + 1,
     $              "] src=[", ixsrc, iysrc, izsrc,
     $              "] nr=",nrec, " xr=[", ixrec(1), ixrec(2),
     $              "]  yr=[", iyrec(1), iyrec(2),"]", 
     $              "]  zr=[", izrec(1), izrec(2),"]" 
               
c...  Start writing to the file first to input file then to dx file
               open(unit=1, file= 'i' // newroot, status='unknown')
               
               write(1,*) numusrhd
               
               do nn=1,numusrhd
                  write(1,*) userhead(nn)
               end do
               
               write(1, in0) 
               close(1)
            
               if(dxmin .ne. dxmax) then
                  open(unit=2, file= 'dx'// newroot, status='unknown')
                  do ll = ixlo, ixhi-1
                     write(2,900) dx(ll)
 900                 format(E16.8)
                  end do
                  close(2)
               end if
               
               if(dymin .ne. dymax) then
                  open(unit=2, file= 'dy'// newroot, status='unknown')
                  do ll = iylo, iyhi-1
                     write(2,900) dy(ll)
 990                 format(E16.8)
                  end do
                  close(2)
               end if
            
            
c...  Read the global data afresh from the root file
               open(unit=1, file= 'i' // rootfile, status='old')
               call fdvsg3d_paramset
               read (1, in0)
               close(1)
               
            end do
         end do
      end do
      
      close(42)
      close(50)
      
      end 
      

c===============================================================
c      Calculates the shift in terms of the co-ordinates
c===============================================================
      subroutine MyShift(ixlo, ixhi, iylo, iyhi, izlo, izhi, 
     $     xshift, yshift, zshift)

      implicit none
      include 'fdvsg3d_dc.par'

      integer ixlo, ixhi, iylo, iyhi, izlo, izhi
      double precision xshift, yshift, zshift
    
      integer ii, jj, kk

      if(dxmin .ne. dxmax) then
         xshift = 0
         do ii = 1, ixlo-1
            xshift = xshift + dx(ii)
         end do
      else
         xshift = 0
         do ii = 1, ixlo-1
            xshift = xshift + dxmin
         end do
      end if
      
      if(dymin .ne. dymax) then
         yshift = 0
         do jj = 1, iylo-1
            yshift = yshift + dy(jj)
         end do
      else
         yshift = 0
         do jj = 1, iylo-1
            yshift = yshift + dymin
         end do
      end if

      zshift = 0
      do kk = 1, izlo-1
         zshift = zshift + dz
      end do

      end 

c===============================================================
c     Expand the domain to include the halo cells
c===============================================================
      
      subroutine AddHalo(ii, jj, kk, nx, ny, nz, 
     $     nxtotal, nytotal, nztotal, 
     $     ixlo, ixhi, iylo, iyhi, izlo, izhi, order)
      
      implicit none
      
c     Declaring the function arguments
      integer ii, jj, kk, nx, ny, nz, nxtotal, nytotal, nztotal
      integer ixlo, ixhi, iylo, iyhi, izlo, izhi, order
      
      
      if ( ixlo .ne. 1 ) then
         ixlo = ixlo - (order / 2)
      end if
      
      if ( ixhi .ne. nxtotal ) then
         ixhi = ixhi + (order / 2)
      end if

      if ( iylo .ne. 1 ) then
         iylo = iylo - (order / 2)
      end if
      
      if ( iyhi .ne. nytotal ) then
         iyhi = iyhi + (order / 2)
      end if
      
      if ( izlo .ne. 1 ) then
         izlo = izlo - (order / 2)
      end if
      
      if ( izhi .ne.  nztotal ) then
         izhi = izhi + (order / 2)
      end if

      nx = ixhi - ixlo + 1
      ny = iyhi - iylo + 1
      nz = izhi - izlo + 1
      
      end 

c===========================================================
c Decides which all receivers belong to my domain
c===========================================================
      subroutine MyReceivers(nrec, ixrec, iyrec, izrec, 
     $     ixlo, ixhi, iylo, iyhi, izlo, izhi)
      
      implicit none
      
c     Declaring the function arguments
      integer nrec, ixrec(2), iyrec(2), izrec(2)
      integer ixlo, ixhi, iylo, iyhi, izlo, izhi

c     Declaring the local variables
      integer ixbegin, ixend, iybegin, iyend, izbegin, izend
      integer ixdiff, iydiff, izdiff
      integer ix, iy, iz, n
      integer ibegin, iend
      logical status

c------------------------------------------------------------------
c... Analyzing for the special case of just one reciever
c------------------------------------------------------------------
      if (nrec .eq. 1) then
         call inmydomain(ixrec(1), iyrec(1), izrec(1), 
     $        ixlo, ixhi, iylo, iyhi, izlo, izhi, 
     $        status)
         
         if(status .eqv. .false.) then 
            nrec = 0
            ixrec(1) = -1
            ixrec(2) = -1
            iyrec(1) = -1
            iyrec(2) = -1
            izrec(1) = -1
            izrec(2) = -1
            write(84,*) 0,0,0
         else
            write(84,*) 1,1,1
         end if
      else
c------------------------------------------------------------------
c     Analyzing the case when there are a whole set of recievres 
c -----------------------------------------------------------------        
         ixdiff = ( ixrec(2) - ixrec(1) ) / (nrec - 1)
         iydiff = ( iyrec(2) - iyrec(1) ) / (nrec - 1)
         izdiff = ( izrec(2) - izrec(1) ) / (nrec - 1)
         
         ibegin  = 0
         iend    = 0
         
c...  Checking which all receivers are there in my domain

         do n = 1, nrec + 1
            ix = ixrec(1) + ixdiff * (n - 1) 
            iy = iyrec(1) + iydiff * (n - 1) 
            iz = izrec(1) + izdiff * (n - 1)
            
            call inmydomain(ix, iy, iz, 
     $           ixlo, ixhi, iylo, iyhi, izlo, izhi, 
     $           status)
            
            if ( status .eqv. .true.) then
               if ( ibegin .eq. 0 ) then
                  ibegin = n
               end if
            else
               if (ibegin .ne. 0 ) then
                  if (iend .eq. 0) then
                     iend = n - 1
                  end if
               end if
            end if
            
         end do
         
        if(ibegin .ne. 0) then
           if(iend .eq. 0) then
              iend = nrec
           end if
        end if
        
c...  Once decided decide the number of recievers in this domain
c...  and their coordinates (as expressed by the endpoints of line 
c...              joining them)
         ix = ixrec(1)
         iy = iyrec(1)
         iz = izrec(1)
         
         if (ibegin .ne. 0) then
            write(*,*) nrec, ibegin, iend, ixdiff, iydiff, izdiff
            nrec = iend - ibegin + 1
            ixrec(1) = ix + ixdiff * (ibegin - 1)
            ixrec(2) = ix + ixdiff * (iend - 1)
            iyrec(1) = iy + iydiff * (ibegin - 1)
            iyrec(2) = iy + iydiff * (iend - 1)
            izrec(1) = iz + izdiff * (ibegin - 1)
            izrec(2) = iz + izdiff * (iend - 1)
            write(84,*) ibegin, iend, nrec
         else
            nrec = 0
            ixrec(1) = -1
            ixrec(2) = -1
            iyrec(1) = -1
            iyrec(2) = -1
            izrec(1) = -1
            izrec(2) = -1
            write(84,*) 0, 0, 0
         end if
         
      end if
      
      end
      
c===========================================================
c         Decides which sources shall be in my domain 
c============================================================

      subroutine MySource(ixsrc, iysrc, izsrc, 
     $     ixlo, ixhi, iylo, iyhi, izlo, izhi)
      
      implicit none 
      
c     Declaring the function arguments      
      integer ixsrc, iysrc, izsrc, ixlo, ixhi, iylo, iyhi, izlo, izhi
      logical status
      
      call inmydomain(ixsrc, iysrc, izsrc, 
     $     ixlo, ixhi, iylo, iyhi, izlo, izhi, status)  
      
      if (status .eqv. .false.) then
         ixsrc = -1
         iysrc = -1
         izsrc = -1
      end if
      
      end
      
      
c================================================================
c     Decides if a given point is in the given square domain
c================================================================
      subroutine inmydomain(x, y, z, 
     $     ixlo, ixhi, iylo, iyhi, izlo, izhi, 
     $     status)
      
      implicit none
      
c     Declaring the function arguments
      integer x, y, z, ixlo, ixhi, iylo, iyhi, izlo, izhi
      
c     Declaring the local variables
      logical status
      
      status = .false.
      
      if ( ixlo .le. x .and. x .le. ixhi .and. 
     $     iylo .le. y .and. y .le. iyhi .and. 
     $     izlo .le. z .and. z .le. izhi ) then
         status = .true.
      end if
      
      end



c=============================================================
c Decides what shall be the basic domain of proc ii,jj,kk
c=============================================================
      subroutine MyBasicDomain(ii, jj, kk, nx, ny, nz, px, py, pz, 
     $     ixlo, ixhi, iylo, iyhi, izlo, izhi)
      
      implicit none
      
c...  Declaring the function arguments
      integer ii, jj, kk, nx, ny, nz, px, py, pz
      integer ixlo, ixhi, iylo, iyhi, izlo, izhi
      
c...  Declaring the local variables
      integer rx, ry, rz
      integer qx, qy, qz
      
      
c...  Calculate a non-overlapping domain
      rx = mod(nx, px)
      qx = nx / px
      
      ry = mod(ny, py)
      qy = ny / py

      rz = mod(nz, pz)
      qz = nz / pz
      
      
      if (ii .gt. (rx - 1) )   then
         ixlo = 1 + (qx + 1 ) * rx + qx * (ii - rx)
         ixhi = ixlo + qx - 1
      else
         ixlo = 1 + (qx + 1) * ii
         ixhi = ixlo + qx 
      end if
      
      if (jj .gt. (ry - 1) )   then
         iylo = 1 + (qy + 1 ) * ry + qy * (jj - ry)
         iyhi = iylo + qy - 1
      else
         iylo = 1 + (qy + 1) * jj
         iyhi = iylo + qy 
      end if

      
      if (kk .gt. (rz - 1)) then 
         izlo = 1 + (qz + 1 ) * rz + qz * (kk - rz)
         izhi = izlo + qz - 1
      else
         izlo = 1 + (qz + 1 ) * kk
         izhi = izlo + qz
      end if
      
      
      
c...  Calculate the total number of grid points allocated to you in each
c...           of the two coordiante directions
      nx = ixhi - ixlo + 1
      ny = iyhi - iylo + 1
      nz = izhi - izlo + 1
      
      end


c=============================================================
c Decides what shall be the computational domain of proc ii,kk
c=============================================================
      subroutine MyComputationalDomain(ii, jj, kk, nx, ny, nz, 
     $     px, py, pz, 
     $     ixlo, ixhi, iylo, iyhi, izlo, izhi)
      
      implicit none

c...  Declaring the function arguments
      integer ii, jj, kk, nx, ny, nz, px, py, pz
      integer ixlo, ixhi, iylo, iyhi, izlo, izhi

c... Make the above non-overlapping domain a overlapping one as
c... the grid we are dealing with is staggered in both directions
      
      if(ixlo .ne. 1) then
         ixlo = ixlo - 1
      end if
      
      if(iylo .ne. 1) then
         iylo = iylo - 1
      end if

      if(izlo .ne. 1) then
         izlo = izlo - 1
      end if
      
c...  Calculate the total number of grid points allocated to you in each
c...  of the two coordiante directions
      nx = ixhi - ixlo + 1
      ny = iyhi - iylo + 1
      nz = izhi - izlo + 1
      
      end
      

c ======================================================================
c	paramset
c	Sets initial values of some parameters
c ======================================================================

	subroutine fdvsg3d_paramset

	include 'fdvsg3d_dc.par'
	integer alldone

	jobid = 0

        fpeak=0.	
        xlambda= 0

	nx=-1
        ny=-1
        nz=-1
        nt=-1
        dz=-1.
        dxmin=-1.
        dxmax=-1.
        dymin=-1.
        dymax=-1.
        dt=-1.

	nstep=1

	isrctype=0
        ixsrc=-1
        iysrc=-1
 	izsrc=-1

	nrec= -1
	do 2 ii=1,MAXRCVRS
	   ixrec(ii)=-1
           iyrec(ii)=-1
       	   izrec(ii)=-1
2       continue

        iprntmap=0

        nout=1
	outfile(1)='txx'

	imode=1
        nblks=1
        nmats=1
	do 6 ii=1,MAXBLCKS
          do 5 i=1,6
	     ijllur(i,ii)=-1
5	  continue
          ijllur(7,ii)=ii
	  vp(ii)=-1.
	  vs(ii)=-1.
          rho(ii)=-1.
6       continue

	tplot0=-1.
	tplot1=-1.
        snap3d='n'
        snap2dx='n'
        snap2dy='n'
        snap2dz='n'
        
	vxsnap3d='n'
        vysnap3d='n'
	vzsnap3d='n'
	txxsnap3d='n'
        tyysnap3d='n'
	tzzsnap3d='n'
        txysnap3d='n'
	txzsnap3d='n'
        tyzsnap3d='n'
        presnap3d='n'

        vxsnap2dx='n'
        vysnap2dx='n'
        vzsnap2dx='n'
        txxsnap2dx='n'
        tyysnap2dx='n'
        tzzsnap2dx='n'
        txysnap2dx='n'
        txzsnap2dx='n'
        tyzsnap2dx='n'
        presnap2dx='n'

        vxsnap2dy='n'
        vysnap2dy='n'
        vzsnap2dy='n'
        txxsnap2dy='n'
        tyysnap2dy='n'
        tzzsnap2dy='n'
        txysnap2dy='n'
        txzsnap2dy='n'
        tyzsnap2dy='n'
        presnap2dy='n'

        vxsnap2dz='n'
        vysnap2dz='n'
        vzsnap2dz='n'
        txxsnap2dz='n'
        tyysnap2dz='n'
        tzzsnap2dz='n'
        txysnap2dz='n'
        txzsnap2dz='n'
        tyzsnap2dz='n'
        presnap2dz='n'


	do 8 ii=1,NSNAPMAX
 	   mtsnap(ii)=0
8       continue
	alldone=0

	return
      end


c==================================================================
c  Decides which materials are present in a particular subdomain
c==================================================================
      subroutine MyMaterials(ixlo, ixhi, iylo, iyhi, izlo, izhi,
     $     nxtotal, nytotal, nztotal, rootfile, newroot)

      implicit none 
      include 'fdvsg3d_dc.par'
      
c..   Declaring the calling variables
      integer ixlo, ixhi, iylo, iyhi, izlo, izhi
      integer nxtotal, nytotal, nztotal
      character*40 rootfile
      character*40 newroot

c..   Declaring the local variables
      integer im, idx, i, j, k
      integer ktmp(MAXIJK)
      character*80 kfilel

c...  ---------------------------------------------------
c...  if you have been provided  material map as a file
c...  ---------------------------------------------------
      
      if(imode .eq. 2) then
c...  open a file for local material map 
         kfilel='map'// newroot
         open(unit=51,file=kfilel,status='unknown')

         do k=1, nztotal
            do  j=1, nytotal
               read(50,*)(ktmp(i), i=1,nxtotal)
               do i=1,nxtotal
                  imat2d(i,j)=ktmp(i)
               end do
            end do

            if (k .ge. izlo .and. k .le. izhi) then
               do  j = iylo, iyhi
                  do i = ixlo, ixhi
                     ktmp(i) = imat2d(i,j)
                  end do
c...   writing to the file for the local material map of one slice of the model 
                  write(51,*)(ktmp(i), i=ixlo,ixhi)
               enddo
            endif

         end do
         rewind(50)
          
c...  ----------------------------------------------------
c...  In case you have been given material map as blocks
c...  -----------------------------------------------------
      else if (imode .eq. 1) then
      
         do  im = 1, nblks
            
c..   Set the material index equal to zero         
            do k = 1, nztotal
               do j = 1, nytotal
                  do i= 1, nxtotal
                     imat(i, j, k) = 0
                  end do
               end do
            end do
            
c..   Map this material's block  on the material grid
            do k = ijllur(3,im), ijllur(6,im)
               do  j = ijllur(2,im), ijllur(5,im)
                  do  i = ijllur(1,im), ijllur(4,im)
                     imat(i,j,k) = ijllur(7,im)
                  end do
               end do
            end do
            
c..   Set the global coordinates as invalid numbers
            do idx=1, 6
               ijllur(idx, im) = -1
            end do
            
c..   Start scanning from the lower-coordinate end of this domain    
            do  k = izlo, izhi
               do  j = iylo, iyhi
                  do  i = ixlo, ixhi
                     if(  imat(i,j,k) .eq. ijllur(7,im) .and.
     $                    ijllur(1,im) .eq. -1 .and. 
     $                    ijllur(2,im) .eq. -1 .and. 
     $                    ijllur(3,im) .eq. -1) then
                        ijllur(1,im) = i - ixlo + 1
                        ijllur(2,im) = j - iylo + 1
                        ijllur(3,im) = k - izlo + 1
                     end if
                  end do
               end do
            end do
            
c..   Start scanning from the upper-coordinate end of this domain
            do  k = izhi, izlo, -1
               do  j = iyhi, iylo, -1
                  do  i = ixhi, ixlo, -1
                     if(  imat(i,j,k) .eq. ijllur(7,im) .and.
     $                    ijllur(4,im) .eq. -1 .and. 
     $                    ijllur(5,im) .eq. -1 .and.
     $                    ijllur(6,im) .eq. -1) then
                        ijllur(4,im) = i - ixlo + 1
                        ijllur(5,im) = j - iylo + 1
                        ijllur(6,im) = k - izlo + 1
                     end if
                  end do
               end do
            end do
            
         end do
      end if
      end




c==============================================================
c   This function appends to the end of the given file name
c    two integers ii and kk. So if filename="root" the output
c       would be root.1.4.2 (assuming ii = 1 jj = 4 and kk = 2
c===============================================================

      character*80 function modifiedfilename(oldname, ii, jj, kk)

      implicit none

c...  declare calling arguments
      character*80 newname
      character*30 oldname
      integer ii, jj, kk, cc, dd
      integer lastnonblank

c...  declare local arguents
      integer lnblnk
      character*80 tempname
      character*15 x
      character*15 y
      character*15 z

      write(x,*) ii
      write(y,*) jj
      write(z,*) kk
      write(tempname,*) oldname //'.'// x // '.' // y  // '.' // z
      lastnonblank = lnblnk(tempname)
      dd = 1

      do cc = 1, lastnonblank
         if ( tempname(cc:cc) .ne. ' ' ) then
            newname(dd:dd) = tempname(cc:cc)
            dd = dd + 1
         endif
      end do

      newname(dd:) = ''

      modifiedfilename = newname

      return

      end

