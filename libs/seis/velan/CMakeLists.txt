cmake_minimum_required(VERSION 2.8)

set (SOURCES 
hypint.f90  nmo_subs.f90    rms2int.f90    velansub.f90  vint2rms.f90
hypsum.f90  nmo_varoff.f90  vconvsubs.f90  velsimp.f90)



set(CMAKE_MACOSX_RPATH 1)

add_library(sepvelan ${SOURCES})
target_link_libraries( sepvelan sepfilter sepmath sep3d)

target_include_directories(sepvelan
	PRIVATE          
	   ${CMAKE_CURRENT_SOURCE_DIR}/../../include 
	PUBLIC
#	   $<INSTALL_INTERFACE:include> 
	   $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>  
      )
install(TARGETS sepvelan DESTINATION lib EXPORT  SEPlibTargets)
