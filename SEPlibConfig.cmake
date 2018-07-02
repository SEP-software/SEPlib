
# - Config file for the FooBar package
# It defines the following variables
#  SEPINCDIR - include directories for SEPlib
#  SEPLIBDIR    - SEPlib library directory
#  SEPBINDIR     - SEPlib binary directory

####### Expanded from @PACKAGE_INIT@ by configure_package_config_file() #######
####### Any changes to this file will be overwritten by the next CMake run ####
####### The input file was SEPlibConfig.cmake.in                            ########

get_filename_component(PACKAGE_PREFIX_DIR "${CMAKE_CURRENT_LIST_DIR}/../" ABSOLUTE)

macro(set_and_check _var _file)
  set(${_var} "${_file}")
  if(NOT EXISTS "${_file}")
    message(FATAL_ERROR "File or directory ${_file} referenced by variable ${_var} does not exist !")
  endif()
endmacro()

macro(check_required_components _NAME)
  foreach(comp ${${_NAME}_FIND_COMPONENTS})
    if(NOT ${_NAME}_${comp}_FOUND)
      if(${_NAME}_FIND_REQUIRED_${comp})
        set(${_NAME}_FOUND FALSE)
      endif()
    endif()
  endforeach()
endmacro()

####################################################################################

if(NOT TARGET sep)
  INCLUDE(${CMAKE_CURRENT_LIST_DIR}/SEPlibExports.cmake)
endif()

get_cmake_property(_variableNames VARIABLES)


set_and_check(SEPlib_DIRNAME_lib "${PACKAGE_PREFIX_DIR}/lib")
set_and_check(SEPlib_DIRNAME_include "${PACKAGE_PREFIX_DIR}/include")

set(SEPINCDIR SEPlib_INCLUDE_DIR)

