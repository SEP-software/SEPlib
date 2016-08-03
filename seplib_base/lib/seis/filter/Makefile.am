

lib_LTLIBRARIES = libsepfilter.la 
if HAVE_FORTRAN
lib_LTLIBRARIES +=libsepfilterf90.la
endif


libsepfilter_la_SOURCES = energysubs.c sinc.c
libsepfilter_la_LIBADD = ../../class/gee/libsepgeef90.la ../../class/util/libsepclassutilf90.la ../../corelibs/superset/libsuperset.la ../../corelibs/sep3d/libsep3d.la ../../corelibs/sep/libsep.la $(FCLIBS) -lm

libsepfilterf90_la_SOURCES = boxconv77.f90 causint77.f90 icaf177.f90 icai377.f90 \
tcai277.f90 boxmo.f90 causint2.f90 icaf277.f90 tcai377.f90 burg.f90 \
icaf377.f90 tcaf177.f90 triangle77.f90 halfdifa.f90 icai177.f90 tcaf277.f90 \
triangle277.f90 halfint.f90 icai277.f90 tcai177.f90 cos_taper.f90 \
tri_smooth_mod.f90 nfilts_io.f90  sep_filter.f90 sinc_interp.f90

# burg2.f90  -> call cinlof(...)
# leaky.f90  -> call tris(...)
# butter.f90 -> call kolmogoroff(...) 

libsepfilterf90_la_LIBADD = libsepfilter.la ../../class/gee/libsepgeef90.la ../../class/util/libsepclassutilf90.la ../../corelibs/superset/libsuperset.la ../../corelibs/sep3d/libsep3d.la ../../corelibs/sep/libsep.la $(FCLIBS) -lm

include $(top_srcdir)/include/fortran.rules

