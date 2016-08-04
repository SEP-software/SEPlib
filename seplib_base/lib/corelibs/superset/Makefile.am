
EXTRA_DIST =  rite.inc.in

SUPERSET=axes.c init.c reed.c debug.c keys.c rite.c drn.c tagstream.c \
header.c list.c rite_file.c headval.c ntraces.c type_usage.c grid.c \
extra_keys.c conform.c  struct_sepc.c fortran_junk.c

MPISUPER=mpi_thread.c coord.c  convert.c  transfer.c

lib_LTLIBRARIES = libsuperset.la
if HAVE_SU
lib_LTLIBRARIES +=libsepsu.la 
endif
if HAVE_MPI
lib_LTLIBRARIES +=libsuperset_mpi.la
libsuperset_mpi_la_LIBADD = ../sep3d/libsep3d.la ../sep/libsep.la $(FCLIBS) -lm
endif

libsepsu_la_SOURCES = reed_su.c rite_su.c init_su.c
libsepsu_la_CPPFLAGS =  -I../include
libsepsu_la_LIBADD = ../sep3d/libsep3d.la ../sep/libsep.la $(FCLIBS) -lm

libsuperset_la_SOURCES = $(SUPERSET) $(MPISUPER) 
if HAVE_FORTRAN
libsuperset_la_SOURCES+=struct_sepf.f90 
endif

libsuperset_mpi_la_SOURCES = $(SUPERSET) $(MPISUPER) 
libsuperset_mpi_la_CPPFLAGS = $(MPI_FLAGS) -I../include
libsuperset_la_CPPFLAGS =  -I../include
libsuperset_la_LIBADD = ../sep3d/libsep3d.la ../sep/libsep.la $(FCLIBS) -lm

libsupersetf90_la_CPPFLAGS = $(CFCDEFINES) -I$(top_srcdir)/tools/cfortran -I../include

%_mpi.o: %_mpi.c
	if $(COMPILE) ${MPI_FLAGS} -MT $@ -MD -MP -MF "$(DEPDIR)/$*_mpi.Tpo" -c -o $@ $<; \
  then mv -f "$(DEPDIR)/$*.Tpo" "$(DEPDIR)/$*_mpi.Po"; else rm -f "$(DEPDIR)/$*_mpi.Tpo"; exit 1; fi


%_mpi.c: %.c
	cp $*.c $@


include $(top_srcdir)/include/fortran.rules
