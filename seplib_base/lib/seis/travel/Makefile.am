

lib_LTLIBRARIES = libseptravel.la 
if HAVE_FORTRAN
#lib_LTLIBRARIES += libseptravelf90.la
endif


libseptravel_la_SOURCES = fastmarch.c hwt_func.c hwt_ray.c hwt_gen.c \
hwt_tesel.c

libseptravel_la_LIBADD = ../../util/sepaux/libsepaux.la ../../corelibs/superset/libsuperset.la ../../corelibs/sep3d/libsep3d.la ../../corelibs/sep/libsep.la $(FCLIBS) -lm

#libseptravelf90_la_SOURCES = fortstubs.c
#libseptravelf90_la_CPPFLAGS = ${CFCDEFINES} -I$(top_srcdir)/tools/cfortran

#libseptravelf90_la_LIBADD = libseptravel.la ../../util/sepaux/libsepaux.la ../../corelibs/superset/libsuperset.la ../../corelibs/sep3d/libsep3d.la ../../corelibs/sep/libsep.la $(FCLIBS) -lm
