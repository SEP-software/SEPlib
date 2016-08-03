
CLEANFILES = Scp3d.c

EXTRA_DIST = Scp3d.csep

bin_PROGRAMS = Scp3d

bin_SCRIPTS = Sls Srm3d Zero Smv3d

Scp3d_LDADD = ${SEPLIB} ${SEPLIB3D} 

Scp3d.c: Scp3d.csep

include $(top_srcdir)/include/fortran.rules


LINK_NO_CASE:	
	-rm -rf ${addprefix ${bindir}/, Ls${EXEEXT} Rm${EXEEXT} Cp${EXEEXT} Mv${EXEEXT} Cp3d${EXEEXT} Mv3d${EXEEXT} Rm3d${EXEEXT}}
	cd ${bindir} && @LN_S@ Scp3d${EXEEXT} Cp3d${EXEEXT}
	cd ${bindir} && @LN_S@ Smv3d${EXEEXT} Mv3d${EXEEXT}
	cd ${bindir} && @LN_S@ Srm3d${EXEEXT} Rm3d${EXEEXT}
	cd ${bindir} && @LN_S@ Srm3d${EXEEXT} Rm${EXEEXT}
	cd ${bindir} && @LN_S@ Smv3d${EXEEXT} Mv${EXEEXT}
	cd ${bindir} && @LN_S@ Scp3d${EXEEXT} Cp${EXEEXT}
	cd ${bindir} && @LN_S@ Sls${EXEEXT} Ls${EXEEXT}

RM_NO_CASE:
	-rm -rf ${addprefix ${bindir}/,Ls${EXEEXT} Rm${EXEEXT} Cp${EXEEXT} Mv${EXEEXT} Cp3d${EXEEXT} Mv3d${EXEEXT} Rm3d${EXEEXT}}


install-data-local:	@LINK_NO_CASE@
	-rm -rf ${addprefix ${bindir}/, Scp${EXEEXT} Smv${EXEEXT} Srm${EXEEXT}}
	cd ${bindir} && @LN_S@ Scp3d${EXEEXT} Scp${EXEEXT}
	cd ${bindir} && @LN_S@ Smv3d${EXEEXT} Smv${EXEEXT}
	cd ${bindir} && @LN_S@ Srm3d${EXEEXT} Srm${EXEEXT}


uninstall-local:	@RM_NO_CASE@
	-rm -rf ${addprefix ${bindir}/, Scp3d${EXEEXT} Smv3d${EXEEXT} Srm3d${EXEEXT}}


