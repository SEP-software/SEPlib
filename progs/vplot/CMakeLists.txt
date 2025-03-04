
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake")
set(CMAKE_POSITION_INDEPENDENT_CODE True)
set(CMAKE_SKIP_INSTALL_RPATH False)
set(CMAKE_SKIP_RPATH False)

set(SEPlib-vplot_MAJOR_VERSION 9)
set(SEPlib-vplot_MINOR_VERSION 0)
set(SEPlib-vplot_VERSION_STRING
  ${SEPlib-vplot_MAJOR_VERSION}.${SEPlib-io_MINOR_VERSION})
enable_language(C OPTIONAL Fortran)

set(CMAKE_Fortran_MODULE_DIRECTORY  ${CMAKE_INSTALL_PREFIX}/include)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -g -O2")

set(CMAKE_Fortran_FLAGS "${CMAKE_Fortran_FLAGS} -g -O2")
find_package(X11)

find_package(PBM)
find_package(Xt)


# Offer the user the choice of overriding the installation directories
set(INSTALL_LIB_DIR lib CACHE PATH "Installation directory for libraries")
set(INSTALL_CMAKE_DIR ${DEF_INSTALL_CMAKE_DIR} CACHE PATH
  "Installation directory for CMake files")

# Make relative paths absolute (needed later on)
foreach(p LIB BIN INCLUDE CMAKE)
  set(var INSTALL_${p}_DIR)
  if(NOT IS_ABSOLUTE "${${var}}")
    set(${var} "${CMAKE_INSTALL_PREFIX}/${${var}}")
  endif()
endforeach()
MESSAGE ( STATUS "Searching for X11..." )
FIND_PACKAGE ( X11 REQUIRED )
FIND_LIBRARY(X11_XT Xt  HINTS ${X11_PATH}/lib PATHS /opt/local /usr/lib /usr/lib64 /usr/lib/X11 /usr/lib64/X11 /opt/X11/lib /opt/local/lib)
FIND_LIBRARY(X11_XAW Xaw HINTS ${X11_PATH}/lib PATHS ${CMAKE_INSTALL_PREFIX}/lib /opt/local /usr/lib /usr/lib64 /usr/lib/X11 /usr/lib64/X11 /opt/X11/lib /opt/local/lib)
FIND_LIBRARY(X11_XP Xp PATHS /opt/local /usr/lib /usr/lib64 /usr/lib/X11 /usr/lib64/X11 /opt/X11/lib /opt/local/lib)


include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/corelibs/include)
include_directories(${SEPCONFIGDIR})


add_subdirectory(include)
add_subdirectory(libvplot)
add_subdirectory(filters)
add_subdirectory(util)
add_subdirectory(glplot)
add_subdirectory(main)

