
AC_PREREQ(2.57)

AC_INIT([rick-sep],[8.0.1],[bob@sep.stanford.edu])

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
AC_PROG_CXX
AC_PROG_MAKE_SET
AC_PATH_PROG(CSH, csh, csh)
MAKE_GMAKE

AC_PATH_PROG(PERL,perl,no)
# Check for required Qt 4 framework
AC_ARG_WITH(qt, AC_HELP_STRING([--with-qt=DIR],
		[Qt 4 toolkit location]))
if test -n "$with_qt"; then
	QMAKE="$with_qt/bin/qmake"
	if ! test -x $QMAKE; then
		AC_MSG_WARN([$QMAKE not found.])
		QMAKE="no"
	fi
else
	AC_CHECK_PROGS(QMAKE,[qmake-qt4 qmake4 qmake])
fi
if test -n "$QMAKE"; then
	AC_MSG_CHECKING([Qt toolkit version])
	if test -n "$QMAKE" && ! ($QMAKE -v | grep -q "[Qt version 4[.][123456789]]"); then
		AC_MSG_RESULT([wrong version.])
		QMAKE="no"
	else
		AC_MSG_RESULT([correct (version 4.1 or later).])
	fi
fi
AM_CONDITIONAL([HAVE_QT],test  x"${QMAKE}" != x"no")
if test  x"${QMAKE}" = x"no"; then
	AC_MSG_RESULT([qt_cube requires Qt toolkit version 4.1 or later.
		Please specify its location via '--with-qt=DIR',
		or see http://www.trolltech.com/ to obtain it. ])
fi

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

AC_MSG_NOTICE([------------------------------------------])
AC_MSG_NOTICE([       SEP Specific options])
AC_MSG_NOTICE([------------------------------------------])

AC_PREFIX_DEFAULT(/usr/local/SEP)
FIND_SEP_ARCH
COMPILE_LEVEL="DISTR"


with_sep=yes
AC_ARG_WITH(sep,
AS_HELP_STRING([--with-sep],[Install SEP version]))


AC_ARG_WITH(su,
AS_HELP_STRING([--with-su=DIR],[Install SU compatibility option]))

if test x$with_su = xyes ; then
  AC_MSG_ERROR([
*** Directory must be specified for --with-su])
fi



if test x$with_su = x ; then
	echo "Not installing SU support"
else
  if test x$with_sep = xyes ; then
    AC_MSG_NOTICE([Installing with SEP, SU disabled])
    with_su=
  else
  if test -d $with_su/lib ; then
		CPPFLAGS="${CPPFLAGS} -DSU -I$with_su/include ${DEFINES}"
		LDFLAGS="${LDFLAGS} -L$with_su/lib "
		MYLIBS="-lpar -lcwp -lpar"
	else
	echo "su directory not specified correctly"
	exit 1;
  fi
  fi
fi

AC_ARG_WITH(relative,[
Install local:
  --with-relative       Directory containing local binaries])

if test x$with_relative = x ; then
RELATIVE="BOOP"
else
RELATIVE=$with_relative
fi


AC_MSG_NOTICE([------------------------------------------])
AC_MSG_NOTICE([       Header files Checks   ])
AC_MSG_NOTICE([------------------------------------------])



AC_C_BIGENDIAN
AC_FUNC_ALLOCA
AC_HEADER_DIRENT
AC_HEADER_STDC
AC_HEADER_SYS_WAIT
dnl Checks for typedefs, structures, and compiler characteristics.
AC_C_CONST
AC_TYPE_OFF_T
AC_TYPE_PID_T
AC_TYPE_SIZE_T
AC_STRUCT_ST_RDEV
AC_HEADER_TIME
AC_STRUCT_TM
AC_TYPE_UID_T

dnl Checks for library functions.
AC_FUNC_MEMCMP
AC_FUNC_SETVBUF_REVERSED
AC_TYPE_SIGNAL
AC_FUNC_FORK([])
AC_FUNC_VPRINTF
AC_CHECK_FUNCS(ftime getcwd gethostname gettimeofday re_comp regcmp regcomp socket strcspn strdup strerror strstr uname)

AC_CHECK_HEADERS(fcntl.h limits.h sgtty.h sys/file.h sys/ioctl.h sys/time.h termio.h unistd.h sys/types.h sys/socket.h rpc/rpc.h rpc/types.h sys/tape.h sys/utsname.h)
AC_CHECK_HEADERS(errno.h stdlib.h sys/stat.h)

AC_MSG_NOTICE([------------------------------------------])
AC_MSG_NOTICE([       Compiler characteristics Checks   ])
AC_MSG_NOTICE([------------------------------------------])

AC_MSG_NOTICE([------------------------------------------])
AC_MSG_NOTICE([       Library function checks   ])
AC_MSG_NOTICE([------------------------------------------])
AC_PATH_XTRA
AC_PATH_MOTIF
AM_CONDITIONAL([FOUND_MOTIF],test  x"${no_motif}" = x"yes")
if test "$no_motif" = yes; then
AC_MSG_NOTICE([NOT COMPILING WITH MOTIF])
else
AC_DEFINE([HAVE_MOTIF],,[Compile with motif])
fi
AC_SUBST(MOTIF_LD)
AC_SUBST(LEXLIB)

AC_MSG_NOTICE([------------------------------------------])
AC_MSG_NOTICE([       System service checks   ])
AC_MSG_NOTICE([------------------------------------------])
AC_ISC_POSIX

AC_MSG_NOTICE([------------------------------------------])
AC_MSG_NOTICE([       Set final variables   ])
AC_MSG_NOTICE([------------------------------------------])





DEFINES="${DEFINES} -D${SEP_ARCH}"
AC_SUBST(DEFINES)
CPPFLAGS="${CPPFLAGS} ${DEFINES} "
FULLSRC="\$(strip \$(shell \${top_builddir}/include/fullpath \${srcdir}))"
CSOURCE="-DSOURCE='\"'\${FULLSRC}/\$(notdir \$<)'\"' "
CPPFLAGS="${CPPFLAGS} ${CSOURCE} ${X_CFLAGS}  "
LIBS="${LIBS} ${X_LIBS}  "
AC_SUBST(CPPFLAGS)
AC_SUBST(CFLAGS)
AC_PROG_INSTALL

SUBDIRS="\${CDIR_DISTR}"
SEP_PROGRAMS="\${CPROG_DISTR}"
bin_SCRIPTS="\${SCRIPTS_DISTR}"
lib_LTLIBRARIES="\${CLIB_DISTR}"


if test ${RELATIVE} = "BOOP"; then
if test "$0" = ../configure ; then
  RELATIVE=`pwd| sed -e 's/.*\///'`
  back=1
  basedir="\${top_srcdir}/../seplib_base/${RELATIVE}"
  sepprogdir="\${top_srcdir}/../seplib_prog/${RELATIVE}"
else
  back=0;
  basedir="\${top_srcdir}/../seplib_base"
  sepprogdir="\${top_srcdir}/../seplib_prog"
fi
else
if test ${RELATIVE} = "NONE" ; then
  back=0;
  basedir="\${top_srcdir}/../seplib_base"
  sepprogdir="\${top_srcdir}/../seplib_prog"
else
  back=1
  basedir="\${top_srcdir}/../seplib_base/${RELATIVE}"
  sepprogdir="\${top_srcdir}/../seplib_prog/${RELATIVE}"
fi
fi
AC_SUBST(basedir)
AC_SUBST(sepprogdir)

if test -z "${SEPDOCIT}" ; then
SEPDOCIT="${basedir}/include/sep_doc_it"
else
echo "SEPDOCIT set"
fi
AC_SUBST(SEPDOCIT)

if test x$with_sep = "xyes" ; then
	if test x$with_su = x ; then
  			CPPFLAGS="${CPPFLAGS} -I\${basedir}/include -I\${sepprogdir}/include/ -I\${top_srcdir}/../seplib_base/include -I\${top_srcdir}/../seplib_prog/include ${DEFINES} "
				LDFLAGS="${LDFLAGS} -L\${basedir}/lib/corelibs/sep/ -L\${basedir}/lib/corelibs/sep3d/ "
				SEP_PROGRAMS="$SEP_PROGRAMS \${CPROG_SEP}"
				bin_SCRIPTS="$bin_SCRIPTS \${SCRIPTS_SEP}"
				SUBDIRS="$SUBDIRS \${CDIR_SEP}"
				lib_LTLIBRARIES="$lib_LTLIBRARIES \${CLIB_SEP}"
				CPPFLAGS="${CPPFLAGS} -DSEPLIB"
				MYLIBS="-lsep3d -lsep"

	else
 		echo "Can not specify --with-sep and --with-su"
 		exit 1;
	fi
else
	if test x$with_su = x ; then
		echo "Must install with either --with-su or --with-sep"
		exit 1
	else
    echo "SU version"
	fi
fi

#this is incredibly terrible hack but haven't found a better way at this stage
if test $SEP_ARCH = SOLARIS ; then
LIBS="${LIBS} ${X_EXTRA_LIBS} -lX11 -lXt"
fi
if test $SEP_ARCH = MACOS ; then
LIBS="${LIBS} ${X_EXTRA_LIBS} -lX11  -Wl,-force_flat_namespace"
fi
if test $SEP_ARCH = SGI64 ; then
LIBS="${LIBS}  -lXt -lXpm -lX11 ${X_EXTRA_LIBS}"
fi
AC_SUBST(LIBS)
AC_SUBST(MYLIBS)
AC_SUBST(LDFLAGS)


#AC_SUBST(SUBDIRS)
#bin_PROGRAMS="\${addsuffix \${EXEEXT}, \${SEP_PROGRAMS}}"
#AC_SUBST(SEP_PROGRAMS)
#AC_SUBST(bin_PROGRAMS)

AC_CONFIG_FILES([Makefile])
AC_CONFIG_FILES([include/Makefile])
AC_CONFIG_FILES([Ricksep/Makefile])
AC_CONFIG_FILES([RickMovie/Makefile])
AC_CONFIG_FILES([include/fullpath:include/fullpath.csh.in],[chmod +x include/fullpath])
#AC_CONFIG_FILES([Ricksep/Rickvelan:Ricksep/Rickvelan.pl.in],[chmod +x Ricksep/Rickvelan])
#AC_CONFIG_FILES([Ricksep/Rick4d:Ricksep/Rick4d.pl.in],[chmod +x Ricksep/Rick4d])
#AC_CONFIG_FILES([Ricksep/Rickmulti:Ricksep/Rickmulti.pl.in],[chmod +x Ricksep/Rickmulti])
AC_CONFIG_FILES([qt_cube/Sep_cube:qt_cube/Sep_cube.py.in],[chmod +x qt_cube/Sep_cube])
AC_CONFIG_FILES([qt_cube/qt_cube.pro])
AC_CONFIG_FILES([qt_cube/Makefile])

AC_OUTPUT

