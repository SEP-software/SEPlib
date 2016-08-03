


lib_LTLIBRARIES = libsepvector.la
if HAVE_FORTRAN
lib_LTLIBRARIES+= libsepvectorf90.la
libsepvectorf90_la_LIBADD = libsepvector.la $(FCLIBS) -lm
endif

libsepvector_la_SOURCES = setvalf.c setvali.c
libsepvector_la_LIBADD = -lm

libsepvectorf90_la_SOURCES =sep_vector.f90 adjnull77.f90 copy77.f90 scale.f90 \
inv.f90 ipow.f90 sqrt.f90
libsepvectorf90_la_CPPFLAGS = $(CFCDEFINES) -I$(top_srcdir)/tools/cfortran

include $(top_srcdir)/include/fortran.rules
