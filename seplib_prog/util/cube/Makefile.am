
EXTRA_DIST = Reshape.csep Sort3d.F90sep Transp.csep \
Interleave.csep Reverse.csep Window3d.csep  Merge.csep \
Scat3d.csep Stack3d.F90sep Window.csep Fold3d.F90sep Pad.csep Stack.csep \
Fold3d.f90s Stack3d.f90s Sort3d.f90s  Patch.csep


bin_SCRIPTS = Scat

bin_PROGRAMS = Pad Window Merge Reverse Transp Interleave Window3d Scat3d SortByHdrs Patch Reshape
if HAVE_FORTRAN
bin_PROGRAMS += Sort3d Stack3d Fold3d 
endif

LDADD=${SEPLIB3D} ${FCLIBS} -lm

Merge_LDADD = ${SEPAUX} ${SEPLIB3D} ${FCLIBS} -lm

Fold3d_SOURCES = Fold3d.f90
Fold3d_LDADD = ${GEEF90} ${CLASSUTILF90} ${SEPLIB2DF90} ${SEPLIB3DF90} ${SEPAUXF90} $(SEPMATHF90) ${FCLIBS} -lm

Sort3d_SOURCES = Sort3d.f90
Sort3d_LDADD = ${SEPAUXF90} ${SEPCONVERTF90} ${SEPLIB3DF90} ${SEPLIB2DF90} $(SEPMATHF90) ${FCLIBS} -lm

Patch_LDADD = ${SEPAUX} ${SEPLIB3D} ${FCLIBS} -lm

Pad_LDADD = ${SEPAUX} ${SEPLIB3D} ${FCLIBS} -lm

Reshape_LDADD = ${SUPERSET} ${FCLIBS} -lm

Scat3d_LDADD = ${SUPERSET} ${FCLIBS} -lm

SortByHdrs_LDADD = ${SEPLIB3D} ${FCLIBS} -lm

Transp_LDADD = ${SUPERSET} ${FCLIBS} -lm

Stack3d_SOURCES=Stack3d.f90
Stack3d_LDADD =${SUPERSETF90} ${SEPLIB2DF90} ${GEEF90} ${CLASSUTILF90} ${FCLIBS}

%M.csep:	%.csep
	cp $*.csep $@


Window3d_LDADD = ${SUPERSET} ${FCLIBS} -lm

Reshape.c: Reshape.csep
Transp.c: Transp.csep
Interleave.c: Interleave.csep
Reverse.c: Reverse.csep
Window3d.c: Window3d.csep
Merge.c: Merge.csep 
Scat3d.c: Scat3d.csep
Window.c: Window.csep
Pad.c: Pad.csep
Stack.c: Stack.csep 

Sort3d.f90: Sort3d.f90s
Sort3d.f90s: Sort3d.F90sep
Stack3d.f90: Stack3d.f90s
Stack3d.f90s: Stack3d.F90sep
Fold3d.f90: Fold3d.f90s
Fold3d.f90s: Fold3d.F90sep

include $(top_srcdir)/include/fortran.rules

LINK_NO_CASE:
	-rm -rf ${addprefix ${bindir}/, Cat3d${EXEEXT} Cat${EXEEXT}}
	cd ${bindir} && @LN_S@ Scat${EXEEXT} Cat${EXEEXT}
	cd ${bindir} && @LN_S@ Scat3d${EXEEXT} Cat3d${EXEEXT}

RM_NO_CASE:
	-rm -rf ${addprefix ${bindir}/,Cat${EXEEXT} Cat3d${EXEEXT}}

install-data-local: @LINK_NO_CASE@
	-rm -rf ${addprefix ${bindir}/, Scat${EXEEXT} Infill3d${EXEEXT} Stack${EXEEXT} Grid_fold${EXEEXT}}
	cd ${bindir} && @LN_S@ Scat3d${EXEEXT} Scat${EXEEXT}
	cd ${bindir} && @LN_S@ Stack3d${EXEEXT} Stack${EXEEXT}
	cd ${bindir} && @LN_S@ Stack3d${EXEEXT} Infill3d${EXEEXT}
	cd ${bindir} && @LN_S@ Sort3d${EXEEXT} Grid_fold${EXEEXT}

uninstall-local: @RM_NO_CASE@
	-rm -rf ${addprefix ${bindir}/, Scat${EXEEXT} Infill3d${EXEEXT} Stack${EXEEXT} Grid_fold${EXEEXT}}


