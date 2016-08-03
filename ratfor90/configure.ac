
AC_PREREQ(2.57)

AC_INIT([ratfor90],[8.0.1],[bob@sep.stanford.edu])

AC_CANONICAL_TARGET

AC_CONFIG_SRCDIR([Makefile.am])

AM_INIT_AUTOMAKE([foreign 1.8 dist-bzip2])

dnl Avoid generating makefile rules to rebuild maintainer-only files by
dnl default. Maintainers may override this default and generate these
dnl makefile rules using the `--enable-maintainer-mode' configure option.
AM_MAINTAINER_MODE

if test -z "$CC"; then
  CC="cc"
fi

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
AC_PATH_PROG(TOUCH, touch, touch)
AC_PATH_PROG(RM, rm, rm)


AC_CONFIG_FILES([Makefile])
AC_CONFIG_FILES([ratfor90:ratfor90.pl.in], [chmod +x ratfor90])
AC_CONFIG_FILES([ratfor90.spec])

AC_OUTPUT

