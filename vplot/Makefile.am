
ACLOCAL_AMFLAGS = -I m4

m4sources = m4/ac_check_ftype.m4 m4/ac_module_extensions_fc.m4 \
m4/find_sep_arch.m4 m4/make_gmake.m4 m4/sep_fc.m4 m4/sep_lib_defs.m4

SUBDIRS = include cfortran Docs libvplot util filters 

EXTRA_DIST = COPYRIGHT vplot-nosep.spec vplot-sep.spec LOCAL_CONFIG \
SEP_BUILD NOSEP_BUILD $(m4sources)

RPMDIR=/usr/src/redhat


rpms:
	cp ${top_builddir}/vplot-${VERSION}.tar.gz ${RPMDIR}/SOURCES
	cp ${top_builddir}/vplot-sep.spec ${top_builddir}/vplot-nosep.spec ${RPMDIR}/SPECS
	rpmbuild -ba ${RPMDIR}/SPECS/vplot-sep.spec
	rm -rf /usr/local/SEP/*
	rpmbuild -ba ${RPMDIR}/SPECS/vplot-nosep.spec
	gunzip vplot-${VERSION}.tar.gz
	rm -rf /usr/local/SEP/*


