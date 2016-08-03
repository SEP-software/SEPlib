AC_PREREQ(2.57)

      AC_INIT([vplot],[8.0.1],[bob@sep.stanford.edu])

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
AC_PROG_FC(f90 pgf90 ifort ifc f95 xlf g95)
MAKE_GMAKE
AC_PROG_MAKE_SET
AC_PROG_INSTALL
AC_PROG_FC(f90 pgf90 ifort ifc f95 xlf)
AC_PATH_PROG(LN, ln, ln)
AC_PATH_PROG(MV, mv, mv)
AC_PATH_PROG(RM, rm, rm)
AC_PATH_PROG(MKDIR, mkdir, mkdir)
AC_PATH_PROG(CP, cp, cp)
AC_PATH_PROG(CSH, csh, csh)
AC_PATH_PROG(SH, sh, sh)
AC_PATH_PROG(PERL, perl, perl)
AC_PATH_PROG(TOUCH, touch, touch)
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



AC_MSG_NOTICE([------------------------------------------])
AC_MSG_NOTICE([       SEP Specific options])
AC_MSG_NOTICE([------------------------------------------])
FULLSRC="\$(strip \$(shell \${top_builddir}/include/fullpath \${srcdir}))"
AC_SUBST(FULLSRC)
FIND_SEP_ARCH
AC_SUBST(SEP_ARCH)
AC_MSG_CHECKING([for SEP distribution type])
COMPILE_LEVEL="SEP"
SEP_FC
AC_ARG_WITH(sep,[;
Install local:

  --with-sep            Compile SEP versions of vplot software
  --without-sep         Do not compile sep software (default)],
  ,[with_sep="yes"])
AC_SUBST(COMPILE_LEVEL)
AC_MSG_RESULT([$COMPILE_LEVEL])



AC_MSG_CHECKING([whether compiling the entire SEPlib package])
FULLSEP=yes
AC_ARG_WITH(fullsep,[;
  --with-fullsep       Installing full SEPlib package
  --without-fullsep    Installing individual SEP packages],
  [FULLSEP="yes"])
AC_SUBST(FULLSEP)
AC_MSG_RESULT([$FULLSEP])
#C COMPILER STUFF
if test -z "$VPLOT_FONT_DIR" ; then
VPLOT_FONT_DIR="\${includedir}/"
fi
AC_SUBST(VPLOT_FONT_DIR)

DEFINES="${DEFINES} -D${SEP_ARCH} -DVPLOT_FONT_DIR='\"\${VPLOT_FONT_DIR}\"'"
AC_SUBST(DEFINES)


AC_MSG_NOTICE([------------------------------------------])
AC_MSG_NOTICE([       Header files Checks   ])
AC_MSG_NOTICE([------------------------------------------])
AC_C_BIGENDIAN
AC_FUNC_ALLOCA
dnl Checks for programs.

dnl Checks for header files.
AC_PATH_X
AC_PATH_XTRA
AC_HEADER_DIRENT
AC_HEADER_STDC
AC_HEADER_SYS_WAIT
AC_CHECK_HEADERS(fcntl.h limits.h sgtty.h sys/file.h sys/ioctl.h sys/time.h termio.h unistd.h  sys/types.h  sys/socket.h rpc/rpc.h rpc/types.h sys/utsname.h)
AC_CHECK_HEADERS(errno.h stdlib.h sys/stat.h)
AC_C_CONST
AC_TYPE_OFF_T
AC_TYPE_PID_T
AC_TYPE_SIZE_T
AC_STRUCT_ST_RDEV
AC_HEADER_TIME
AC_STRUCT_TM
AC_TYPE_UID_T

AC_MSG_NOTICE([------------------------------------------])
AC_MSG_NOTICE([       Compiler characteristics Checks   ])
AC_MSG_NOTICE([------------------------------------------])
OCPP="/lib/cpp -P"

AC_MSG_NOTICE([------------------------------------------])
AC_MSG_NOTICE([       Library function checks   ])
AC_MSG_NOTICE([------------------------------------------])

LIBS="-lm ${LIBS}"
dnl Checks for library functions.
AC_FUNC_MEMCMP
AC_FUNC_SETVBUF_REVERSED
AC_TYPE_SIGNAL
AC_FUNC_FORK([])
AC_FUNC_VPRINTF
AC_CHECK_FUNCS(ftime getcwd gethostname gettimeofday re_comp regcmp regcomp socket strcspn strdup strerror strstr uname)
AC_SUBST(LEXLIB)



