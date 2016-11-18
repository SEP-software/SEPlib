cmake_minimum_required(VERSION 2.8)
project(SEPLIB-base-lib-util-dip)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../../../include)


set (SOURCES 
allder3d.f90	    dipinteg_effic.f90	grad3_dip.f90	   model_mask.f90
allpass3d.f90	    divide.f90		igrad2_2d_reg.f90  super_chain_mod.f90
dipinteg_3Dcos.f90  find_slope_mod.f90	igrad3_epst.f90    ztrans_mod.f90)


add_library(sepdip ${SOURCES})
install(TARGETS sepdip DESTINATION lib)
