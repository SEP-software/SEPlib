cmake_minimum_required(VERSION 2.8)
project(SEPLIB-base-lib-seis-image)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../../../include)


set (SOURCES 
adcig.f90  fftwflags.f90  odcig.f90   srm_storm.f90
amo.f90    kirchfast.f90  omppar.f90 kirmod_mod.f90)


add_library(sepimage ${SOURCES})
install(TARGETS sepimage DESTINATION lib)
