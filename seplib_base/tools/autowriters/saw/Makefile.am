
#SCRIPTS_LOCAL = sawf90 cmsawf sawf90.awk cmsawf.awk

EXTRA_DIST = sawf.awk

bin_SCRIPTS = saw saw.awk sawf sawf90 cmsawf sawf90.awk cmsawf.awk 

bin_PROGRAMS = Lex.fort

Lex_fort_SOURCES = sawf.l
Lex_fort_LDADD = ${LEXLIB}

sawf90.awk:	sawf.awk
	${OCPP} ${DEFINES} -DF90 $< | @AWK@ 'NF>0' > $@
	
cmsawf.awk:	sawf.awk
	${OCPP} ${DEFINES} -DF90 $< | @AWK@ 'NF>0' > $@
	
saw.awk:	sawf.awk
	${OCPP} ${DEFINES} ${CF77DEFINES} $< | @AWK@ 'NF>0' > $@
	
sawf90:	sawf.csh
	sed -e s,AWKFILE,sawf90.awk,g $< | sed -e s,BINDIR,${bindir},g | \
	sed -e s,SAW,sawf90,g | sed -e s,RS,FS90,g | sed -e s,EXT,f90,g | \
	sed -e s,F77,f90,g \
	> $@ && chmod +x $@

cmsawf:	sawf.csh
	sed -e s,AWKFILE,cmsawf.awk,g $< | sed -e s,BINDIR,${bindir},g | \
	sed -e s,SAW,cmsawf,g | sed -e s,RS,fcm,g | sed -e s,EXT,fcm,g | \
	sed -e s,F77,cmf,g \
	> $@ && chmod +x $@

sawf:	sawf.csh
	sed -e s,AWKFILE,saw.awk,g $<| sed -e s,BINDIR,${bindir},g | \
	sed -e s,SAW,saw,g | sed -e s,RS,rs,g | sed -e s,EXT,f,g | \
	sed -e s,F77,f77,g \
	> $@ && chmod +x $@

saw:	sawf.csh
	sed -e s,AWKFILE,saw.awk,g $< | sed -e s,BINDIR,${bindir},g | \
	sed -e s,SAW,saw,g | sed -e s,RS,rs,g | sed -e s,EXT,f,g | \
	sed -e s,F77,f77,g \
	> $@ && chmod +x $@


clean-local:
	-rm -rf saw sawf90 sawf90.awk cmsawf sawf cmsawf.awk sawf.csh
