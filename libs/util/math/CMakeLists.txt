#cmake_minimum_required(VERSION 2.8)

#obb.cpp
set (SOURCES cluster.c sqroot.c obb.cpp)

if(CMAKE_Fortran_COMPILER)
set(SOURCES ${SOURCES} pctrist.f90   rand.f90   vtris.f90 ptridiag.f90  rand_mod.f90
quant.f90 rand01.f90    subfslan.f90)

endif(CMAKE_Fortran_COMPILER)



set(CMAKE_MACOSX_RPATH 1)
add_library(sepmath ${SOURCES})
target_link_libraries( sepmath sepaux sep m)

##target_include_directories(sepmath
#
#	PUBLIC
#	   $<INSTALL_INTERFACE:include> 
#	   $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
#	   )
install(TARGETS sepmath DESTINATION lib EXPORT  SEPlibTargets)


