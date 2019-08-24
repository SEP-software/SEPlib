#cmake_minimum_required(VERSION 2.8)

set (SOURCES 
lock.c  pass_mpi.c   split.c)

if(CMAKE_Fortran_COMPILER)
set(SOURCES ${SOURCES} sep_param.f90)
endif(CMAKE_Fortran_COMPILER)



set(CMAKE_MACOSX_RPATH 1)
add_library(seppar ${SOURCES})
target_link_libraries( seppar  sep)
#target_include_directories(seppar
#
#	PUBLIC
#	   $<INSTALL_INTERFACE:include> 
#	   $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
#	   )
install(TARGETS seppar DESTINATION lib EXPORT  SEPlibTargets)
