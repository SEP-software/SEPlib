
#EXTRA_DIST =  Sdip.csep Dip.F90sep  Dipintegrator.F90sep Flatten.F90sep
EXTRA_DIST =   Dip.F90sep  Dipintegrator.F90sep Flatten.F90sep

#bin_PROGRAMS =Sdip
bin_PROGRAMS =
if HAVE_FORTRAN
bin_PROGRAMS += Dip  Dipintegrator Flatten
endif

LDADD = $(SEPFILTER) $(SEPMATH) $(SEPLIB3D) -lm
LD_SEPLIBF90 = $(SEPLIBF90) $(FCLIBS) 
LD_GEEF90 = $(GEEF90) $(SEPFFTF90) $(SEPLIB2DF90) $(FCLIBS) -lm
LD_SEPLIB3DF90 = $(SEPLIB3DF90) $(FCLIBS)
LD_SUPERSETF90 = $(SUPERSETF90) $(SEPLIB2DF90)

#Sdip_LDADD=${SEPSERGEY}  ${SEPLIB3D} ${SEPLIB} -lm

Dipintegrator_SOURCES = Dipintegrator.f90
Dipintegrator_LDADD = ${SEPDIPF90} $(SEPMATHF90) $(LD_SUPERSETF90) $(SEPDIPF90) ${SEPFFTF90} $(LD_SEPLIB3DF90) ${FFTW_FCLD}

Flatten_SOURCES = Flatten.f90
Flatten_LDADD = ${SEPDIPF90} ${SEPFILTERF90} ${SEPFILTER} $(SEPGEEF90) $(LD_SUPERSETF90) $(SEPDIPF90) ${SEPFFTF90} $(LD_SEPLIB3DF90) ${FFTW_FCLD}

#${SEPFFTF90} ${SEPMATHF90} -lsepvector \
#-lsepvectorf90 ${FFTW_FCLD} $

Dipintegrator.f90: Dipintegrator.f90s
Dipintegrator.f90s: Dipintegrator.F90sep

Dip_SOURCES = Dip.f90
Dip_LDADD = ${SEPFFTF90} $(SEPMATHF90) $(LD_SUPERSETF90) $(SEPDIPF90) $(LD_SEPLIB3DF90) 

Dip.f90: Dip.f90s
Dip.f90s: Dip.F90sep

#Sdip.c: Sdip.csep

include $(top_srcdir)/include/fortran.rules
