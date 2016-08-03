

lib_LTLIBRARIES = libsepaux.la
if HAVE_FORTRAN
lib_LTLIBRARIES += libsepauxf90.la
endif
libsepaux_la_LIBADD = ../math/libsepmathf90.la ../math/libsepmath.la ../../corelibs/superset/libsuperset.la ../../corelibs/sep3d/libsep3d.la ../../corelibs/sep/libsep.la $(FCLIBS) -lm
libsepauxf90_la_LIBADD = libsepaux.la ../math/libsepmathf90.la ../math/libsepmath.la ../../corelibs/superset/libsuperset.la ../../corelibs/sep3d/libsep3d.la ../../corelibs/sep/libsep.la $(FCLIBS) -lm

libsepaux_la_SOURCES = arrayreadf.c compare.c pqueue.c arrayreadi.c \
multihdr.c sgainpar.c cent.c parcat.c time_window.c pad.c loop_calc.c patch_oc.c

libsepauxf90_la_SOURCES = aux_string_mod.f90 iter_mod.f90 \
sorting.f90 interpolate.f90 sort_subs.f90 utilities.f90 pad2.f90 \
interp2.f90 isamax.f90 subrslan.f90 helixcartmod_big.f90 septimers.f90 sep_aux.f90
libsepauxf90_la_CPPFLAGS = $(CFCDEFINES) -I$(top_srcdir)/tools/cfortran

include $(top_srcdir)/include/fortran.rules

