
set (SOURCES 
doc.c  geth.c  Puthead.c  seperr.c  sepwhere.c)



add_library(tseplib ${SOURCES})
target_include_directories(tseplib

	PUBLIC
	   $<INSTALL_INTERFACE:include> 
	   $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
	   )

target_link_libraries(tseplib sep)
install(TARGETS tseplib DESTINATION lib   EXPORT  SEPlibTargets)


