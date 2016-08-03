EXTRA_DIST=build.py  tour.py make.py







install-data-local: 
	-mkdir -p  ${libdir}/python/SEP
	-rm -rf ${addprefix ${libdir}/python/SEP/, ${EXTRA_DIST}}
	cp ${EXTRA_DIST}  ${libdir}/python/SEP

uninstall-local: 
	-rm -rf ${addprefix ${libdir}/python/SEP/, ${EXTRA_DIST}}
