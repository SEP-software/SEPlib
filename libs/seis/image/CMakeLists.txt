cmake_minimum_required(VERSION 3.4)

set(CMAKE_MACOSX_RPATH 1)
if(FFTW_LIBRARIES)
set (sppflags "-DUSE_FFTW" )
endif()

set (SOURCES 
fftwflags.f90  srm_storm.f90 amo.f90
kirchfast.f90  omppar.f90 kirmod_mod.f90)

set (FORTRANS
adcig.f90s odcig.f90s)

FOREACH (fort ${FORTRANS})
  STRING(REGEX REPLACE ".f90s\$" ".f90" fortFile "${fort}")
  ADD_CUSTOM_COMMAND(OUTPUT "${fortFile}"
    COMMAND ${CMAKE_CURRENT_SOURCE_DIR}/../../include/spp <${CMAKE_CURRENT_SOURCE_DIR}/${fort} ${sppflags} >${fortFile}
    DEPENDS "${fort}" )
  set (SOURCES ${SOURCES} ${fortFile})
ENDFOREACH(fort)




add_library(sepimage ${SOURCES})
target_link_libraries( sepimage sepfft sepmath sepvectorOps  ${FFTW_LIBRARIES})

target_include_directories(sepimage
	PRIVATE          
	   ${CMAKE_CURRENT_SOURCE_DIR}/../../include 
	PUBLIC
	   $<INSTALL_INTERFACE:include> 
	   $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}/../>
	   $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>  
      )
install(TARGETS sepimage DESTINATION lib EXPORT  SEPlibTargets)
