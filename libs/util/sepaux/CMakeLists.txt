#cmake_minimum_required(VERSION 2.8)

set (SOURCES 
arrayreadf.c	           pad.c		      sgainpar.c
arrayreadi.c	        parcat.c		      
    patch_oc.c	     
cent.c		          pqueue.c	
compare.c	      loop_calc.c        time_window.c
	      multihdr.c       
)


set(CMAKE_MACOSX_RPATH 1)
if(CMAKE_Fortran_COMPILER)
set(SOURCES ${SOURCES}
	      #interp2.f90 
      interpolate.f90        sorting.f90
aux_string_mod.f90    isamax.f90            sort_subs.f90
iter_mod.f90     pqueue.c		      subrslan.f90
sep_aux.f90	      utilities.f90
helixcartmod_big.f90  pad2.f90	       septimers.f90
)
endif(CMAKE_Fortran_COMPILER)




add_library(sepaux ${SOURCES})
target_link_libraries( sepaux   superset sep)

#target_include_directories(sepaux
#
#	PUBLIC
#	   $<INSTALL_INTERFACE:include> 
#	   $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
#	   )
install(TARGETS sepaux DESTINATION lib EXPORT  SEPlibTargets)
