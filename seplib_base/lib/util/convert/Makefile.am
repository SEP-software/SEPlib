
lib_LTLIBRARIES = libsepconvert.la 
if HAVE_FORTRAN
lib_LTLIBRARIES += libsepconvertf90.la
endif

libsepconvert_la_SOURCES = convert_char.c createfloat.c getbackint.c zasc.c

libsepconvert_la_LIBADD = ../../corelibs/sep/libsep.la $(FCLIBS) -lm

libsepconvertf90_la_SOURCES = sepconvert.f90

libsepconvertf90_la_LIBADD = libsepconvert.la ../../corelibs/sep/libsep.la $(FCLIBS) -lm

include $(top_srcdir)/include/fortran.rules
