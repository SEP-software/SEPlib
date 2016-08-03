
COPY_FILES=sep_old_external.h sep_pars_external.h \
sep3d.h sepcube.h prototypes.h sep_fortran.h seplib.h \
sep_main_external.h vplot.h glplot.h sepmath.h sepmathf.h \
sepvector.h sepvectorf.h sepfftf.h sepfft.h septravel.h sepvelan.h \
sepvelanf.h superset.h cfortran.h sepaux.h sepconvert.h \
sepfilterf.h sepfilter.h hwt.h mpi_sep.h sep3dc.h sulib.h sep_par.h\
sf_dip.h 
#sergey_rsf.h

MADE_FILES=segy.h su.h sitedef.h

INCLUDE_FILES = $(COPY_FILES) $(MADE_FILES)

EXTRA_DIST = $(COPY_FILES) sitedef.h.in SEP.aux.rules fortran.rules

bin_SCRIPTS = fullpath ratsep v_f90 sep_doc_it

install-data-local:
	$(mkinstalldirs) ${includedir}
	${CP} ${MADE_FILES} ${includedir}
	${CP} $(addprefix ${srcdir}/, ${COPY_FILES}) ${includedir}
	chmod 664 ${addprefix ${includedir}/, ${INCLUDE_FILES}}

uninstall-local:
	${TOUCH} ${addprefix ${includedir}/, ${INCLUDE_FILES}}
	${RM} ${addprefix ${includedir}/, ${INCLUDE_FILES}}
