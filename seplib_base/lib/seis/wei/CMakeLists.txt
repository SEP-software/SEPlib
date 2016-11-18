cmake_minimum_required(VERSION 2.8)
project(SEPLIB-base-lib-seis-wei)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../../../include)



set (SOURCES 
lloyd.f90)
if(FFTW_LIBRARIES)
set(SOURCES ${SOURCES}
	  wei_fk_share.f90  wei_path.f90      wei_timers.f90
weiattr.f90	  wei_flags.f90     wei_pspi.f90      wei_verb.f90
wei_basics.f90	  wei_image.f90     wei_quantile.f90  wei_wavespace.f90
wei_cam.f90	  wei_imaging.f90   wei_run.f90       wei_wem.f90
weicig.f90	  wei_kmap.f90	    wei_sll.f90       wei_xmap.f90
wei_data.f90	  wei_mem.f90	    wei_slow.f90
wei_external.f90  wei_mig_base.f90  wei_ssf.f90
wei_fft.f90	  wei_par.f90	    weitds.f90)

endif(FFTW_LIBRARIES)
add_library(sepwei ${SOURCES})
install(TARGETS sepwei DESTINATION lib)
