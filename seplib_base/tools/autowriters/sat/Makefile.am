

EXTRA_DIST=satf.awk

EXTRA_PROGRAMS = sat.fort
 
bin_PROGRAMS = sat.fort
bin_SCRIPTS = sat sat.awk

sat_fort_SOURCES = sat.l
sat_fort_LDADD = ${LEXLIB}


sat:satf.csh
	sed -e s,AWKFILE,sat.awk,g $< | sed -e s,BINDIR,${bindir},g > $@

sat.awk:satf.awk
	${CPP} ${DEFINES} ${CFCDEFINES} $< | @AWK@ 'NF>0' > $@

clean-local:
	-rm -rf sat satf.csh
