

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../../../seplib_base/include ${NETPBM_INCLUDE_DIR})
set (SOURCE1 
rasattr.c	rasconf.c   rasreset.c	 rasvector4.c
rasvector2.c  rasvector.c
raserase.c     rasvector3.c)


set(SOURCES ${SOURCE1} rasclose.c rasopen.c )
set(SOURCES_SEP  ${SOURCE1} rasopen_SEP.c rasclose_SEP.c )





add_library(ras_pen STATIC ${SOURCES})
target_include_directories(ps_pen

	PUBLIC
	   $<INSTALL_INTERFACE:include> 
	   $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
	   )

target_link_libraries(ras_pen genlib loclib  ${NETPBM_LIBRARY}  vplotutil)
install(TARGETS ras_pen DESTINATION lib   EXPORT  SEPlibTargets)

add_library(ras_pen_SEP  STATIC ${SOURCES_SEP})
target_include_directories(ps_pen_SEP

	PUBLIC
	   $<INSTALL_INTERFACE:include> 
	   $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
	   )

target_link_libraries(ras_pen_SEP  genlib  ${NETPBM_LIBRARY} vplotutil tseplib sep)
install(TARGETS ras_pen_SEP DESTINATION lib   EXPORT  SEPlibTargets)
