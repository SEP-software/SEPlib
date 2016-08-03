
EXTRA_DIST = Aniso2d.F90sep Iso2d.F90sep Spike.csep Wavelet.csep \
Fdmod.csep Kirmod3d.F90sep Surface.csep Gauss.F90sep \
Marine_geom3d.F90sep Planar3d.F90sep Scatter3d.F90sep Vel.F90sep \
Aniso2d.f90s Gauss.f90s \
Iso2d.f90s Marine_geom3d.f90s Planar3d.f90s Scatter3d.f90s Vel.f90s

CLEANFILES = Spike.c Surface.c Surface.c Fdmod.c Aniso.f90 Iso2d.f90 \
Wavelet.f90 Gauss.f90 Kirmod3d.f90 Marine_geom.f90 Vel.f90 


bin_PROGRAMS = Surface Fdmod 
if HAVE_FORTRAN
bin_PROGRAMS +=Kirmod3d Vel Marine_geom3d Planar3d Scatter3d Iso2d Spike Aniso2d Gauss Wavelet
endif

LDADD = ${SUPERSET} ${SEPLIB3D} ${SEPLIB} ${SEPCWP} -lm

Aniso2d_SOURCES=Aniso2d.f90
Aniso2d_LDADD= ${SEPMATHF90} ${SEPLIB2DF90} ${SEPLIBF90} ${FCLIBS} -lm

Iso2d_SOURCES=Iso2d.f90
Iso2d_LDADD= ${SEPMATHF90} ${SEPLIB2DF90}  ${SEPLIBF90} ${FCLIBS} -lm

Vel_SOURCES=Vel.f90
Vel_LDADD= ${SEPLIB2DF90} ${SEPMATHF90} ${SEPLIBF90} ${FCLIBS} -lm

Gauss_SOURCES=Gauss.f90
Gauss_LDADD=${SEPLIB2DF90} ${SEPLIB3DF90} ${FCLIBS}

Marine_geom3d_SOURCES=Marine_geom3d.f90
Marine_geom3d_LDADD=${SEPLIB2DF90} ${SEPLIB3DF90} ${FCLIBS}

Planar3d_SOURCES=Planar3d.f90
Planar3d_LDADD=${SEPLIB2DF90} ${SEPLIB3DF90} ${FCLIBS}

Scatter3d_SOURCES=Scatter3d.f90
Scatter3d_LDADD=${SEPLIB2DF90} ${SEPLIB3DF90} ${FCLIBS}



Kirmod3d_SOURCES=Kirmod3d.f90 kirmod_mod.f90
Kirmod3d_LDADD=${SUPERSETF90} ${FCLIBS}

Fdmod_LDADD=${SUPERSET} -lsepcwp -lm


Wavelet_LDADD=-lsepfft -lsepfftf90  ${SEPMATH} ${SEPLIB3D}  -lm

# Modules dependencies
Kirmod3d.o: kirmod_mod.o

# Modules dependencies for libtool
Kirmod3d.lo: kirmod_mod.lo

Fdmod.c: Fdmod.csep
Spike.c: Spike.csep
Surface.c: Surface.csep
Wavelet.c: Wavelet.csep

Aniso2d.f90: Aniso2d.f90s
Aniso2d.f90s: Aniso2d.F90sep
Iso2d.f90: Iso2d.f90s
Iso2d.f90s: Iso2d.F90sep
Kirmod3d.f90: Kirmod3d.f90s
Kirmod3d.f90s: Kirmod3d.F90sep
Gauss.f90: Gauss.f90s 
Gauss.f90s: Gauss.F90sep
Marine_geom3d.f90: Marine_geom3d.f90s
Marine_geom3d.f90s: Marine_geom3d.F90sep
Planar3d.f90: Planar3d.f90s
Planar3d.f90s: Planar3d.F90sep
Scatter3d.f90: Scatter3d.f90s
Scatter3d.f90s: Scatter3d.F90sep
Vel.f90: Vel.f90s
Vel.f90s: Vel.F90sep

include $(top_srcdir)/include/fortran.rules

