cmake_minimum_required(VERSION 2.8)
project(SEPLIB-base-include)

set(INCLUDES    sepconvert.h	   sepmathf.h		sepvelan.h
    sepcube.h		   sepmath.h	
hwt.h	      sepfftf.h		   sep_old_external.h	sf_dip.h
mpi_sep.h     sepfft.h		   sep_par.h		
prototypes.h  sepfilterf.h	   sep_pars_external.h	su.h
segy.h	      sepfilter.h	   septravel.h		sulib.h
sep3dc.h      sep_fortran.h	   sepvectorf.h		superset.h
sep3d.h       seplib.h		   sepvector.h		vplot.h
sepaux.h      sep_main_external.h  sepvelanf.h)


install(FILES ${INCLUDES} DESTINATION include)
