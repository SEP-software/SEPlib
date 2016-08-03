
ACLOCAL_AMFLAGS = -I m4

m4sources = m4/ac_check_ftype.m4 m4/ac_module_extensions_fc.m4 \
m4/find_sep_arch.m4 m4/make_gmake.m4 m4/sep_fc.m4 m4/sep_lib_defs.m4 \
m4/swig.m4 m4/python_devel.m4

SUBDIRS = include tools lib

EXTRA_DIST = COPYRIGHT seplib_base-local.spec seplib_base-dist.spec \
DIST_BUILD LOCAL_BUILD LOCAL_CONFIG $(m4sources)

RPMDIR=/usr/src/redhat


rpms: dist
	cp ${top_builddir}/seplib_base-${VERSION}.tar.gz ${RPMDIR}/SOURCES
	cp ${top_builddir}/seplib_base-local.spec ${top_builddir}/seplib_base-dist.spec ${RPMDIR}/SPECS
	rpmbuild -ba ${RPMDIR}/SPECS/seplib_base-local.spec
	rm -rf /usr/local/SEP/*
	rpmbuild -ba ${RPMDIR}/SPECS/seplib_base-dist.spec
	rm -rf /usr/local/SEP/*

uninstall-local:
	-rm -rf ${wildcard ${addprefix ${includedir}/, *.${FCMODSUFFIX}}}
	-rm -rf examples

PHONY:FORCE
FORCE: ;
