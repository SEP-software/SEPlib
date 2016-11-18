cmake_minimum_required(VERSION 2.8)
project(SEPLIB-vplot-filters-tseplib)

set (SOURCES 
doc.c  geth.c  Puthead.c  seperr.c  sepwhere.c)





add_library(tseplib ${SOURCES})
install(TARGETS tseplib DESTINATION lib)
