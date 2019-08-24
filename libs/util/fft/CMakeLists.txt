#cmake_minimum_required(VERSION 2.8)

set (SOURCES 
cefft.c         refft.c	  
    )
if(CMAKE_Fortran_COMPILER)

set(SOURCES ${SOURCES}
     fftw.f90      ft1axis.f90  ftlib1.f90  
fftwflag.f90  ft2axis.f90  ftnew.f90    rfft.f90   sep_fft.f90
fth.f90       rowcc.f90 fake_fftw.f90)
set (FORTRANS
ftu.f90s
)
endif(CMAKE_Fortran_COMPILER)

set(CMAKE_MACOSX_RPATH 1)
set (sppflags "-DUSE_FFTW" )
include_directories(${FFTWF_INCLUDES})

FOREACH (fort ${FORTRANS})
  STRING(REGEX REPLACE ".f90s\$" ".f90" fortFile "${fort}")
  ADD_CUSTOM_COMMAND(OUTPUT "${fortFile}"
    COMMAND ${CMAKE_CURRENT_SOURCE_DIR}/../../include/spp <${CMAKE_CURRENT_SOURCE_DIR}/${fort} ${sppflags} >${fortFile}
    DEPENDS "${fort}" )
  set (SOURCES ${SOURCES} ${fortFile})
ENDFOREACH(fort)


add_library(sepfft ${SOURCES})
target_link_libraries(sepfft sep3d sep)
#target_include_directories(sepfft
#
#	PUBLIC
#	   $<INSTALL_INTERFACE:include> 
#	   $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
#	   )
#
target_link_libraries(sepfft  ${FFTW_LIBRARIES})
install(TARGETS sepfft DESTINATION lib   EXPORT  SEPlibTargets )





