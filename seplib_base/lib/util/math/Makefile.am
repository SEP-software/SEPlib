

lib_LTLIBRARIES = libsepmath.la
if HAVE_FORTRAN
lib_LTLIBRARIES +=  libsepmathf90.la
endif

libsepmath_la_LIBADD = -lm
libsepmathf90_la_LIBADD = libsepmath.la ../../corelibs/sep/libsep.la $(FCLIBS) -lm

libsepmath_la_SOURCES = cabs2.c cdiv.c cinv.c cmult.c csmult.c csub.c cadd.c \
cexp.c clog.c cneg.c cspow.c sqroot.c ccabs.c ciexp.c cmplx.c conjg.c csqrt.c

libsepmathf90_la_SOURCES = rand_mod.f90 subfslan.f90 pctrist.f90 ptridiag.f90 \
quant.f90 rand01.f90 rand.f90 vtris.f90

#Allow OMP FOR ROUTINES IN THIS DIRECTORY

# Module dependencies
pctrist.o: ptridiag.o

pctrist.lo: ptridiag.lo ../sepaux/utilities.lo

../sepaux/utilities.lo:
	cd ../sepaux && $(MAKE) utilities.lo

include $(top_srcdir)/include/fortran.rules
