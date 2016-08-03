

bin_SCRIPTS = Stube vp_OverUnderAniso vp_SideBySideIso pstexpen \
vp_OverUnderIso vp_Unrotate tube vp_Overlay vp_Movie vp_SideBySideAniso \
vp_annotate Rasterize

LINK_NO_CASE:
	${TOUCH} ${addprefix ${bindir}/,Tube${EXEEXT}}
	${RM} ${addprefix ${bindir}/,Tube${EXEEXT}}
	cd ${bindir} && @LN_S@ -s Stube${EXEEXT} Tube${EXEEXT}

RM_NO_CASE:
	${TOUCH} ${addprefix ${bindir}/,Tube${EXEEXT}}
	${RM} ${addprefix ${bindir}/,Tube${EXEEXT}}

install-data-local: @LINK_NO_CASE@

uninstall-local: @RM_NO_CASE@


