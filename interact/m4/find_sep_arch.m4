
AC_DEFUN([FIND_SEP_ARCH],
[ 
case "$build" in
*-apple-darwin*)
	OCPP="/lib/cpp -P -traditional"
        CFLAGS="-I/sw/include -I/usr/X11R6/include ${CFLAGS}"
        LIBS="-L/sw/lib -L/usr/X11R6/lib ${LIBS}"
	SEP_ARCH=MACOS
;;
mips*-sgi-irix6*)
	SEP_ARCH=SGI64
	if test "${CC}" != "gcc" ; then
		DEFINES="${DEFINES} -DSGI "
		LDFLAGS="${LDFLAGS} -64"
		CFLAGS="-64 -O2 ${CFLAGS}"
		FCFLAGS="-64 -O2 ${FCFLAGS} -extend_source"
	fi
;;
mips*-sgi-irix*)
	SEP_ARCH=SGI
;;
powerpc-*-linux*)
	OCPP="/lib/cpp -P -traditional"
	SEP_ARCH=LINUX 
;;
ia64-*-linux*)
	OCPP="/lib/cpp -P -traditional"
	SEP_ARCH=LINUX64 
;;
*-linux*)
	OCPP="/lib/cpp -P -traditional"
	SEP_ARCH=LINUX
;;
*-*-cygwin)
	OCPP="/lib/cpp -P -traditional"
	SEP_ARCH=CYGWIN 
;;
*-*-solaris2*)
	OCPP="/usr/ccs/lib/cpp -P"
	SEP_ARCH=SOLARIS
	LIBS="-lsocket -lnsl -lgen -lintl -lw -lm -lc ${LIBS} "
;;
*-*-sunos4*)
	SEP_ARCH=SUN4 
;;
*-hp-hpux*)
	SEP_ARCH=HP700
	CPPFLAGS="${CPPFILAGS} -Ae -D_HPUX_SOURCE"
	LIBS="-lBSD -lcl -lnsl ${LIBS}"
;;
rs6000-*-*)
	SEP_ARCH=RS600
dnl	AM_CONDITIONAL(RS6000,test ${SEP_ARCH} = "RS6000")
;;
*-convex-*)
	SEP_ARCH=CONVEX 
;;
*-cray-*)
	SEP_ARCH=CRAY 
;;
alpha-dec-*)
	SEP_ARCH=DECALPHA 
;;
*-dec-*)
	SEP_ARCH=DEC 
;;
*)
	SEP_ARCH=$build 
;;
esac
if test -z "$FCINCFLAG"; then
	if test "$SEP_ARCH" = "SOLARIS" ; then
  	FCINCFLAG="-M"
	else
  	FCINCFLAG="-I"
	fi
fi
AC_SUBST(SEP_ARCH)
])

