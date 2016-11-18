cmake_minimum_required(VERSION 2.8)
project(SEPLIB-base-lib-util-fft)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../../../include)

set (SOURCES 
cefft.c        fftw.f90      ft1axis.f90  ftlib1.f90  refft.c	  rvfft.c
cvfft90.c      fftwflag.f90  ft2axis.f90  ftnew.f90    rfft.f90   sep_fft.f90
 fth.f90	  ftu.f90      rowcc.f90)
if(FFTW_LIBRARIES)
MESSAGE("FFTW INSTALLED")
else(FFTW_LIBRARIES)
set(SOURCES ${SOURCES} fake_fftw.f90)
endif(FFTW_LIBRARIES)


set(SOURCES ${SOURCES} fake_fftw.f90)


add_library(sepfft ${SOURCES})
install(TARGETS sepfft DESTINATION lib)
