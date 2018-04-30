cmake_minimum_required(VERSION 2.8)
project(SEPLIB-base-lib-util-fft)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../../../include)
include_directories(/usr/local/include)
include_directories(/usr/include)

set (SOURCES 
cefft.c        fftw.f90      ft1axis.f90  ftlib1.f90  refft.c	  rvfft.c
cvfft90.c      fftwflag.f90  ft2axis.f90  ftnew.f90    rfft.f90   sep_fft.f90
fth.f90       rowcc.f90 fake_fftw.f90)

set (FORTRANS
ftu.f90s
)

#if(FFTWF_LIBRARIES)
MESSAGE("FFTW INSTALLED")
set (sppflags "-DUSE_FFTW" )
include_directories(${FFTWF_INCLUDES})
#else(FFTWF_LIBRARIES)
#set(SOURCES ${SOURCES} fake_fftw.f90)
#endif(FFTWF_LIBRARIES)

FOREACH (fort ${FORTRANS})
  STRING(REGEX REPLACE ".f90s\$" ".f90" fortFile "${fort}")
  ADD_CUSTOM_COMMAND(OUTPUT "${fortFile}"
    COMMAND ${CMAKE_CURRENT_SOURCE_DIR}/../../../tools/spp/spp <${CMAKE_CURRENT_SOURCE_DIR}/${fort} ${sppflags} >${fortFile}
    DEPENDS "${fort}" )
  set (SOURCES ${SOURCES} ${fortFile})
ENDFOREACH(fort)


add_library(sepfft ${SOURCES})

if(FFTWF_LIBRARIES)
target_link_libraries (sepfft ${FFTWF_LIBRARIES})
endif()

install(TARGETS sepfft DESTINATION lib)
