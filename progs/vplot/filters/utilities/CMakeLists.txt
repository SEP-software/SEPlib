
set (SOURCES 
clip.c	   dither.c   error.c	greycorr.c   solve.c  vecoutline.c
dashvec.c  dupside.c  fatvec.c	intersect.c  sort.c   vptodev.c)


add_library(vplotutil ${SOURCES})
target_include_directories(vplotutil

	PUBLIC
	   $<INSTALL_INTERFACE:include> 
	   $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
	   )

target_link_libraries(vplotutil vplot)
install(TARGETS vplotutil DESTINATION lib   EXPORT  SEPlibTargets)


