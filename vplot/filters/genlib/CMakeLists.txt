cmake_minimum_required(VERSION 2.8)
project(SEPLIB-vplot-filters-genlib)

set (SOURCES 
genarea.c	  geninteract.c  genpatarea.c  genraster.c  nulldev.c	vecarea.c
gen_do_dovplot.c  genmarker.c	 genpoint.c    gentext.c    polyfix.c
genhatch.c	  genmessage.c	 genraster1.c  genvector.c  polysubs.c)




add_library(genlib ${SOURCES})
install(TARGETS genlib DESTINATION lib)
