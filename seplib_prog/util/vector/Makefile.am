
EXTRA_DIST = Math_base.csep Log.csep Clip.csep Solver_ops.F90sep Solver_ops.f90s

CLEANFILES = Math_base.c Log.c Clip.c

bin_SCRIPTS = arithpar Math

bin_PROGRAMS = Math_base Log Clip
if HAVE_FORTRAN
bin_PROGRAMS += Solver_ops #Solver2_ops
endif


LDADD = $(SEPMATH) $(SEPAUX) $(SUPERSET) $(SEPLIB3D) $(SEPLIB) -lm
Solver_ops_SOURCES = Solver_ops.f90
Solver_ops_LDADD = ${SUPERSETF90} ${SEPLIB2DF90} ${SEPLIB3DF90} ${SEPAUXF90}  ${FCLIBS}

Solver_ops.f90s: Solver_ops.F90sep

#Solver2_ops_SOURCES = Solver2_ops.f90
#Solver2_ops_LDADD = ${SUPERSETF90} ${SEPLIB2DF90} ${SEPLIB3DF90} ${SEPAUXF90}  ${FCLIBS}

#Solver2_ops.f90s: Solver2_ops.F90sep


Math_base.c: Math_base.csep
Log.c: Log.csep
Clip.c: Clip.csep

include $(top_srcdir)/include/fortran.rules

#COMPILE MATH WITH THREADS
Math_base_LDADD = $(SEPMATH) $(SEPAUX) $(SUPERSET) $(SEPLIB3D) $(SEPLIB) ${PTHREAD_LIBS} -lm


install-data-local: uninstall-local
	-rm -rf ${addprefix ${bindir}/, Cmplx${EXEEXT} Rtoc${EXEEXT} Real${EXEEXT} Imag${EXEEXT} Conj${EXEEXT} Cabs${EXEEXT} Cabs2${EXEEXT} Gpow${EXEEXT} Pow${EXEEXT} Cadd${EXEEXT} Add${EXEEXT} Scale${EXEEXT}}
	cd ${bindir} && @LN_S@ Math_base${EXEEXT} Cmplx${EXEEXT}
	cd ${bindir} && @LN_S@ Math_base${EXEEXT} Rtoc${EXEEXT}
	cd ${bindir} && @LN_S@ Math_base${EXEEXT} Real${EXEEXT}
	cd ${bindir} && @LN_S@ Math_base${EXEEXT} Imag${EXEEXT}
	cd ${bindir} && @LN_S@ Math_base${EXEEXT} Conj${EXEEXT}
	cd ${bindir} && @LN_S@ Math_base${EXEEXT} Cabs${EXEEXT}
	cd ${bindir} && @LN_S@ Math_base${EXEEXT} Cabs2${EXEEXT}
	cd ${bindir} && @LN_S@ Math_base${EXEEXT} Gpow${EXEEXT}
	cd ${bindir} && @LN_S@ Math_base${EXEEXT} Pow${EXEEXT}
	cd ${bindir} && @LN_S@ Math_base${EXEEXT} Add${EXEEXT}
	cd ${bindir} && @LN_S@ Math_base${EXEEXT} Cadd${EXEEXT}
	cd ${bindir} && @LN_S@ Clip${EXEEXT} Scale${EXEEXT}

uninstall-local:
	-rm -rf $(addsuffix ${EXEEXT},${addprefix ${bindir}/, Rtoc Real Imag Conj Cabs Cabs2 Gpow Pow Cadd Cmplx Add Scale})


