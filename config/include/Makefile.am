
COPY_FILES = SEP.generic.defs SEP.top Prog.defs.compile SEP.lib.defs \
Doc.defs.top 

EXTRA_DIST = Prog.rules.C SEP.idoc.rules Prog.rules.C++ SEP.ifdef \
Dir.defs.bottom Doc.defs.bottom Prog.rules.F77 SEP.local.defs \
Prog.rules.F90 SEP.local.rules Doc.rules.action Prog.rules.bottom \
SEP.machine.type Doc.rules.book Prog.rules.depend SEP.obj.rules \
Doc.rules.clean Prog.rules.general SEP.overide.defaults Doc.rules.fig \
Prog.rules.java SEP.prog.rules Doc.rules.html Prog.rules.lib SEP.site.defs \
Doc.rules.idoc Prog.rules.shell Doc.rules.test README SEP.bottom \
SEP.distr.bottom SEP.distr.defs SEP.distr.dir Prg.rules.lib SEP.distr.rules \
sepweb.top SEP.distr.top Prog.defs.top septex.tar septex.pl sepbook.pl


TOTAL = ${EXTRA_DIST} ${COPY_FILES}

bin_SCRIPTS=not_found CreateSSH Actify Latify latex2dvi latex2pdf

SHARE=${prefix}/share

install-data-local:
	$(mkinstalldirs) ${includedir}
	$(mkinstalldirs) ${SHARE}
	${CP} $(addprefix ${srcdir}/, septex.pl sepbook.pl septex.tar) ${SHARE}
	${CP} ${COPY_FILES} ${includedir}
	${CP} $(addprefix ${srcdir}/, ${EXTRA_DIST}) ${includedir}
	chmod 664 ${addprefix ${includedir}/, ${TOTAL}}

uninstall-local:
	${TOUCH} ${addprefix ${includedir}/, ${TOTAL}}
	${RM} ${addprefix ${includedir}/, ${TOTAL}}

