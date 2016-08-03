

lib_LTLIBRARIES = libseppar.la
if HAVE_MPI
lib_LTLIBRARIES +=  libseppar_mpi.la
endif
if HAVE_FORTRAN
lib_LTLIBRARIES +=  libsepparf90.la
libsepparf90_la_LIBADD = libseppar.la ../../corelibs/sep/libsep.la $(FCLIBS) -lm
if HAVE_MPI
lib_LTLIBRARIES +=  libsepparf90_mpi.la
libsepparf90_mpi_la_LIBADD = libseppar_mpi.la ../../corelibs/sep/libsep.la $(FCLIBS) -lm
endif
endif
                                                                                
libseppar_la_SOURCES = pass.c  lock.c
libseppar_la_LIBADD = ../../corelibs/sep/libsep.la $(FCLIBS) -lm

libseppar_mpi_la_SOURCES = pass_mpi.c lock.c split.c
libseppar_mpi_la_CPPFLAGS = $(CFCDEFINES) $(MPI_FLAGS) \
  -I$(top_srcdir)/tools/cfortran
libseppar_mpi_la_LIBADD = ../../corelibs/sep/libsep.la $(FCLIBS) -lm

libsepparf90_la_SOURCES = fortstubs.c

libsepparf90_mpi_la_SOURCES = fortstubs.c 
libsepparf90_mpi_la_CPPFLAGS = $(CFCDEFINES) $(MPI_FLAGS) \
  -I$(top_srcdir)/tools/cfortran

include $(top_srcdir)/include/fortran.rules