AC_MSG_NOTICE([------------------------------------------])
AC_MSG_NOTICE([       System service checks   ])
AC_MSG_NOTICE([------------------------------------------])

AC_ISC_POSIX
AC_PATH_XTRA


CFLAGS="${CFLAGS} ${X_CFLAGS} ${CFCDEFINES} "


AC_MSG_NOTICE([------------------------------------------])
AC_MSG_NOTICE([       Final Setup ])
AC_MSG_NOTICE([------------------------------------------])

SUBDIRS="\${CDIR_DISTR}"
SEP_PROGRAMS="\${CPROG_DISTR}"
bin_SCRIPTS="\${SCRIPTS_DISTR}"
lib_LIBRARIES="\${CLIB_DISTR}"

AC_ARG_WITH(relative,[;
  --with-relative       Directory containing binaries])

AC_MSG_CHECKING([for relative compiling])
if test x$with_relative = x ; then
RELATIVE="BOOP"
else
RELATIVE=$with_relative
fi

if test $RELATIVE = "BOOP" ; then
if test "$0" = ../configure; then
	AC_MSG_RESULT([yes])
  back="../"
  RELATIVE=`pwd| sed -e 's/.*\///'`
  basedir="\${top_srcdir}/../seplib_base/${RELATIVE}"
  sepprogdir="\${top_srcdir}/../seplib_prog/${RELATIVE}"
else
	AC_MSG_RESULT([no])
  back="./"
  basedir="\${top_srcdir}/../seplib_base"
  sepprogdir="\${top_srcdir}/../seplib_prog"
fi
else
if test ${RELATIVE} = "NONE" ; then
	AC_MSG_RESULT([no])
  back=".";
  basedir="\${top_srcdir}/../seplib_base"
  sepprogdir="\${top_srcdir}/../seplib_prog"
else
	AC_MSG_RESULT([yes])
  back=".."
  basedir="\${top_srcdir}/../seplib_base/${RELATIVE}"
  sepprogdir="\${top_srcdir}/../seplib_prog/${RELATIVE}"
fi
fi
AC_SUBST(basedir)
AC_SUBST(sepprogdir)

CPPFLAGS="${CPPFLAGS} ${DEFINES} -I\${top_srcdir}/include"

if test $with_sep = "yes" ; then
if test -d ${back}/../seplib_base ; then
if test -d ${back}/../seplib_prog ; then
	CPPFLAGS="${CPPFLAGS} -I\${basedir}/include -I\${sepprogdir}/include -I\${top_srcdir}/../seplib_base/include -I\${top_srcdir}/../seplib_prog/include "
	LDFLAGS="${LDFLAGS} -L\${basedir}/lib/corelibs/sep  "
	SEP_PROGRAMS="$SEP_PROGRAMS \${CPROG_SEP}"
	bin_SCRIPTS="$bin_SCRIPTS \${SCRIPTS_SEP}"
	SUBDIRS="$SUBDIRS \${CDIR_SEP}"
	lib_LIBRARIES="$lib_LIBRARIES \${CLIB_SEP}"
else
 echo "Specified --with-sep but can't find seplib_prog directory"
 exit 1;
fi
else
 echo "Specified --with-sep but can't find seplib_base directory"
 exit 1;
fi
else
AC_CHECK_HEADER(seplib.h,[sepok=yes],[sepok=no])
#AC_CHECK_HEADERS(seplib.h sep.main,[sepok=yes],[sepok=no])
if test $sepok = "no" ; then
 echo "CPPFLAGS " $CPPFLAGS
 echo "Specified --with-sep but can't find seplib.h sep.main in include path"
 exit 1;
fi
AC_CHECK_LIB([sep],[main],[dosep=yes],[dosep=no],[])ac_cv_lib_sep=ac_cv_lib_sep_main

if test $sepok = "no" ; then
	echo "LDFLAGS " $LDFLAGS
 echo "Specified --with-sep but can't find libsep.a"
 exit 1;
fi
fi

AC_CHECK_LIB([X11],[XOpenDisplay])
AC_CHECK_LIB([Xt],[XtOpenDisplay])
AC_CHECK_LIB([Xaw], [XawDialogGetValueString])

AC_SUBST(LIBS)
AC_SUBST(LDFLAGS)
AC_SUBST(bin_SCRIPTS)
AC_SUBST(SUBDIRS)
AC_SUBST(SEP_PROGRAMS)
bin_PROGRAMS="\${addsuffix \${EXEEXT}, \${SEP_PROGRAMS}}"
AC_SUBST(bin_PROGRAMS)




