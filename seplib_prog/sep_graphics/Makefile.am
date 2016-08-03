
EXTRA_DIST = Box.csep Dip_azim.F90sep Graph.csep Operplot.csep \
Ta2vplot.csep Wiggle.csep Contour.csep Dots.csep Grey.csep Overlay.csep \
Taplot.csep Cubeplot.csep Ftplot.csep Histogram.csep Seis_vel.F90sep \
Thplot.csep Merge_field.csep

CLEANFILES = Box.c Dots.c Grey.c Operplot.c Thplot.c Contour.c Histogram.c \
 Ta2vplot.c Cubeplot.c Graph.c Wiggle.c Overlay.c Ftplot.c Taplot.c  Merge_field.c

#CPROG_LOCAL=Overlay
#FCPROG_LOCAL=Dip_azim Seis_vel

bin_PROGRAMS = Box Dots Grey Operplot Thplot Contour Histogram \
Ta2vplot Cubeplot Graph Wiggle Overlay Merge_field
if HAVE_FORTRAN
bin_PROGRAMS +=  Ftplot Taplot Dip_azim Seis_vel
endif

LDADD = $(GLPLOT) $(VPLOT) $(SEPLIB3D) -lm

Dip_azim_SOURCES=Dip_azim.f90
Dip_azim_LDADD=${SEPLIB2DF90} ${SEPLIB3DF90} ${SEPAUXF90} -lsepmathf90 ${FCLIBS}

Seis_vel_SOURCES=Seis_vel.f90
Seis_vel_LDADD=${SEPLIB3DF90} ${SEPLIB2DF90} ${FCLIBS} 


Grey_CPPFLAGS = $(CFCDEFINES) -I$(top_srcdir)/tools/cfortran
Grey_LDADD=$(SEPAUX) $(LDADD)


Taplot_CPPFLAGS = $(CFCDEFINES) -I$(top_srcdir)/tools/cfortran
Taplot_LDADD=$(SEPAUX) $(SEPMATH) $(GLPLOT) $(VPLOT) $(SEPLIB) -lm

Ftplot_LDADD=$(SEPFFT) $(SEPMATH) $(GLPLOT) $(VPLOT) $(SEPLIB)  -lm

Box.c: Box.csep
Graph.c: Graph.csep
Operplot.c: Operplot.csep
Ta2vplot.c: Ta2vplot.csep
Wiggle.c: Wiggle.csep
Contour.c: Contour.csep
Dots.c: Dots.csep
Grey.c: Grey.csep
Overlay.c: Overlay.csep
Taplot.c: Taplot.csep
Cubeplot.c: Cubeplot.csep
Ftplot.c: Ftplot.csep
Histogram.c: Histogram.csep
Thplot.c: Thplot.csep

Seis_vel.f90: Seis_vel.f90s
Seis_vel.f90s: Seis_vel.F90sep
Dip_azim.f90: Dip_azim.f90s
Dip_azim.f90s: Dip_azim.F90sep

include $(top_srcdir)/include/fortran.rules

install-data-local:
	-rm -rf ${bindir}/Byte
	cd ${bindir} && ${LN_S} Taplot Byte

uninstall-local:
	-rm -rf ${bindir}/Byte

