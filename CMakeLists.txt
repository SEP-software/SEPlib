project(SEPlib)
cmake_policy(SET CMP0042 NEW)
cmake_minimum_required(VERSION 2.8)
set(CMAKE_INCLUDE_CURRENT_DIR TRUE)

MESSAGE("Installing SEPlib in ${CMAKE_INSTALL_PREFIX}")
# configure a header file to pass some of the CMake settings

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake")
set(CMAKE_POSITION_INDEPENDENT_CODE True)
#
#  SEPLIB can be built with or without shared libraries.
#  If shared libraries are desired, we suggest building
#  with shared libraries first using
#
#       cmake -DBUILD_SHARED_LIBS=True
#
#  and then rebuilding without shared libraries using
#
#       cmake -DBUILD_SHARED_LIBS=False
#
#  so that the standard program executables are
#  statically linked.
#
set(CMAKE_SKIP_INSTALL_RPATH False)
set(CMAKE_SKIP_RPATH False)

set(SEPlib_MAJOR_VERSION 8)
set(SEPlib_MINOR_VERSION 2)
set(SEPlib_VERSION_STRING
  ${SEPlib_MAJOR_VERSION}.${SEPlib_MINOR_VERSION})
enable_language(Fortran C CXX)
set(CMAKE_Fortran_MODULE_DIRECTORY  ${CMAKE_INSTALL_PREFIX}/include)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -g -O2")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -O2")
set(CMAKE_Fortran_FLAGS "${CMAKE_Fortran_FLAGS} -g -O2")
set(DEFAULT_DOC_PATH ${CMAKE_INSTALL_PREFIX}/bin)


# Offer the user the choice of overriding the installation directories
set(INSTALL_LIB_DIR lib CACHE PATH "Installation directory for libraries")
set(INSTALL_BIN_DIR bin CACHE PATH "Installation directory for executables")
set(INSTALL_CMAKE_DIR ${DEF_INSTALL_CMAKE_DIR} CACHE PATH
  "Installation directory for CMake files")

# Make relative paths absolute (needed later on)
foreach(p LIB BIN INCLUDE CMAKE)
  set(var INSTALL_${p}_DIR)
  if(NOT IS_ABSOLUTE "${${var}}")
    set(${var} "${CMAKE_INSTALL_PREFIX}/${${var}}")
  endif()
endforeach()



SET(SEPlib_DIRNAME_lib     ${CMAKE_INSTALL_PREFIX}/lib)
SET(SEPlib_DIRNAME_include ${CMAKE_INSTALL_PREFIX}/include)
SET(SEPlib_DIRNAME_cmake ${CMAKE_INSTALL_PREFIX}/cmake)

find_package(SU)
if(SU_LIBRARIES)
set(SU_SUPPORT true)
endif(SU_LIBRARIES)
find_package(FFTW)
find_package(Motif)
find_package(PBM)
find_package(Xt)
find_package(Java)
find_package(JNI)
set(QT_USE_QT3SUPPORT True)
find_package(Qt4)
find_package(SymLink)
find_package(CCS)
find_package(Tdb)

INCLUDE (CheckIncludeFiles)
CHECK_INCLUDE_FILES(termios.h HAVE_TERMIOS_H)
CHECK_INCLUDE_FILES(termio.h HAVE_TERMIO_H)
CHECK_INCLUDE_FILES(stdio.h HAVE_STDIO_H)
CHECK_INCLUDE_FILES(stdlib.h HAVE_STDLIB_H)
CHECK_INCLUDE_FILES(string.h HAVE_STRING_H)
CHECK_INCLUDE_FILES(strings.h HAVE_STRINGS_H)
CHECK_INCLUDE_FILES(sys/ioctl.h HAVE_SYS_IOCTL_H)
CHECK_INCLUDE_FILES(sys/file.h HAVE_SYS_FILE_H)
CHECK_INCLUDE_FILES(sys/stat.h HAVE_SYS_STAT_H)
CHECK_INCLUDE_FILES(sys/tape.h HAVE_SYS_TAPE_H)
CHECK_INCLUDE_FILES(sys/uio.h HAVE_SYS_UIO_H)
CHECK_INCLUDE_FILES(sgtty.h HAVE_SGTTY_H)
CHECK_INCLUDE_FILES(signal.h HAVE_SIGNAL_H)
CHECK_INCLUDE_FILES(sys/types.h HAVE_SYS_TYPES_H)
CHECK_INCLUDE_FILES(sys/termios.h HAVE_SYS_TERMIOS_H)
CHECK_INCLUDE_FILES(sys/utsname.h HAVE_SYS_UTSNAME_H)
CHECK_INCLUDE_FILES(sys/param.h HAVE_SYS_PARAM_H)
CHECK_INCLUDE_FILES(unistd.h HAVE_UNISTD_H)
CHECK_INCLUDE_FILES(fcntl.h HAVE_FCNTL_H)
CHECK_INCLUDE_FILES(dirent.h HAVE_DIRENT_H)
CHECK_INCLUDE_FILES(sys/ndir.h HAVE_SYS_NDIR_H)
CHECK_INCLUDE_FILES(sys/dir.h HAVE_SYS_DIR_H)
CHECK_INCLUDE_FILES(ndir.h HAVE_NDIR_H)
CHECK_INCLUDE_FILES(limits.h HAVE_LIMITS_H)
CHECK_INCLUDE_FILES(errno.h HAVE_ERRNO_H)
CHECK_INCLUDE_FILES(sys/socket.h HAVE_SYS_SOCKET_H)
CHECK_INCLUDE_FILES(rpc/rpc.h HAVE_RPC_RPC_H)
CHECK_INCLUDE_FILES(rpc/types.h HAVE_RPC_TYPES_H)
CHECK_INCLUDE_FILES(ctime.h HAVE_CTIME_H)
CHECK_INCLUDE_FILES(utime.h HAVE_UTIME_H)

 
# add the binary tree to the search path for include files
# so that we will find TutorialConfig.h
include_directories("${PROJECT_BINARY_DIR}")


