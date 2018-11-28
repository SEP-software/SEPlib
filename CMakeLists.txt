project(SEPlib)
message("IN MAIN")
cmake_minimum_required(VERSION 2.8)

set(SEPlib_MAJOR_VERSION 9)
set(SEPlib_MINOR_VERSION 0)
set(SEPlib_VERSION_STRING ${SEPlib_MAJOR_VERSION}.${SEPlib_MINOR_VERSION})

option(BUILD_SEISMIC_PROGS "Build seismic programs" ON)
option(BUILD_UTIL_PROGS "Build seismic programs" ON)
option(BUILD_CONVERTER_PROGS "Build seismic programs" ON)
option(BUILD_JAVA "Build java interfaces" OFF)
option(BUILD_MAKERULES "Install makerules" OFF)
option(BUILD_VPLOT_GRAPHICS "Build vplot programs" ON)
option(BUILD_RATFOR90 "Build and install ratfor90" OFF)

find_package(Git QUIET)
if(GIT_FOUND AND EXISTS "${PROJECT_SOURCE_DIR}/.git")
  # Update submodules as needed
  option(GIT_SUBMODULE "Check submodules during build" ON)
  if(GIT_SUBMODULE)
    message(STATUS "Submodule update")
    execute_process(COMMAND ${GIT_EXECUTABLE} submodule update --init
                            --recursive
                    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
                    RESULT_VARIABLE GIT_SUBMOD_RESULT)
    if(NOT GIT_SUBMOD_RESULT EQUAL "0")
      message(
        FATAL_ERROR
          "git submodule update --init failed with ${GIT_SUBMOD_RESULT}, please checkout submodules"
        )
    endif()
  endif()
endif()

if(NOT EXISTS "${PROJECT_SOURCE_DIR}/progs/seis/corelibs/CMakeLists.txt")
  message(
    FATAL_ERROR
      "The submodules were not downloaded! GIT_SUBMODULE was turned off or failed. Please update submodules and try again."
    )
endif()

message("BEORE CONDITIONAL IO")
if(NOT BUILD_CLASS_LIBS
   AND
   NOT BUILD_JAVA
   AND
   NOT BUILD_SEISMIC_PROGS
   AND
   NOT BUILD_UTIL_PROGS
   AND
   NOT BUILD_CONVERTER_PROGS
   AND
   NOT BUILD_VPLOT_GRAPHICS)
  option(BUILD_UTIL_LIBS "Build and install util LIBS" OFF)
  if(BUILD_UTIL_LIBS)
    add_subdirectory(progs/seis/libs)
  else(BUILD_UTIL_LIBS)
      option(BUILD_IO_LIBS "Build and install IO LIBS" ON)
  if(BUILD_IO_LIBS)
    add_subdirectory(progs/seis/corelibs)
  endif(BUILD_IO_LIBS)

  endif(BUILD_UTIL_LIBS)
endif(NOT
      BUILD_CLASS_LIBS
      AND
      NOT
      BUILD_JAVA
      AND
      NOT
      BUILD_SEISMIC_PROGS
      AND
      NOT
      BUILD_UTIL_PROGS
      AND
      NOT
      BUILD_CONVERTER_PROGS
      AND
      NOT
      BUILD_VPLOT_GRAPHICS)


if(NOT BUILD_SEISMIC_PROGS)
  option(BUILD_CLASS_LIBS "Build and class LIBS" ON)
  if(BUILD_CLASS_LIBS)
    add_subdirectory(progs/seis/class)
  endif(BUILD_CLASS_LIBS)
endif(NOT  BUILD_SEISMIC_PROGS)

if(NOT BUILD_UTIL_PROGS)
  option(BUILD_PYTHON "Build python classes" ON)
  if(BUILD_PYTHON)
    add_subdirectory(progs/util/python)
  endif(BUILD_PYTHON)
endif(NOT  BUILD_UTIL_PROGS)



if(BUILD_RATFOR90)
  add_subdirectory(ratfor90)
endif(BUILD_RATFOR90)

if(BUILD_JAVA)
  add_subdirectory(java)
endif(BUILD_JAVA)

if(BUILD_SEISMIC_PROGS)
  add_subdirectory(progs/seis)
  set(SEPCONFIGDIR ${CMAKE_CURRENT_BINARY_DIR}/progs/seis/corelibs)

endif(BUILD_SEISMIC_PROGS)

if(BUILD_UTIL_PROGS)

  add_subdirectory(progs/util)
  if(NOT SEPCONFIGDIR)
      set(SEPCONFIGDIR ${CMAKE_CURRENT_BINARY_DIR}/progs/util/corelibs)
  endif(NOT SEPCONFIGDIR)
endif(BUILD_UTIL_PROGS)

if(BUILD_CONVERTER_PROGS)
  add_subdirectory(progs/converters)
    if(NOT SEPCONFIGDIR)
      set(SEPCONFIGDIR ${CMAKE_CURRENT_BINARY_DIR}/progs/converters/corelibs)
  endif(NOT SEPCONFIGDIR)
endif(BUILD_CONVERTER_PROGS)

message("BEFORE VPLOt")
if(BUILD_VPLOT_GRAPHICS)
  add_subdirectory(progs/vplotProgs)
    if(NOT SEPCONFIGDIR)
      set(SEPCONFIGDIR ${CMAKE_CURRENT_BINARY_DIR}/progs/vplotProgs/corelibs)
  endif(NOT SEPCONFIGDIR)
endif(BUILD_VPLOT_GRAPHICS)

include(InstallRequiredSystemLibraries)
set(CPACK_RESOURCE_FILE_LICENSE "${PROJECT_SOURCE_DIR}/LICENSE")
set(CPACK_PACKAGE_VERSION_MAJOR "${SEPlib_MAJOR_VERSION}")
set(CPACK_PACKAGE_VERSION_MINOR "${SEPlib_MINOR_VERSION}")
set(CPACK_PACKAGE_VERSION_PATCH "0")
set(CPACK_PACKAGE_NAME "SEPlib")
set(CPACK_PACKAGE_CONTACT "Robert Clapp")
include(CPack)

