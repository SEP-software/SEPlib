

lib_LTLIBRARIES = libsepcwp.la
if HAVE_FORTRAN
lib_LTLIBRARIES += libsepcwpf90.la
endif

libsepcwp_la_SOURCES = pfafft.c valpkge.c xdrbhdrsub.c xdrhdrsub.c cwp_alloc.c \
ealloc.c intcub.c xindex.c cubicspline.c
libsepcwp_la_LIBADD = ../../corelibs/sep/libsep.la $(FCLIBS) -lm

libsepcwpf90_la_SOURCES = sep_cwp.f90
libsepcwpf90_la_LIBADD = libsepcwp.la ../../corelibs/sep/libsep.la $(FCLIBS) -lm


include $(top_srcdir)/include/fortran.rules

