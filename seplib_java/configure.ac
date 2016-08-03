AC_PREREQ(2.57)

AC_INIT([seplib-java],[8.0.1],[stew@sep.stanford.edu])

AC_CONFIG_SRCDIR([Makefile.am])
AC_CONFIG_HEADERS([include/sitedef.h])

AC_CANONICAL_TARGET

AM_INIT_AUTOMAKE([foreign 1.8 dist-bzip2])

dnl Avoid generating makefile rules to rebuild maintainer-only files by
dnl default. Maintainers may override this default and generate these
dnl makefile rules using the `--enable-maintainer-mode' configure option.
AM_MAINTAINER_MODE

dnl Disable shared library building
AM_DISABLE_SHARED
dnl Libtool stuff check
AM_PROG_LIBTOOL

AC_MSG_NOTICE([------------------------------------------])
AC_MSG_NOTICE([       Program Checks])
AC_MSG_NOTICE([------------------------------------------])

AC_PROG_CC(cc egcs gcc)

AC_PROG_MAKE_SET
MAKE_GMAKE
AC_PATH_PROG(LN, ln, ln)
AC_PATH_PROG(MV, mv, mv)
AC_PATH_PROG(RM, rm, rm)
AC_PATH_PROG(MKDIR, mkdir, mkdir)
AC_PATH_PROG(CP, cp, cp)
AC_PATH_PROG(CSH, csh, csh)
AC_PATH_PROG(SH, sh, sh)
AC_PATH_PROG(TOUCH, touch, touch)
AC_PROG_INSTALL
AC_PROG_AWK
if test $AWK = "gawk" ; then
  AWK="gawk -W compat"
fi

AM_PROG_LEX
if test ${LEX} = "flex" ; then
  LEX="flex -l"
  AC_DEFINE([FLEX],,[Define if using flex])
fi
AC_PROG_LN_S

AC_PATH_PROG(PODTEXT, pod2text, less)
AC_SUBST(PODTEXT)
AC_MSG_NOTICE([------------------------------------------])
AC_MSG_NOTICE([       SEP Specific options   ])
AC_MSG_NOTICE([------------------------------------------])

AC_PREFIX_DEFAULT(/usr/local/SEP)

AC_ARG_WITH(relative,[
  --with-relative       Directory containing binaries])

AC_MSG_CHECKING([for relative compiling])
if test x$with_relative = x ; then
RELATIVE="BOOP"
BASE="."
else
RELATIVE=$with_relative
BASE=".."
fi

if test ${RELATIVE} = "BOOP" ; then
if test "$0" = ../configure; then
  AC_MSG_RESULT([yes])
	back=1
	RELATIVE=`pwd| sed -e 's/.*\///'`
	basedir="\${top_srcdir}/../seplib_base/${RELATIVE}"
	vplotdir="\${top_srcdir}/../vplot/${RELATIVE}"
else
  AC_MSG_RESULT([no])
	back=0;
	basedir="\${top_srcdir}/../seplib_base"
	vplotdir="\${top_srcdir}/../vplot"
fi
else
if test ${RELATIVE} = "NONE" ; then
  AC_MSG_RESULT([no])
  back=0;
  basedir="\${top_srcdir}/../seplib_base"
  vplotdir="\${top_srcdir}/../vplot"
else
  AC_MSG_RESULT([yes])
  back=1
  basedir="\${top_srcdir}/../seplib_base/${RELATIVE}"
  vplotdir="\${top_srcdir}/../vplot/${RELATIVE}"
fi
fi

AC_SUBST(basedir)
AC_SUBST(vplotdir)
FULLSRC="\$(strip \$(shell \${top_builddir}/include/fullpath \${srcdir}))"
AC_SUBST(FULLSRC)

HAVE_MAN_FMT="yes"
AC_MSG_NOTICE([Setting up manual support])
AM_CONDITIONAL(HAVE_MAN_FMT, test ${HAVE_MAN_FMT} = "yes")
if test -z "$DEFAULT_DOC_PATH"; then
if test "$0" = ../configure; then
DEFAULT_DOC_PATH=`cd ..;pwd`
else
DEFAULT_DOC_PATH=`pwd`
fi
fi
AC_SUBST(DEFAULT_DOC_PATH)

AC_MSG_CHECKING([Do no-case linking])
if test ${SEP_ARCH} = "MACOS" ; then
AC_MSG_RESULT([no])
LINK_NO_CASE=""
RM_NO_CASE=""
else
if test ${SEP_ARCH} = "CYGWIN" ; then
AC_MSG_RESULT([no])
LINK_NO_CASE=""
RM_NO_CASE=""
else
  AC_MSG_RESULT([yes])
  LINK_NO_CASE="LINK_NO_CASE"
  RM_NO_CASE="LINK_NO_CASE"
fi
fi
AC_SUBST(LINK_NO_CASE)
AC_SUBST(RM_NO_CASE)

SEP_LIB_DEFS

AC_MSG_NOTICE([------------------------------------------])
AC_MSG_NOTICE([       Header files Checks   ])
AC_MSG_NOTICE([------------------------------------------])


AC_MSG_NOTICE([------------------------------------------])
AC_MSG_NOTICE([       Compiler characteristics Checks   ])
AC_MSG_NOTICE([------------------------------------------])

if test -z "${SEPDOCIT}" ; then
SEPDOCIT="${basedir}/include/sep_doc_it"
else
echo "SEPDOCIT set"
fi
AC_SUBST(SEPDOCIT)

AC_MSG_NOTICE([------------------------------------------])
AC_MSG_NOTICE([       Library function checks   ])
AC_MSG_NOTICE([------------------------------------------])
AC_CHECK_LIB(fl,yywrap,LEXLIB=-lfl,[echo " "],-lc)
AC_CHECK_LIB(l,yywrap,LEXLIB=-ll,[echo " "],-lc)

AC_MSG_NOTICE([------------------------------------------])
AC_MSG_NOTICE([       System service checks   ])
AC_MSG_NOTICE([------------------------------------------])
AC_ISC_POSIX
AC_SYS_LARGEFILE

AC_MSG_NOTICE([------------------------------------------])
AC_MSG_NOTICE([       Set final variables   ])
AC_MSG_NOTICE([------------------------------------------])


DEFINES="${DEFINES} -D${SEP_ARCH}"
AC_SUBST(DEFINES)
CPPFLAGS="${CPPFLAGS} ${DEFINES} "
CSOURCE="-DSOURCE='\"'\${FULLSRC}/\$(notdir \$<)'\"' ${X_CFLAGS}"


LDFLAGS="${LOCLDFLAGS} -L${basedir}/lib/corelibs/sep -L${basedir}/lib/corelibs/sep3d -L${basedir}/lib/corelibs/superset -L${vplotdir}/libvplot -L${basedir}/lib/graphics/glplot -L${basedir}/lib/class/gee -L${basedir}/lib/class/util -L${basedir}/lib/util/math -L${basedir}/lib/util/sepaux -L${basedir}/lib/util/fft -L${basedir}/lib/util/par -L${basedir}/lib/util/vector -L${basedir}/lib/util/convert -L${basedir}/lib/seis/travel -L${basedir}/lib/seis/velan -L${basedir}/lib/seis/filter -L${basedir}/lib/seis/image -L${basedir}/lib/seis/wei -L${basedir}/lib/seis/dip -L${basedir}/lib/util/cwp -L${basedir}/lib/seis/model "

AC_SUBST(LDFLAGS)

CPPFLAGS="${CPPFLAGS} -I\${top_srcdir}/include -I\${top_builddir}/include -I\${basedir}/include -I\${top_srcdir}/../seplib_base/include -I\${top_srcdir}/../vplot/include ${X_CFLAGS} ${SUINCLUDES} ${CSOURCE}"

AC_CONFIG_FILES([Makefile include/Makefile 
lib/Makefile
main/Makefile
doc/Makefile])

AC_OUTPUT
