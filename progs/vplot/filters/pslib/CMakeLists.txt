
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../../../seplib_base/include)
set (SOURCE1 
psarea.c     psdoc.h    ps.h	   psplot.c	     psreset.c
psattr.c   	  pserase.c 	   psraster_dumb.c   pstext.c
psclose.c   psfonts.h   psraster_smart.c  psvector.c)

set (SOURCES ${SOURCE1} psconf.c psopen.c)
set (SOURCES_SEP ${SOURCE1} psconf_SEP.c psopen_SEP.c)



add_library(ps_pen ${SOURCES})
target_include_directories(ps_pen

	PUBLIC
	   $<INSTALL_INTERFACE:include> 
	   $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
	   )

target_link_libraries(ps_pen  genlib loclib vplotutil vplot)
install(TARGETS ps_pen DESTINATION lib   EXPORT  SEPlibTargets)

add_library(ps_pen_SEP ${SOURCES_SEP})
target_include_directories(ps_pen_SEP

	PUBLIC
	   $<INSTALL_INTERFACE:include> 
	   $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
	   )

target_link_libraries(ps_pen_SEP genlib  vplotutil  loclib vplot tseplib sep)
install(TARGETS ps_pen_SEP DESTINATION lib   EXPORT  SEPlibTargets)


