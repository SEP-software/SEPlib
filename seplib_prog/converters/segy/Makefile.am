
EXTRA_DIST = Sep2segy.csep Segy2sep.csep
CLEANFILES = Sep2segy.c Segy2sep.c

bin_PROGRAMS = 
if HAVE_SU
bin_PROGRAMS += Segy2sep Sep2segy
endif



LDADD = $(SUSEPLIB) -lm

Segy2sep_SOURCES = Segy2sep.c 
Sep2segy_SOURCES = Sep2segy.c 

Sep2segy.c: Sep2segy.csep
Segy2sep.c: Segy2sep.csep


include $(top_srcdir)/include/fortran.rules
