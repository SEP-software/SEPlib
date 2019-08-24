#cmake_minimum_required(VERSION 2.8)

set (SOURCES 
setvali.c  setvalf.c)

if(CMAKE_Fortran_COMPILER)
set(SOURCES ${SOURCES}  adjnull77.f90  ipow.f90   sep_vector.f90  
copy77.f90     inv.f90      scale.f90        sqrt.f90)
endif(CMAKE_Fortran_COMPILER)




set(CMAKE_MACOSX_RPATH 1)

add_library(sepvectorOps ${SOURCES})
target_link_libraries( sepvectorOps sep3d)

#target_include_directories(sepvector
#
#	PUBLIC
#	   $<INSTALL_INTERFACE:include> 
#	   $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
#	   )
install(TARGETS sepvectorOps DESTINATION lib EXPORT  SEPlibTargets)
