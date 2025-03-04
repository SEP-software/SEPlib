cmake_minimum_required(VERSION 3.13)
if(POLICY CMP0048)
  cmake_policy(SET CMP0048 NEW)
endif(POLICY CMP0048)
project(SEPlib-seisProgs VERSION 9.0.0 LANGUAGES CXX C Fortran)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake")

set(SEPlib_MAJOR_VERSION 9)
set(SEPlib_MINOR_VERSION 0)
set(SEPlib_VERSION_STRING ${SEPlib_MAJOR_VERSION}.${SEPlib_MINOR_VERSION})

  

# Handle superbuild first
option (USE_SUPERBUILD "Whether or not a superbuild should be invoked" OFF)
if (USE_SUPERBUILD)
message("IN SPUER")
  project (SUPERBUILD NONE)
  # execute the superbuild (this script will be invoked again without the
  # USE_SUPERBUILD option this time)
  include (cmake/SuperBuild.cmake)
else()


if(NOT SUBPACKAGE)
	option(BUILD_DOC "Build documentation" OFF)
  option(BUILD_TEST "Build with test support" OFF)

else(NOT SUBPACKAGE)
  option(BUILD_DOC "Build documentation" OFF)
endif(NOT SUBPACKAGE)

option(BUILD_SEISMIC_PROGS "Build seismic programs" ON)
option(BUILD_UTIL_PROGS "Build seismic programs" ON)
option(BUILD_CONVERTER_PROGS "Build seismic programs" ON)
option(BUILD_JAVA "Build java interfaces" OFF)
option(BUILD_GCP "Build GCP" OFF)
option(BUILD_MAKERULES "Install makerules" OFF)
option(BUILD_VPLOT_GRAPHICS "Build vplot programs" ON)
# option(BUILD_RATFOR90 "Build and install ratfor90" OFF)
include_directories(${CMAKE_CURRENT_BINARY_DIR}/libs/core/external/genericIO/)
include_directories(
  ${CMAKE_CURRENT_SOURCE_DIR}/libs/core/external/genericIO/external/buffers/external/json
  )

if(BUILD_TEST)
  enable_testing()
endif(BUILD_TEST)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Git QUIET)
if(GIT_FOUND AND EXISTS "${PROJECT_SOURCE_DIR}/.git") 
  # Update submodules as needed
  option(GIT_SUBMODULE "Check submodules during build" ON)
  if(GIT_SUBMODULE AND NOT SUBPACKAGE)
    message(STATUS "Submodule update")
    execute_process(COMMAND ${GIT_EXECUTABLE} submodule update --init
                            --recursive
                    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
                    RESULT_VARIABLE GIT_SUBMOD_RESULT)
  endif()
endif()

if(NOT EXISTS "${PROJECT_SOURCE_DIR}/libs/core/CMakeLists.txt")
  message(
    FATAL_ERROR
      "The submodules were not downloaded! GIT_SUBMODULE was turned off or failed. Please update submodules and try again."
    )
endif()
macro(install_symlink filepath sympath)
    install(CODE "execute_process(COMMAND ${CMAKE_COMMAND} -E create_symlink ${filepath} ${sympath})")
    install(CODE "message(\"-- Created symlink: ${sympath} -> ${filepath}\")")
endmacro(install_symlink)
set(SYMLINK_FOUND True)

add_subdirectory(libs/core)
include_directories(libs/core/include)
include_directories(libs/core/sep)
find_package(TIRPC)
if(${TIRPC_FOUND})
  include_directories(${TIRPC_INCLUDE_DIRS})
  set(TIRPC ${TIRPC_LIBRARIES})
else()
  set(TIRPC "")
endif()


set(CMAKE_Fortran_MODULE_DIRECTORY ${CMAKE_INSTALL_PREFIX}/include)
include_directories(${CMAKE_INSTALL_PREFIX}/include)

find_package(TBB REQUIRED)
find_package(FFTW REQUIRED)

set(SUBPACKAGE yes)
if(BUILD_CLASS_LIBS
   OR BUILD_JAVA
   OR BUILD_SEISMIC_PROGS
   OR BUILD_UTIL_PROGS
   OR BUILD_UTIL_LIBS
   OR BUILD_CONVERTER_PROGS
   OR BUILD_VPLOT_GRAPHICS)
  add_subdirectory(libs/class)
endif(BUILD_CLASS_LIBS
      OR
      BUILD_JAVA
      OR
      BUILD_SEISMIC_PROGS
      OR
      BUILD_UTIL_PROGS
      OR
      BUILD_UTIL_LIBS
      OR
      BUILD_CONVERTER_PROGS
      OR
      BUILD_VPLOT_GRAPHICS)

if(BUILD_JAVA
   OR BUILD_SEISMIC_PROGS
   OR BUILD_UTIL_PROGS
   OR BUILD_UTIL_LIBS
   OR BUILD_CONVERTER_PROGS
   OR BUILD_VPLOT_GRAPHICS)
  add_subdirectory(libs/util)
  add_subdirectory(libs/seis)
endif(BUILD_JAVA
      OR
      BUILD_SEISMIC_PROGS
      OR
      BUILD_UTIL_PROGS
      OR
      BUILD_UTIL_LIBS
      OR
      BUILD_CONVERTER_PROGS
      OR
      BUILD_VPLOT_GRAPHICS)

set(SEPCONFIGDIR ${CMAKE_CURRENT_BINARY_DIR}/libs/core)

if(BUILD_UTIL_PROGS)
  add_subdirectory(progs/util)
endif(BUILD_UTIL_PROGS)

if(BUILD_SEISMIC_PROGS)
  add_subdirectory(progs/seis)
endif(BUILD_SEISMIC_PROGS)

if(BUILD_CONVERTER_PROGS)
  add_subdirectory(progs/converters)
endif(BUILD_CONVERTER_PROGS)

if(BUILD_VPLOT_GRAPHICS)
  add_subdirectory(progs/vplot)
endif(BUILD_VPLOT_GRAPHICS)

# if(BUILD_RATFOR90) add_subdirectory(ratfor90) endif(BUILD_RATFOR90)

if(BUILD_JAVA)
  add_subdirectory(java)
endif(BUILD_JAVA)

include(InstallRequiredSystemLibraries)
set(CPACK_RESOURCE_FILE_LICENSE "${PROJECT_SOURCE_DIR}/LICENSE")
set(CPACK_PACKAGE_VERSION_MAJOR "${SEPlib_MAJOR_VERSION}")
set(CPACK_PACKAGE_VERSION_MINOR "${SEPlib_MINOR_VERSION}")
set(CPACK_PACKAGE_VERSION_PATCH "0")
set(CPACK_PACKAGE_NAME "SEPlib")
set(CPACK_PACKAGE_CONTACT "Robert Clapp")
include(CPack)
endif()
