
COPY_FILES = vplot.h prototypes.h


EXTRA_DIST = ${COPY_FILES} sitedef.h.in SEP.aux.rules
INCLUDE_FILES = ${COPY_FILES}


bin_SCRIPTS = fullpath


install-data-local:
	$(mkinstalldirs) ${includedir}
	${CP} ${srcdir}/vplot.h ${includedir}
	chmod 664 ${includedir}/vplot.h


uninstall-local:
	${TOUCH} ${addprefix ${includedir}/, vplot.h}
	${RM} ${addprefix ${includedir}/, vplot.h}
