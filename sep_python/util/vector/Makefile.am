EXTRA_DIST=math_base.py 









install-data-local: 
	-mkdir -p  ${libdir}/python/SEP
	-rm -rf ${addprefix ${libdir}/python/SEP/, ${EXTRA_DIST}}
	cp ${EXTRA_DIST}  ${libdir}/python/SEP

uninstall-local: 
	-rm -rf ${addprefix ${libdir}/python/SEP/, ${EXTRA_DIST}}
