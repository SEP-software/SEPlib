
bin_SCRIPTS = key-word Snoop
bin_PROGRAMS = fgrep3

EXTRA_PROGRAMS = fgrep3
EXTRA_DIST = DIRLIST SYNONYMS

fgrep3_SOURCES = fgrep3.c

install-data-local:
	$(mkinstalldirs) ${libdir}
	${CP} $(addprefix ${srcdir}/, ${EXTRA_DIST}) ${libdir}
	chmod 664 $(addprefix ${libdir}/, ${EXTRA_DIST})

uninstall-local:
	@TOUCH@ ${addprefix ${libdir}/, ${EXTRA_DIST_FILES} aa} 
	@RM@ ${addprefix ${libdir}/, ${EXTRA_DIST_FILES} aa} 
