
ACLOCAL_AMFLAGS = -I m4

m4sources = m4/ac_check_ftype.m4 m4/ac_module_extensions_fc.m4 \
m4/find_sep_arch.m4 m4/make_gmake.m4 m4/sep_fc.m4 m4/sep_lib_defs.m4 

SUBDIRS = include util seis converters sep_graphics

EXTRA_DIST = COPYRIGHT DIST_BUILD LOCAL_CONFIG LOCAL_BUILD \
seplib_prog-local.spec seplib_prog-dist.spec $(m4sources)

RPMDIR = /usr/src/redhat

rpms: dist
	cp ${top_builddir}/seplib_prog-${VERSION}.tar.gz ${RPMDIR}/SOURCES
	cp ${top_builddir}/seplib_prog-local.spec ${top_builddir}/seplib_prog-dist.spec ${RPMDIR}/SPECS
	rpmbuild -ba ${RPMDIR}/SPECS/seplib_prog-local.spec
	rm -rf /usr/local/SEP/*
	rpmbuild -ba ${RPMDIR}/SPECS/seplib_prog-dist.spec
	rm -rf /usr/local/SEP/*

.PHONY : FORCE
FORCE: ;
