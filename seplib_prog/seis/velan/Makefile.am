
EXTRA_DIST = Hypint.F90sep MCvfit.F90sep Velan3d.F90sep Vslan.F90sep Hypmovie.F90sep \
Nmo3d.F90sep Stretch.F90sep Velan.csep Hypsum.F90sep Vconvert.F90sep Hypint.f90s \
Hypsum.f90s Stretch.f90s Velan3d.f90s Hypmovie.f90s MCvfit.f90s \
Vconvert.f90s Vslan.f90s 

CLEANFILES = Velan.c Hypint.f90 Hypsum.f90 Nmo3d.f90 Vconvert.f90 \
Hypmovie.f90 MCvfit.f90 Stretch.f90 Velan3d.f90 


bin_SCRIPTS = NMO Radial Radnmo Unmo LMO

bin_PROGRAMS = Velan
if HAVE_FORTRAN
bin_PROGRAMS +=  Hypint Hypmovie Hypsum MCvfit Stretch Vconvert \
Velan3d Nmo3d Vslan
endif

LDADD = $(SEPLIB3D) -lm

Vconvert_SOURCES = Vconvert.f90
Vconvert_LDADD = ${GEEF90} ${SEPVELANF90} ${SEPFILTERF90} ${CLASSUTILF90} ${SEPLIBF90} \
${SEPFFTF90} ${SEPMATHF90}  ${SEP3D} ${SEPLIBF90} ${FCLIBS}

Vslan_SOURCES = Vslan.f90
Vslan_LDADD = ${GEEF90} ${SEPFFTF90} ${CLASSUTILF90} ${SEPMATHF90} ${SEPLIB2DF90} ${FCLIBS} -lm

Hypint_SOURCES = Hypint.f90
Hypint_LDADD = ${GEEF90} ${SEPFFTF90} ${CLASSUTILF90} ${SEPMATHF90} ${SEPVELANF90} \
${SEPLIB2DF90} ${SEPFILTERF90} ${SEPLIBF90} ${FCLIBS}

Hypmovie_SOURCES = Hypmovie.f90
Hypmovie_LDADD = ${GEEF90} ${SEPVELANF90} ${SEPFILTERF90} ${CLASSUTILF90} ${SEPLIB2DF90} \
${SEPFFTF90} ${SEPMATHF90} ${SEPLIB3D}  ${SEPLIBF90} ${SEPLIB3DF90} ${FCLIBS}

Hypsum_SOURCES = Hypsum.f90
Hypsum_LDADD = ${GEEF90} ${SEPVELANF90} ${SEPFILTERF90} ${CLASSUTILF90} ${SEPLIB2DF90} ${SEPLIB3DF90}\
${SEPFFTF90} ${SEPMATHF90} ${SEPLIB3D} ${SEPLIBF90} ${FCLIBS}

MCvfit_SOURCES = MCvfit.f90
MCvfit_LDADD = ${GEEF90} ${SEPVELANF90} ${SEPFILTERF90} ${CLASSUTILF90} ${SEPLIBF90} \
${SEPFFTF90} ${SEPMATHF90}  ${SEPLIB3D}  ${SEPLIBF90} ${FCLIBS}

Stretch_SOURCES = Stretch.f90
Stretch_LDADD = ${GEEF90} ${SEPVELANF90} ${SEPFILTERF90} ${CLASSUTILF90} ${SEPLIBF90} \
${SEPFFTF90} ${SEPMATHF90}  ${SEPLIB3D} ${SEPLIBF90} ${FCLIBS}

Velan3d_SOURCES = Velan3d.f90
Velan3d_LDADD = ${SEPVELANF90} ${SUPERSETF90} ${GEEF90} ${CLASSUTILF90} ${SEPFILTERF90} \
${SEPFFTF90} ${SEPMATHF90} ${SEPLIB2DF90} ${FCLIBS}

Nmo3d_SOURCES = Nmo3d.f90
Nmo3d_LDADD = ${SEPVELANF90} ${SUPERSETF90} ${SEPAUXF90} ${SEPMATHF90} \
${SEPFILTERF90} ${SEPFFTF90} ${SEPLIB2DF90} ${GEEF90}  ${CLASSUTILF90} ${FCLIBS}

Velan.c: Velan.csep

%M.F90sep: %.F90sep
	cp $*.F90sep $@


Hypint.f90: Hypint.f90s
Hypint.f90s: Hypint.F90sep
MCvfit.f90: MCvfit.f90s
MCvfit.f90s: MCvfit.F90sep
Velan3d.f90: Velan3d.f90s
Velan3d.f90s: Velan3d.F90sep
Vslan.f90: Vslan.f90s
Vslan.f90s: Vslan.F90sep
Hypmovie.f90: Hypmovie.f90s
Hypmovie.f90s: Hypmovie.F90sep 
Nmo3d.f90s: Nmo3d.F90sep
Stretch.f90: Stretch.f90s
Stretch.f90s: Stretch.F90sep
Hypsum.f90: Hypsum.f90s
Hypsum.f90s: Hypsum.F90sep
Vconvert.f90: Vconvert.f90s
Vconvert.f90s: Vconvert.F90sep

include $(top_srcdir)/include/fortran.rules


