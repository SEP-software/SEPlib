cmake_minimum_required(VERSION 3.4)

set(CMAKE_MACOSX_RPATH 1)


set (SOURCES 
data.f90		image.f90	 slow.f90
extrapolation.f90	kernal.f90	 wave.f90
extrapolation_type.f90	rtm_section.f90  wavelet_mod.f90)



set(CMAKE_MACOSX_RPATH 1)
add_library(sepmodel ${SOURCES})
target_link_libraries( sepmodel superset sep3d sep ${FFTW_LIBRARIES})

target_include_directories(sepmodel
	PRIVATE          
	   ${CMAKE_CURRENT_SOURCE_DIR}/../../include 
	PUBLIC
	   $<INSTALL_INTERFACE:include> 
	   $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}/../>
	   $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>  
      )
install(TARGETS sepmodel DESTINATION lib EXPORT  SEPlibTargets)
