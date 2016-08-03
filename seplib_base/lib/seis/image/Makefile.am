EXTRA_DIST=odcig.f90s adcig.f90s

lib_LTLIBRARIES = 
if HAVE_FORTRAN
lib_LTLIBRARIES += libsepimagef90.la
endif

libsepimagef90_la_LIBADD = \
   ../../util/math/libsepmathf90.la \
   ../../util/math/libsepmath.la \
   ../../corelibs/sep/libsep.la $(FCLIBS) -lm

libsepimagef90_la_SOURCES = fftwflags.f90 omppar.f90 adcig.f90 odcig.f90 \
srm_storm.f90 amo.f90 kirchfast.f90 
# stoltmig.f90 -> call cinterp1(...)
# gazadj.f90   -> data(iw,ikx) = data(iw,ikx) * eiktau(...) 
# aamig.f90    -> call trimo(...)
# phasemig.f90 -> call null(...)


include $(top_srcdir)/include/fortran.rules
