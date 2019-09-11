cmake_minimum_required(VERSION 2.8)

set(CMAKE_MACOSX_RPATH 1)
include_directories(${SEPLIBCONFIGDIR})
set (SOURCES 
fastmarch.c    hwt_func.c  hwt_gen.c  hwt_ray.c  hwt_tesel.c)



add_library(septravel ${SOURCES})
target_link_libraries( septravel sepaux sepfilter sep)

target_include_directories(septravel
	PRIVATE          
	   ${CMAKE_CURRENT_SOURCE_DIR}/../../include 
	PUBLIC
	   $<INSTALL_INTERFACE:include> 
	   $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>  
      )
install(TARGETS septravel DESTINATION lib EXPORT  SEPlibTargets)
