cmake_minimum_required(VERSION 3.4)

set(CMAKE_MACOSX_RPATH 1)
if(FFTW_LIBRARIES)
set (sppflags "-DUSE_FFTW" )
endif()

set (SOURCES 
allder3d.f90	    dipinteg_effic.f90	model_mask.f90
allpass3d.f90	    igrad2_2d_reg.f90  super_chain_mod.f90
find_slope_mod.f90  igrad3_epst.f90    ztrans_mod.f90
divide.f90 	    grad3_dip.f90
)

set (FORTRANS
dipinteg_3Dcos.f90s
)

FOREACH (fort ${FORTRANS})
  STRING(REGEX REPLACE ".f90s\$" ".f90" fortFile "${fort}")
  ADD_CUSTOM_COMMAND(OUTPUT "${fortFile}"
    COMMAND ${CMAKE_CURRENT_SOURCE_DIR}/../../include/spp <${CMAKE_CURRENT_SOURCE_DIR}/${fort} ${sppflags} >${fortFile}
    DEPENDS "${fort}" )
  set (SOURCES ${SOURCES} ${fortFile})
ENDFOREACH(fort)



add_library(sepdip ${SOURCES})
target_link_libraries( sepdip sep ${FFTW_LIBRARIES})

target_include_directories(sepdip
	PRIVATE          
	   ${CMAKE_CURRENT_SOURCE_DIR}/../../include 
	PUBLIC
	   $<INSTALL_INTERFACE:include> 
	   $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>  
      )
install(TARGETS sepdip DESTINATION lib EXPORT  SEPlibTargets)

