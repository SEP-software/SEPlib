

set (SOURCES 
convert_char.c	createfloat.c    getbackint.c   zasc.c)

if(CMAKE_Fortran_COMPILER)
set(SOURCES ${SOURCES} sepconvert.f90)
endif(CMAKE_Fortran_COMPILER)


set(CMAKE_MACOSX_RPATH 1)

add_library(sepconvert ${SOURCES})
#target_include_directories(sepconvert
#
#	PUBLIC
#	   $<INSTALL_INTERFACE:include> 
#	   $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
#	   )

target_link_libraries(sepconvert sep3d sep)
install(TARGETS sepconvert DESTINATION lib   EXPORT  SEPlibTargets )



