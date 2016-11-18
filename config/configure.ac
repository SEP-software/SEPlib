
AC_PREREQ(2.57)

AC_INIT([sep-config],[8.0.1],[bob@sep.stanford.edu])

AC_CONFIG_SRCDIR([Makefile.am])
AC_CONFIG_HEADERS([include/sitedef.h])

AC_CANONICAL_TARGET

AM_INIT_AUTOMAKE([foreign 1.8 dist-bzip2])

dnl Avoid generating makefile rules to rebuild maintainer-only files by
dnl default. Maintainers may override this default and generate these
dnl makefile rules using the `--enable-maintainer-mode' configure option.
AM_MAINTAINER_MODE

dnl Disable shared library building
dnl AM_DISABLE_SHARED
dnl Libtool stuff check
dnl AM_PROG_LIBTOOL

AC_MSG_NOTICE([------------------------------------------])
AC_MSG_NOTICE([       Program Checks   ])
AC_MSG_NOTICE([------------------------------------------])
AC_PROG_CC(cc egcs gcc)
AC_PROG_FC(f90 pgf90 ifort ifc f95 xlf g95)
AC_PROG_MAKE_SET
AC_PATH_PROG(CSH, csh, csh)
MAKE_GMAKE
AC_PROG_INSTALL
AC_PATH_PROG(PERL,perl,no)
if test "${PERL}" = no; then
  echo "You must have perl (5.00+) to install SEPlib"
  exit 1;
else
 if ( eval "${PERL} -v | grep -v 5.001 |grep 5" ) ; then
    echo "Valid version of perl"
 else
    echo "Require perl version > 5.001"
    exit 1;
  fi
fi
FULLSRC="\$(strip \$(shell \${top_builddir}/include/fullpath \${srcdir}))"
AC_SUBST(FULLSRC)
#EXISTENCE AND LOCATIONS OF GENERIC UTILITIES
AC_PATH_PROG(LN, ln, ln)
AC_PATH_PROG(MV, mv, mv)
AC_PATH_PROG(RM, rm, rm)
AC_PATH_PROG(MKDIR, mkdir, mkdir)
AC_PATH_PROG(CP, cp, cp)
AC_PATH_PROG(CSH, csh, csh)
AC_PATH_PROG(SH, sh, sh)
AC_PATH_PROG(TOUCH, touch, touch)
AC_PROG_AWK
if test $AWK = "gawk" ; then
	AWK="gawk -W compat"
fi
AC_PATH_PROG(GHOSTVIEW, ghostview gv, \${SEPLIBDIR}/not_found.x ghostview)
AC_PATH_PROG(CAT, cat, \${SEPLIBDIR}/not_found.x cat)
AC_PATH_PROG(XV, xv, \${SEPLIBDIR}/not_found.x xv)
AC_PATH_PROG(TEST, test, \${SEPLIBDIR}/not_found.x test)
AC_PATH_PROG(PPM2GIF, ppmtogif, \${SEPLIBDIR}/not_found.x ppmtogif)
AC_PATH_PROG(GIF2PPM, giftopnm, \${SEPLIBDIR}/not_found.x giftopnm)
AC_PATH_PROG(ECHO, echo, \${SEPLIBDIR}/not_found.x echo)
AC_PATH_PROG(GTAR, tar, \${SEPLIBDIR}/not_found.x tar)
AC_PATH_PROG(DVIPS, dvips, \${SEPLIBDIR}/not_found.x dvips)
AC_PATH_PROG(PS2PDF, epstopdf, \${SEPLIBDIR}/not_found.x epstopdf)
AC_PATH_PROG(ACROREAD, acroread, \${SEPLIBDIR}/not_found.x acroread)
AC_PATH_PROG(XTEX, xtex, \${SEPLIBDIR}/not_found.x xtex)
AC_PATH_PROG(XDVI, xdvi, \${SEPLIBDIR}/not_found.x xdvi)

AC_MSG_NOTICE([------------------------------------------])
AC_MSG_NOTICE([       SEP Specific options   ])
AC_MSG_NOTICE([------------------------------------------])
AC_PREFIX_DEFAULT(/usr/local/SEP)
FIND_SEP_ARCH
AC_MSG_NOTICE([------------------------------------------])
AC_MSG_NOTICE([       Header files Checks   ])
AC_MSG_NOTICE([------------------------------------------])


AC_MSG_NOTICE([------------------------------------------])
AC_MSG_NOTICE([       Compiler characteristics Checks   ])
AC_MSG_NOTICE([------------------------------------------])

SEP_FC
if  test "${FC}" == no; then
   AC_MSG_NOTICE([ NO FORTRAN])
else
  AC_LANG_PUSH(Fortran)
  AC_FC_FREEFORM
fi
DEFINES="${DEFINES} -D\${SEP_ARCH}"
AC_SUBST(DEFINES)
OCPPFLAGS="${CPPFLAGS} ${DEFINES} "
CSOURCE="-DSOURCE='\"'\${FULLSRC}/\$(notdir \$<)'\"' ${X_CFLAGS}"
AC_SUBST(OCPPFLAGS)
AC_SUBST(CFLAGS)
FCMODSUFFIX=`echo "$FCMODEXT"| sed 's/\*\.//g'`
AC_SUBST(FCMODSUFFIX)
AC_SUBST(SUBDIRS)
AC_SUBST(bin_PROGRAMS)
AC_PROG_CPP

if test $SEP_ARCH = "MACOS" ; then
FPP="/usr/bin/cpp -P"
else
FPP="/lib/cpp"
fi
AC_SUBST(FPP)


OCLIBS="${LIBS}"
OFCLIBS="${FCLIBS}"
AC_SUBST(OCLIBS)
AC_SUBST(OFCLIBS)

SEP_LIB_DEFS

#WE WANT TO CREATE LOCAL SITE DEFINES
#MAKE FILE GENERATION

OCPPFLAGS="-I\${SEPINCDIR} ${CPPFLAGS}"
OFCFLAGS=" ${FCFLAGS} ${FCDEFINES} ${FCINCFLAG}\${SEPINCDIR}"
OFCDEFINES=${FCDEFINES}
AC_SUBST(OFCDEFINES)
FCFLAGS=" ${LOCFCFLAGS} ${FCFLAGS}"
AC_SUBST(OFCFLAGS)

OLDFLAGS="${LDFLAGS} -L\${SEPLIBDIR}"
OFCLDFLAGS="${FCLDFLAGS} -L\${SEPLIBDIR}"
OFCPFLAGS="${FCPFLAGS}"
FCPFLAGS="${FCPFLAGS} ${FCSOURCE} "
AC_SUBST(OFCPFLAGS)
AC_SUBST(OLDFLAGS)
AC_SUBST(OFCLDFLAGS)
AC_SUBST(OCPP)
LDFLAGS="${LDFLAGS} ${LOCLDFLAGS}"
F77LDFLAGS="${FCLDFLAGS} ${LOCLDFLAGS}"
FCLDFLAGS="${FCLDFLAGS} ${LOCLDFLAGS}"

AC_SUBST(LIBS)
AC_SUBST(bin_SCRIPTS)
AC_SUBST(AR_EXTRA)


AC_MSG_NOTICE([------------------------------------------])
AC_MSG_NOTICE([       Library function checks   ])
AC_MSG_NOTICE([------------------------------------------])

AC_MSG_NOTICE([------------------------------------------])
AC_MSG_NOTICE([       System service checks   ])
AC_MSG_NOTICE([------------------------------------------])

AC_MSG_NOTICE([------------------------------------------])
AC_MSG_NOTICE([       Set final variables   ])
AC_MSG_NOTICE([------------------------------------------])




########################################
###############UTILITIES################
########################################


#DOC RULE STUFF

dnl THE FILES WE ARE GOING TO CREATE


AC_CONFIG_FILES([Makefile include/Makefile])
AC_CONFIG_FILES([include/SEP.top include/SEP.generic.defs include/SEP.lib.defs
include/Doc.defs.top include/Prog.defs.compile])

AC_CONFIG_FILES([include/not_found:include/not_found.pl.in],[chmod +x include/not_found])
AC_CONFIG_FILES([include/CreateSSH:include/CreateSSH.pl.in],[chmod +x include/CreateSSH])
AC_CONFIG_FILES([include/Actify:include/Actify.pl.in],[chmod +x include/Actify])
AC_CONFIG_FILES([include/Latify:include/Latify.pl.in],[chmod +x include/Latify])
AC_CONFIG_FILES([include/latex2dvi:include/latex2dvi.pl.in],[chmod +x include/latex2dvi])
AC_CONFIG_FILES([include/latex2pdf:include/latex2pdf.pl.in],[chmod +x include/latex2pdf])

AC_OUTPUT
