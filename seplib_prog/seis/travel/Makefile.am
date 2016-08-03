
EXTRA_DIST = Gfgradz.F90sep MTTmaps.F90sep Gfgradz.f90s MTTmaps.f90s Hwt2d.csep

CLEANFILES = MTTmaps.f90 Gfgradz.f90

#CPROG_LOCAL=Hwt3d Hwt2d
#FCPROG_LOCAL=MTTmaps Gfgradz

bin_PROGRAMS = Hwt3d Hwt2d  FMeikonal
if HAVE_FORTRAN
bin_PROGRAMS += Gfgradz  MTTmaps
endif



LDADD = $(SEPTRAVEL) $(SEPAUX) $(SEPLIB3D) $(SEPLIB) -lm

MTTmaps_SOURCES = MTTmaps.f90
MTTmaps_LDADD = ${SEPLIB2DF90} $(SEPLIBF90) $(FCLIBS)

Gfgradz_SOURCES = Gfgradz.f90
Gfgradz_LDADD = ${SEPLIB2DF90} $(SEPLIBF90) $(FCLIBS)

Gfgradz.f90: Gfgradz.f90s
Gfgradz.f90s: Gfgradz.F90sep
MTTmaps.f90: MTTmaps.f90s
MTTmaps.f90s: MTTmaps.F90sep

Hwt2d.c: Hwt2d.csep

include $(top_srcdir)/include/fortran.rules

