cmake_minimum_required(VERSION 2.8)

set(CMAKE_MACOSX_RPATH 1)

set (SOURCES 
energysubs.c     sinc.c	)

if(CMAKE_Fortran_COMPILER)
set(SOURCES ${SOURCES} boxconv77.f90  icaf377.f90             tcai377.f90
boxmo.f90      icai177.f90     sinc_interp.f90  triangle277.f90
burg.f90       halfdifa.f90  icai277.f90     tcaf177.f90      triangle77.f90
causint2.f90   halfint.f90   icai377.f90     tcaf277.f90      tri_smooth_mod.f90
causint77.f90  icaf177.f90   
#nfilts_io.f90  
 tcai177.f90
cos_taper.f90  icaf277.f90   sep_filter.f90  tcai277.f90)
endif(CMAKE_Fortran_COMPILER)



add_library(sepfilter ${SOURCES})
target_link_libraries( sepfilter sepgeef90 sepclassutil superset )

target_include_directories(sepfilter
	PRIVATE          
	   ${CMAKE_CURRENT_SOURCE_DIR}/../../include 
	PUBLIC
	   $<INSTALL_INTERFACE:include> 
	   $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}/../>
	   $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>  
      )
install(TARGETS sepfilter DESTINATION lib EXPORT  SEPlibTargets)
