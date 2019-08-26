include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../../../seplib_base/include)
include_directories(${X11_INCLUDES})
set (SOURCE1 
appdata.c  xtcolors.c	 xtdoc.h	   xtframe.h	   xtplot.c
popup.c    xtcommands.c  	   xtgetpoint.c  xtpaint.c     xtpoint.c
xtarea.c   xtcommands.h   xtinteract.c  xtpen.h       xtraster.c
xtattr.c    xterase.c	   xtmessage.c	 xtpixmap.c
xtclose.c    xtframe.c	   	 xtpixmap.h)

set(SOURCES ${SOURCE1} xt_dovplot.c xtopen.c xtconf.c)
set(SOURCES_SEP  ${SOURCE1} xt_dovplot_SEP.c xtopen_SEP.c xtconf_SEP.c)




add_library(xt_pen STATIC ${SOURCES})
target_include_directories(xt_pen

	PUBLIC
	   $<INSTALL_INTERFACE:include> 
	   $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
${X11_INCLUDE_DIR}
	   )

target_link_libraries(xt_pen genlib loclib  vplotutil ${X11_XAW} ${X11_XT} ${X11_LIBRARIES} )
install(TARGETS xt_pen DESTINATION lib   EXPORT  SEPlibTargets)

add_library(xt_pen_SEP STATIC ${SOURCES_SEP})
target_include_directories(xt_pen_SEP

	PUBLIC
	   $<INSTALL_INTERFACE:include> 
	   $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
${X11_INCLUDE_DIR}
	   )

target_link_libraries(xt_pen_SEP genlib vplotutil loclib  tseplib ${X11_XAW} ${X11_XT} ${X11_LIBRARIES} sep)
install(TARGETS xt_pen_SEP DESTINATION lib   EXPORT  SEPlibTargets)
