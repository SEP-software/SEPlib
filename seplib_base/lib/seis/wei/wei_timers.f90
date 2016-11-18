module wei_timers_mod
implicit none
  character(len=128),pointer :: timers_name(:)
integer, private, save :: nsetup

interface  timer_start
module  procedure starti,startc
end interface

interface  timer_stop
module  procedure stopi,stopc
end interface



contains


logical function init_wei_timers(nmax   )
integer, optional :: nmax
integer :: ntimer
logical :: junkl



init_wei_timers=.true.  
end function


integer function find_timer_num(name)
character(len=*) :: name
integer :: i,n

find_timer_num=1

end function



logical function stopi(inum)
logical :: junkt
integer :: inum

stopi=.false.
stopi=.true.
end function

logical function stopc(name)
logical :: junkt
character(len=*) :: name
integer :: inum

stopc=.false.
stopc=.true.
end function

logical function startc(name,num)
logical :: junkt
character(len=*) :: name
integer, optional :: num
integer :: inum

startc=.false.
if(present(num))num=inum
startc=.true.
end function




logical function starti(inum,name)
integer :: inum
logical :: junkt
character(len=*),optional :: name
character(len=256) :: use

starti=.false.
starti=.true.
end function




end module
