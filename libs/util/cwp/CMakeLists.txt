cmake_minimum_required(VERSION 2.8)

set (SOURCES 
cubicspline.c  ealloc.c     intcub.c  sep_cwp.f90  xdrbhdrsub.c  xindex.c
cwp_alloc.c      pfafft.c  valpkge.c    xdrhdrsub.c)




set(CMAKE_MACOSX_RPATH 1)
add_library(sepcwp ${SOURCES})
#target_include_directories(sepcwp
##
#	PUBLIC
#	   $<INSTALL_INTERFACE:include> 
#	   $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
#	   )
#
target_link_libraries(sepcwp sep3d sep)
install(TARGETS sepcwp DESTINATION lib   EXPORT  SEPlibTargets)

