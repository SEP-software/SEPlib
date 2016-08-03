
COPY_FILES=sep.startup sep.wrapup sep.main 

MADE_FILES=sitedef.h
INCLUDE_FILES=${COPY_FILES} ${MADE_FILES}

EXTRA_DIST = ${COPY_FILES} sitedef.h.in SEP.aux.rules fortran.rules


bin_SCRIPTS = fullpath


install-data-local:
	$(mkinstalldirs) ${includedir}
	${CP} ${MADE_FILES} ${includedir}
	${CP} $(addprefix ${srcdir}/, ${COPY_FILES}) ${includedir}
	chmod 664 ${addprefix ${includedir}/, ${INCLUDE_FILES}}

uninstall-local:
	${TOUCH} ${addprefix ${includedir}/, ${INCLUDE_FILES}}
	${RM} ${addprefix ${includedir}/, ${INCLUDE_FILES}}
