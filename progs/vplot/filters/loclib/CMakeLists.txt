
find_package(FLEX)
FLEX_TARGET(MyScanner2 ${CMAKE_CURRENT_SOURCE_DIR}/getpar_scan.l ${CMAKE_CURRENT_BINARY_DIR}/getpar_scan.c)


include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../include)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../../corelibs/include)
set (SOURCES 
alloc.c   fsize.c   getch.c    getpar.c		 ${FLEX_MyScanner2_OUTPUTS}       seperr.c
bufpar.c  getch2.c  geth.c     getpar_decode.c	getpar_string_store.c
file.c	  getch_.c  getpar_.c  getparin.c	puth.c)





add_library(loclib ${SOURCES})
target_include_directories(loclib

	PUBLIC
	   $<INSTALL_INTERFACE:include> 
	   $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
	   )

target_link_libraries(loclib vplotutil)
install(TARGETS loclib DESTINATION lib   EXPORT  SEPlibTargets)

