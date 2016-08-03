
EXTRA_DIST = ratfor90.spec.in

bin_SCRIPTS = ratfor90

RPMDIR = /usr/src/redhat

rpm:dist
	cp ${top_builddir}/ratfor90-${VERSION}.tar.gz ${RPMDIR}/SOURCES
	cp ${top_builddir}/ratfor90.spec ${RPMDIR}/SPECS
	rpmbuild -ba ${RPMDIR}/SPECS/ratfor90.spec
	gunzip ratfor90-${VERSION}.tar.gz
	
