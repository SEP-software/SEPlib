
EXTRA_DIST = Attr.csep Dis3dhead.F90sep Get.csep Sdd.csep Attr3dhead.F90sep \
Disfil.csep Datapath.csep In3d.csep Dis3dhead.f90s Attr3dhead.f90s  


bin_PROGRAMS = Attr Sdd Disfil Get In3d Datapath
if HAVE_FORTRAN
bin_PROGRAMS +=  Dis3dhead Attr3dhead
endif


bin_SCRIPTS = atoF

LDADD = ${SUPERSET} ${SEPLIB3D} -lm

Attr_LDADD = ${SUPERSET} ${SEPLIB3D} -lpthread -lm

Dis3dhead_SOURCES = Dis3dhead.f90
Dis3dhead_LDADD = ${SUPERSETF90} ${SEPLIB2DF90} ${SEPAUXF90} ${SEPMATHF90} ${FCLIBS}


Attr3dhead_SOURCES = Attr3dhead.f90
Attr3dhead_LDADD = ${SUPERSETF90} ${SEPLIB2DF90} ${SEPAUXF90} ${SEPMATHF90} ${FCLIBS}

Attr.c: Attr.csep
Sdd.c: Sdd.csep
Datapath.c: Datapath.csep
Disfil.c: Disfil.csep
In3d.c: In3d.csep
Get.c: Get.csep 

Dis3dhead.f90: Dis3dhead.f90s
Dis3dhead.f90s: Dis3dhead.F90sep
Attr3dhead.f90: Attr3dhead.f90s
Attr3dhead.f90s: Attr3dhead.F90sep

include $(top_srcdir)/include/fortran.rules

LINK_NO_CASE:
	-rm -rf ${addprefix ${bindir}/, Dd${EXEEXT}}
	cd ${bindir} && @LN_S@ Sdd${EXEEXT} Dd${EXEEXT}

RM_NO_CASE:
	-rm -rf ${addprefix ${bindir}/, Dd${EXEEXT}}

install-data-local: @LINK_NO_CASE@
	-rm -rf ${addprefix ${bindir}/, In${EXEEXT}}
	cd ${bindir} && @LN_S@ In3d${EXEEXT} In${EXEEXT}

uninstall-local: @RM_NO_CASE@
	-rm -rf ${addprefix ${bindir}/, In${EXEEXT}}

