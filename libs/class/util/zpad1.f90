! Zero pad.  Surround data by zeros. 1-D
!
subroutine zpad1( adj,add,  data,nd,  padd,np )
integer           adj,add,    d, nd,    p, np
real                        data(nd), padd(np)
call adjnull(     adj,add,  data,nd,  padd,np)
do d= 1, nd  
  p = d + (np-nd)/2
  if ( adj .eq. 0 ) then
    padd(p) = padd(p) + data(d)
  else
    data(d) = data(d) + padd(p)
  end if
end do 
return
end  