MESSAGE ( STATUS "Searching for X11..." )
FIND_PACKAGE ( X11 REQUIRED )
FIND_LIBRARY(X11_XT Xt PATHS /opt/local /usr/lib /usr/lib64 /usr/lib/X11 /usr/lib64/X11 /opt/X11/lib /opt/local/lib)
FIND_LIBRARY(X11_XAW Xaw PATHS /opt/local /usr/lib /usr/lib64 /usr/lib/X11 /usr/lib64/X11 /opt/X11/lib /opt/local/lib)
FIND_LIBRARY(X11_XP Xp PATHS /opt/local /usr/lib /usr/lib64 /usr/lib/X11 /usr/lib64/X11 /opt/X11/lib /opt/local/lib)


INCLUDE (CheckIncludeFile)
CHECK_INCLUDE_FILE(Xm/Xm.h HAVE_XM_XM_H "-I${MOTIF_INCLUDE_DIR}/.")
  
add_subdirectory(ratfor90)
add_subdirectory(seplib_base)
add_subdirectory(vplot)
add_subdirectory(seplib_prog)
if(JNI_FOUND AND Java_JAVAC_EXECUTABLE AND Java_JAVAH_EXECUTABLE AND Java_JAR_EXECUTABLE AND Java_JAVADOC_EXECUTABLE)
INCLUDE(UseJava)
add_subdirectory(seplib_java)
endif(JNI_FOUND AND Java_JAVAC_EXECUTABLE AND Java_JAVAH_EXECUTABLE AND Java_JAR_EXECUTABLE AND Java_JAVADOC_EXECUTABLE)
add_subdirectory(sep_python)
#Breaking remote installs...remove for now
#add_subdirectory(interact)
add_subdirectory(config)

configure_file (
  "${PROJECT_SOURCE_DIR}/module/seplib.in"
  "${PROJECT_BINARY_DIR}/module/seplib"
  )

install(FILES ${PROJECT_BINARY_DIR}/module/seplib  DESTINATION module)

configure_file (
  "${PROJECT_SOURCE_DIR}/sepConfig.h.in"
  "${PROJECT_BINARY_DIR}/sepConfig.h"
  )

install(FILES ${PROJECT_BINARY_DIR}/sepConfig.h  DESTINATION include)

configure_file (
  "${PROJECT_SOURCE_DIR}/seplib_base/include/ratsep.pl.in"
  "${PROJECT_BINARY_DIR}/seplib_base/include/ratsep"
  )


###################

export(TARGETS sep sep3d superset FILE "${PROJECT_BINARY_DIR}/SEPlibTargets.cmake")
export(PACKAGE SEPlib)

configure_file(${PROJECT_SOURCE_DIR}/cmake/SEPlibConfig.cmake.in
  "${PROJECT_BINARY_DIR}/cmake/SEPlibConfig.cmake" @ONLY)
# ... for both
configure_file(${PROJECT_SOURCE_DIR}/cmake/SEPlibConfigVersion.cmake.in
  "${PROJECT_BINARY_DIR}/cmake/SEPlibConfigVersion.cmake" @ONLY)

install(FILES
  "${PROJECT_BINARY_DIR}/cmake/SEPlibConfig.cmake"
  "${PROJECT_BINARY_DIR}/cmake/SEPlibConfigVersion.cmake"
  DESTINATION "${SEPlib_DIRNAME_cmake}" COMPONENT dev)

install(EXPORT SEPlibTargets DESTINATION
  "${SEPlib_DIRNAME_cmake}" COMPONENT dev)


###################








include(InstallRequiredSystemLibraries)
set(CPACK_RESOURCE_FILE_LICENSE "${PROJECT_SOURCE_DIR}/LICENSE")
set(CPACK_PACKAGE_VERSION_MAJOR "${SEPlib_MAJOR_VERSION}")
set(CPACK_PACKAGE_VERSION_MINOR "${SEPlib_MINOR_VERSION}")
set(CPACK_PACKAGE_VERSION_PATCH "0")
set(CPACK_PACKAGE_NAME "SEPlib")
set(CPACK_PACKAGE_CONTACT "Robert Clapp")
include(CPack)
