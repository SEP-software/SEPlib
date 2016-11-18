project(SEPLIB)
cmake_minimum_required(VERSION 2.8)
set(CMAKE_INCLUDE_CURRENT_DIR TRUE)

MESSAGE("Installing SEPlib in ${CMAKE_INSTALL_PREFIX}")
# configure a header file to pass some of the CMake settings

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake")

enable_language(Fortran C CXX)
set(CMAKE_Fortran_MODULE_DIRECTORY  ${CMAKE_INSTALL_PREFIX}/include)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -g -O2")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -pg")
set(CMAKE_Fortran_FLAGS "${CMAKE_Fortran_FLAGS} -g -O2")
set(DEFAULT_DOC_PATH ${CMAKE_INSTALL_PREFIX}/bin)

find_package(SU)
if(SU_LIBRARIES)
set(SU_SUPPORT true)
endif(SU_LIBRARIES)
find_package(FFTW )


 
# add the binary tree to the search path for include files
# so that we will find TutorialConfig.h
include_directories("${PROJECT_BINARY_DIR}")

configure_file (
  "${PROJECT_SOURCE_DIR}/sepConfig.h.in"
  "${PROJECT_BINARY_DIR}/sepConfig.h"
  )


MESSAGE ( STATUS "Searching for X11..." )
FIND_PACKAGE ( X11 REQUIRED )
FIND_LIBRARY(X11_XT Xt HINTS /usr/lib /usr/lib64 /usr/lib/X11 /usr/lib64/X11 )
FIND_LIBRARY(X11_XAW Xaw HINTS /usr/lib /usr/lib64 /usr/lib/X11 /usr/lib64/X11 )


install(FILES ${PROJECT_BINARY_DIR}/sepConfig.h  DESTINATION include)
add_subdirectory(ratfor90)
add_subdirectory(seplib_base)
add_subdirectory(vplot)
add_subdirectory(seplib_prog)
add_subdirectory(sep_python)
add_subdirectory(config)
