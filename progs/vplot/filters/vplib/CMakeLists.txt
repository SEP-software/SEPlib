
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../../../seplib_base/include)
set (SOURCE1 
vpattr.c      vpdoc.h	   vplogmessage.c  vpopen.c    vpreset.c	 vpvector.c
vpclose.c     vpdovplot.c  vplogvector.c   vpplot.c  
     vperase.c    vpmarker.c	   vppoly.c   
 vp.h	   vpmessage.c	   vpraster.c  vptext.c)

set(SOURCES ${SOURCE1} vpsepwhere.c vpconf.c)
set(SOURCES_SEP  ${SOURCE1} vpsepwhere_SEP.c vpconf_SEP.c)






add_library(vp_pen ${SOURCES})
target_include_directories(vp_pen

	PUBLIC
	   $<INSTALL_INTERFACE:include> 
	   $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
	   )

target_link_libraries(vp_pen genlib loclib  vplotutil)
install(TARGETS vp_pen DESTINATION lib   EXPORT  SEPlibTargets)

add_library(vp_pen_SEP ${SOURCES_SEP})
target_include_directories(ps_pen_SEP

	PUBLIC
	   $<INSTALL_INTERFACE:include> 
	   $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
	   )

target_link_libraries(vp_pen_SEP genlib vplotutil tseplib sep)
install(TARGETS vp_pen_SEP DESTINATION lib   EXPORT  SEPlibTargets)
