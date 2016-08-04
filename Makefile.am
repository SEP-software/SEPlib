
ACLOCAL_AMFLAGS = -I m4

m4sources = m4/ac_check_ftype.m4 m4/find_sep_arch.m4 m4/sep_fc.m4 \
m4/ac_module_extensions_fc.m4 m4/make_gmake.m4

examples = examples/c/Makefile examples/c/scale_it.c examples/c/scaled.H \
examples/saw examples/saw/Makefile examples/saw/README examples/saw/scale_it.rs \
examples/Makefile examples/README examples/unscaled.HH examples/c_calls_f \
examples/c_calls_f/Makefile examples/c_calls_f/README \
examples/c_calls_f/scale_it.c examples/c_calls_f/scale_trace.f \
examples/c_calls_f/scaled.H examples/f_calls_c examples/f_calls_c/Makefile \
examples/f_calls_c/scale_it.f90 examples/f_calls_c/scale_trace.c \
examples/fortran77 examples/fortran77/Makefile examples/fortran77/README \
examples/fortran77/scale_it.f examples/fortran90 examples/fortran90/Makefile \
examples/fortran90/scale_it.f90 examples/ratfor90 examples/ratfor90/Makefile \
examples/ratfor90/scale_it.rs90 examples/sep2df90 examples/sep2df90/Makefile \
examples/sep2df90/scale_it.f90


SUBDIRS = include docs config ratfor90 seplib_base/include seplib_base/tools seplib_base/lib/corelibs vplot seplib_base seplib_prog sep_python
#seplib_java  interact

DIST_DIRS = seplib_prog seplib_local vplot ratfor90

EXTRA_DIST = MAKERULES COPYRIGHT CONVERTING_OLD_SEPLIB ENVIRONMENT \
seplib-distr.spec seplib-local.spec RPM_BUILD_LOCAL RPM_BUILD_DISTR \
LOCAL_CONFIG TO_DO Recurs_pod.pl NOTE_AUTOMAKE $(m4sources) $(examples)

CONFIG_DIRS = config ratfor90 seplib_base vplot seplib_prog interact \
sep_python seplib_java

update:
	@echo Updating config tools...
	@for d in $(CONFIG_DIRS) ; do \
		echo cd $$d && cd $$d && autoreconf -vif && cd .. || exit 1; \
		done
	@autoreconf -vif
	@echo All config tools updated.


uninstall-local:
	${TOUCH} ${addprefix ${includedir}/, junk.${F90MODSUFFIX}}
	${RM} ${wildcard ${addprefix ${includedir}/, *.${F90MODSUFFIX}}}
	${RM} -r examples
	cd @PROG_DIR@; ${MAKE} uninstall	
	cd @BASE_DIR@; ${MAKE} uninstall	
	cd @RATFOR_DIR@; ${MAKE} uninstall	
	cd @RICK_DIR@; ${MAKE} uninstall	
	cd @VPLOT_DIR@; ${MAKE} uninstall	
	cd @CONFIG_DIR@; ${MAKE} uninstall	


#do on kana preferably
stage1: dist


RPM=/usr/src/redhat
FTP=/net/sepwww/ftpdisk/ftp/pub/sep-distr/
#do on linux machine
stage2:	rpms stage1


BRPMS=${RPM}/RPMS/i386/seplib-distr-${VERSION}.i386.rpm \
	${RPM}/RPMS/i386/seplib-local-${VERSION}.i386.rpm 

SRPMS=${RPM}/SRPMS/seplib-distr-${VERSION}.rpm \
	${RPM}/SRPMS/seplib-local-${VERSION}.rpm 

	

stage3: seplib-distr-${VERSION}.i386.rpm
	mv seplib-distr-${VERSION}.i386.rpm seplib-local-${VERSION}.i386.rpm \
		seplib-distr-${VERSION}.rpm seplib-local-${VERSION}.rpm ${FTP}
	

.PHONY : FORCE
FORCE: ;
rpm-local: FORCE seplib-distr.spec seplib-local.spec
	cd ratfor90;make rpm
	cd seplib_base; make rpms
	cd vplot; make rpms
	cd seplib_prog; make rpms
	cd interact; make rpms
	cd config; make rpm
#	cd sep_python; make rpm

rpms:	 FORCE rpm-local seplib-distr.spec seplib-local.spec
	cp seplib-${VERSION}.tar.gz ${RPM}/SOURCES
	cp ${srcdir}/seplib-distr.spec ${srcdir}/seplib-local.spec ${RPM}/SPECS
	rpmbpuild -ba ${RPM}/SPECS/seplib-local.spec 
	rpmbpuild -ba ${RPM}/SPECS/seplib-distr.spec 
	mv ${BRPMS} ${SRPMS} .

