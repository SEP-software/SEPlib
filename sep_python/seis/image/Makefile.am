EXTRA_DIST=lloyd.py off2ang.py wei.py wei_op.py wei_off_mig.py wei_off_model.py\
                  wei_ang.py wei_ang_op.py wei_ang_mig.py wei_ang_model.py









install-data-local: 
	
	-mkdir -p  ${libdir}/python/SEP
	-rm -rf ${addprefix ${libdir}/python/SEP/, ${EXTRA_DIST}}
	cp ${EXTRA_DIST}  ${libdir}/python/SEP

uninstall-local: 
	-rm -rf ${addprefix ${libdir}/python/SEP/, ${EXTRA_DIST}}
