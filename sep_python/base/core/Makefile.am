EXTRA_DIST=datapath.py __init__.py\
  parameter.py  util.py  paths.py  spawn.py  prog.py args.py rc.py \
  opt_base.py opt_none.py \
  flow.py  opt_prog.py  \
  stat_base.py stat_sep.py \
  sep_ff.py sepfile.py \
  log_base.py log.py opt_data.py
  
  









install-data-local: 
	
	-mkdir -p  ${libdir}/python/SEP
	-rm -rf ${addprefix ${libdir}/python/SEP/, ${EXTRA_DIST}}
	cp ${EXTRA_DIST}  ${libdir}/python/SEP

uninstall-local: 
	-rm -rf ${addprefix ${libdir}/python/SEP/, ${EXTRA_DIST}}
