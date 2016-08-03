

lib_LTLIBRARIES = 
if HAVE_FORTRAN
lib_LTLIBRARIES += libsepvelanf90.la
endif

libsepvelanf90_la_LIBADD = ../filter/libsepfilterf90.la \
   ../filter/libsepfilter.la \
   ../../util/math/libsepmathf90.la \
   ../../util/math/libsepmath.la \
   ../../corelibs/superset/libsuperset.la \
   ../../corelibs/sep3d/libsep3d.la \
   ../../corelibs/sep/libsep.la $(FCLIBS) -lm

libsepvelanf90_la_SOURCES = velansub.f90 nmo_varoff.f90 nmo_subs.f90 \
vconvsubs.f90 rms2int.f90 velsimp.f90 vint2rms.f90 hypint.f90 \
hypsum.f90
# veltran.f90 -> call null(...)
# veltran.f90 -> call trimo(...)

include $(top_srcdir)/include/fortran.rules

