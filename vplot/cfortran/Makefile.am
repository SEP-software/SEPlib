
EXTRA_DIST = cfortran.doc cfortran.h

install-data-local:
	${CP} ${srcdir}/cfortran.h ${includedir}
	chmod 664 ${includedir}/cfortran.h

uninstall-local:	
	${TOUCH} ${includedir}/cfortran.h
	${RM} ${includedir}/cfortran.h
