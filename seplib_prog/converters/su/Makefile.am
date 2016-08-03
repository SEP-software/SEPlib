
EXTRA_DIST = Su2sep.csep Sep2su.csep
CLEANFILES = Su2sep.c Sep2su.c

bin_PROGRAMS =
if HAVE_SU
bin_PROGRAMS += Su2sep Sep2su
endif

LDADD = $(SUSEPLIB) -lm

Su2sep_SOURCES = Su2sep.c
Sep2su_SOURCES = Sep2su.c

Su2sep.c: Su2sep.csep 
Sep2su.c: Sep2su.csep


include $(top_srcdir)/include/fortran.rules