########################################
###############UTILITIES################
########################################

#EXISTENCE AND LOCATIONS OF GENERIC UTILITIES


SEPLIB="../seplib_base/lib/corelibs/sep/libsep.la"
AC_SUBST(SEPLIB)
VPLOT="${abs_top_builddir}/libvplot/libvplot.la "
AC_SUBST(VPLOT)
VPLOTF="${abs_top_builddir}/libvplot/libvplotf.la ${abs_top_builddir}/libvplot/libvplot.la "
AC_SUBST(VPLOTF)
VPLOTF90="${abs_top_builddir}/libvplotf90.la ${abs_top_builddir}/libvplot.la "
AC_SUBST(VPLOTF90)
AC_SUBST(CFCDEFINES)
if test -z "$PPM_LD"; then
	AC_CHECK_LIB(ppm, main,[HAVE_PPM=yes;
	AC_DEFINE([HAVE_PPM],, [Define if having ppm])],[HAVE_PPM=no],-lpgm -lpbm)
if test "${HAVE_PPM}" = no; then
	AC_CHECK_LIB(netpbm, main,[HAVE_PPM=yes;
	AC_DEFINE([HAVE_PPM],, [Define if having ppm])],[HAVE_PPM=no])
	PPM_LD="-lnetpbm"
else
	PPM_LD="-lppm -lpgm -lpbm "
fi
else
HAVE_PPM="yes"
AC_DEFINE([HAVE_PPM],, [Define if having ppm])
fi
if test "${HAVE_PPM}" = no; then
	PPM_LD=""
fi
AC_SUBST(PPM_LD)
AC_SUBST(PPM_FLAGS)
AC_SUBST(lib_LIBRARIES)

if test ${SEP_ARCH} = "MACOS" ; then
LINK_NO_CASE=""
RM_NO_CASE=""
else
if test ${SEP_ARCH} = "CYGWIN" ; then
LINK_NO_CASE=""
RM_NO_CASE=""
else
  LINK_NO_CASE="LINK_NO_CASE"
  RM_NO_CASE="LINK_NO_CASE"
fi
fi
AC_SUBST(LINK_NO_CASE)
AC_SUBST(RM_NO_CASE)


dnl THE FILES WE ARE GOING TO CREATE



AC_CONFIG_FILES([Makefile include/Makefile cfortran/Makefile libvplot/Makefile
Docs/Makefile util/Makefile util/Debug/Makefile util/shells/Makefile filters/Makefile
filters/include/Makefile filters/vplotfonts/Makefile filters/genlib/Makefile
filters/utilities/Makefile filters/loclib/Makefile filters/tseplib/Makefile
filters/xtlib/Makefile filters/pslib/Makefile filters/vplib/Makefile
filters/raslib/Makefile])


AC_CONFIG_FILES([include/fullpath:include/fullpath.csh.in],[chmod +x include/fullpath])
AC_CONFIG_FILES([util/shells/Stube],[chmod +x util/shells/Stube])
AC_CONFIG_FILES([util/shells/tube],[chmod +x util/shells/tube])
AC_CONFIG_FILES([util/shells/pstexpen],[chmod +x util/shells/pstexpen])
AC_CONFIG_FILES([util/shells/vp_Movie],[chmod +x util/shells/vp_Movie])
AC_CONFIG_FILES([util/shells/Rasterize],[chmod +x util/shells/Rasterize])
AC_CONFIG_FILES([util/shells/vp_OverUnderAniso],[chmod +x util/shells/vp_OverUnderAniso])
AC_CONFIG_FILES([util/shells/vp_OverUnderIso],[chmod +x util/shells/vp_OverUnderIso])
AC_CONFIG_FILES([util/shells/vp_Overlay],[chmod +x util/shells/vp_Overlay])
AC_CONFIG_FILES([util/shells/vp_SideBySideAniso],[chmod +x util/shells/vp_SideBySideAniso])
AC_CONFIG_FILES([util/shells/vp_SideBySideIso],[chmod +x util/shells/vp_SideBySideIso])
AC_CONFIG_FILES([util/shells/vp_Unrotate],[chmod +x util/shells/vp_Unrotate])
AC_CONFIG_FILES([util/shells/vp_annotate],[chmod +x util/shells/vp_annotate])


AC_OUTPUT

