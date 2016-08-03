
SUBDIRS = include vplotfonts genlib utilities loclib tseplib xtlib pslib raslib vplib

bin_PROGRAMS = xtpen vppen ppmpen pspen Svppen Spspen Sppmpen Sxtpen

BASE = dovplot.c proc_vplot.c
NOSEPPEN = ${BASE} main_vplot.c init_vplot.c
SEPPEN = ${BASE} init_vplot_SEP.c main_vplot_SEP.c
BLIB = ./genlib/libgenlib.la ./utilities/libvplotutil.la ./loclib/libloclib.la ../libvplot/libvplotf90.la ../libvplot/libvplot.la -lm
BSLIB = ./genlib/libgenlib.la ./utilities/libvplotutil.la ./loclib/libloclib.la ./tseplib/libtseplib.la ../${SEPLIB} ../libvplot/libvplotf90.la ../libvplot/libvplot.la ${FCLIBS} -lm

Sxtpen_SOURCES=${SEPPEN}
xtpen_SOURCES=${NOSEPPEN}
Sxtpen_LDADD=./xtlib/libxtpen_sep.la ${BSLIB} ${X_LIBS} ${X_PRE_LIBS} ${X_EXTRA_LIBS}
xtpen_LDADD=./xtlib/libxtpen.la ${BLIB} ${X_LIBS} ${X_PRE_LIBS} ${X_EXTRA_LIBS}

Spspen_SOURCES=${SEPPEN}
pspen_SOURCES=${NOSEPPEN}
Spspen_LDADD=./pslib/libpspen_sep.la ${BSLIB}
pspen_LDADD=./pslib/libpspen.la ${BLIB}

Svppen_SOURCES=${SEPPEN}
vppen_SOURCES=${NOSEPPEN}
Svppen_LDADD=./vplib/libvppen_sep.la ${BSLIB}
vppen_LDADD=./vplib/libvppen.la ${BLIB}

Sppmpen_SOURCES=${SEPPEN}
ppmpen_SOURCES=${NOSEPPEN}
Sppmpen_LDADD=./raslib/libraspen_sep.la ${PPM_LD} ${BSLIB}
ppmpen_LDADD=./raslib/libraspen.la ${PPM_LD} ${BLIB}


SUFFIXES = _SEP.c _SEP.o

_SEP.c_SEP.o:
	$(COMPILE) $(CF77DEFINES) -DSEP -c -o $@ $< 

LINK_NO_CASE:
	${TOUCH} ${addprefix ${bindir}/,Pspen${EXEEXT} Vppen${EXEEXT} Pmpen${EXEEXT} Xtpe${EXEEXT}n}
	${RM} ${addprefix ${bindir}/,Pspen${EXEEXT} Vppen${EXEEXT} Pmpen${EXEEXT} Xtpen${EXEEXT}}
	cd ${bindir} && @LN@ -s Spspen${EXEEXT} Pspen${EXEEXT}
	cd ${bindir} && @LN@ -s Svppen${EXEEXT} Vppen${EXEEXT}
	cd ${bindir} && @LN@ -s Sppmpen${EXEEXT} Pmpen${EXEEXT}
	cd ${bindir} && @LN@ -s Sxtpen${EXEEXT} Xtpen${EXEEXT}

RM_NO_CASE:
	${TOUCH} ${addprefix ${bindir}/,Pspen${EXEEXT} Vppen${EXEEXT} Pmpen${EXEEXT} Xtpen${EXEEXT}}
	${RM} ${addprefix ${bindir}/,Pspen${EXEEXT} Vppen${EXEEXT} Pmpen${EXEEXT} Xtpen${EXEEXT}}

install-data-local: @LINK_NO_CASE@

uninstall-local: @RM_NO_CASE@
