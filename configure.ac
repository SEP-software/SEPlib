AC_PREREQ(2.57)

AC_INIT([seplib],[8.0.1],[bob@sep.stanford.edu])

AC_CONFIG_HEADERS([include/sitedef.h])
AC_CONFIG_SRCDIR([Makefile.am])

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

AC_PROG_CC([cc egcs gcc])
AC_PROG_FC([f90 pgf90 ifort ifc f95 xlf g95])
AC_PROG_MAKE_SET
MAKE_GMAKE

AC_MSG_NOTICE([------------------------------------------])
AC_MSG_NOTICE([       SEP Specific options])
AC_MSG_NOTICE([------------------------------------------])

AC_PREFIX_DEFAULT([/usr/local/SEP])
echo "where i die 1"

FIND_SEP_ARCH

AC_MSG_NOTICE([Checking for SEP distribution type])

COMPILE_LEVEL="DISTR"
AC_SUBST(COMPILE_LEVEL)

AC_ARG_WITH(mpi,
AS_HELP_STRING([--with-mpi],[Compile with MPI support]))
AC_ARG_VAR([MPI_LD],[Libraries for compiling C with MPI support])
AC_ARG_VAR([MPI_FCLD],[Libraries for compiling Fortran with MPI support])

AC_MSG_NOTICE([Checking whether OpenMP support is requested])
AC_ARG_WITH(omp,
AS_HELP_STRING([--with-omp],[Compile with OpenMP support]))
AC_ARG_VAR([OMP_FCFLAGS],[Fortran compiler flag to be included for OpenMP support])
AC_ARG_VAR([OMP_FCLD],[Fortran linker flag to be included for OpenMP support])

AC_MSG_NOTICE([Checking whether CWP/SU support is requested])
AC_ARG_WITH(su,
AS_HELP_STRING([--with-su=DIR],[Install CWP/SU compatibility option]))
if test "x$with_su" = xyes ; then
  AC_MSG_ERROR([Directory must be specified for --with-su])
fi
if test "x$with_su" = x ; then
	AC_MSG_NOTICE([Not installing SU support])
fi

dnl HANDLE MAN PAGES
HAVE_MAN_FMT="yes"
AC_MSG_NOTICE([Checking whether man page processing is requested])
AC_ARG_WITH(mansupport,
AS_HELP_STRING([--with-mansupport],[Install formatted manual pages]),
[HAVE_MAN_FMT="yes"], [HAVE_MAN_FMT="no"])

dnl FILE SIZE LIMIT
AC_MSG_NOTICE([Checking whether we want to limit binaries to 2 GB])
AC_ARG_WITH(file-2gb,
AS_HELP_STRING([--with-file-2gb],[Limit file sizes to 2gb]))

AC_MSG_NOTICE([Checking whether FFTW support is requested])
AC_ARG_WITH(fftw,
AS_HELP_STRING([--with-fftw],[Compile with FFTW3 support (float type)]))
AC_ARG_VAR([FFTW_FCLD],[Fortran compiler flag to be included for FFTW support])

AM_CONDITIONAL(HAVE_MAN_FMT, test "$HAVE_MAN_FMT" = "yes")
AC_SUBST(ARG_LIST_BASE)
AC_SUBST(ARG_LIST_SEP)

AC_CONFIG_FILES([
Makefile
include/Makefile
docs/Makefile
docs/config_examples/Makefile
docs/pod/Makefile
docs/pod/seplib_prog/Makefile
docs/pod/seplib_base/Makefile
docs/pod/vplot/Makefile
docs/html/Makefile
docs/html/seplib_base/Makefile
docs/html/seplib_prog/Makefile
docs/html/vplot/Makefile
docs/man/Makefile
docs/man/man1/Makefile docs/man/man3/Makefile
])

AC_CONFIG_SUBDIRS(config)
AC_CONFIG_SUBDIRS(ratfor90)
AC_CONFIG_SUBDIRS(seplib_base)
AC_CONFIG_SUBDIRS(vplot)
AC_CONFIG_SUBDIRS(seplib_prog)
AC_CONFIG_SUBDIRS(sep_python)
AC_OUTPUT



