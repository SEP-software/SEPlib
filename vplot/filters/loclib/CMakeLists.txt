cmake_minimum_required(VERSION 2.8)
project(SEPLIB-vplot-filters-loclib)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../../../seplib_base/include)
set (SOURCES 
alloc.c   fsize.c   getch.c    getpar.c		getpar_scan.c	       seperr.c
bufpar.c  getch2.c  geth.c     getpar_decode.c	getpar_string_store.c
file.c	  getch_.c  getpar_.c  getparin.c	puth.c)





add_library(loclib ${SOURCES})
install(TARGETS loclib DESTINATION lib)
