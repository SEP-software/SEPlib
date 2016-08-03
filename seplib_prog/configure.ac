AC_PREREQ(2.57)

AC_INIT([seplib-prog],[8.0.1],[bob@sep.stanford.edu])

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

AC_PATH_PROG(PYTHON,python,no)
AM_CONDITIONAL([HAVE_PYTHON], [test "x${PYTHON}" != xno])
AC_SUBST(PYTHON)


case "$FC" in
ifort)
CFCLDFLAGS="-nofor_main"
;;
*)
CFCLDFLAGS=""
;;
esac
AC_SUBST(CFCLDFLAGS)

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
AC_PATH_PROG(PERL,perl,no)
if test "${PERL}" = no; then
  echo "You must have perl (5.00+) to install SEPlib"
  exit 1;
fi
AC_PATH_PROG(PODTEXT, pod2text, less)
AC_SUBST(PODTEXT)
AC_MSG_NOTICE([------------------------------------------])
AC_MSG_NOTICE([       SEP Specific options   ])
AC_MSG_NOTICE([------------------------------------------])

AC_PREFIX_DEFAULT(/usr/local/SEP)
FIND_SEP_ARCH
AC_MSG_CHECKING([Compile with mpi support ])
MPI=no
AC_ARG_WITH(mpi,[;
  --with-mpi            System has a working copy of MPI and appropriate variables set
  --without-mpi         Do not compile with MPI],
  [MPI="yes"])
AC_MSG_RESULT([$MPI])

if test "x${MPI}" = "xyes" ; then
MPI_FLAGS="${MPI_FLAGS} -DSEP_MPI"
fi
AC_SUBST(MPI_FLAGS)

if test "x${OMP_FCFLAGS}" = "x" ; then
  OMP_FCFLAGS=""
fi
if test "x${OMP_FCFLAGS}" = "x" ; then
  OMP_FCFLAGS=""
fi

AM_CONDITIONAL([HAVE_MPI], [test "x${MPI}" = xyes])

AC_SUBST(OMP_FCLD)
AC_SUBST(OMP_FCFLAGS)
MPI_FCLD="${MPI_FCLD}"
MPI_LD="${MPI_LD}"
AC_SUBST(MPI_FCLD)
AC_SUBST(MPI_LD)

AC_MSG_CHECKING([Compile with FFTW support])
FFTW=no
AC_ARG_WITH(fftw,[;
  --with-fftw            System has a working copy of FFTW and appropriate variables set
  --without-fftw         Do not compile with FFTW],
  [FFTW="yes"])

AC_MSG_RESULT([$FFTW])
if test "x${FFTW}" = "xyes" ; then
FCDEFINES="${FCDEFINES} -DUSE_FFTW"
fi

if test "x${FFTW_LD}" = "x" ; then
  FFTW_LD=""
fi
if test "x${FFTW_FCLD}" = "x" ; then
  FFTW_FCLD=""
fi
AC_SUBST(FFTW_FCLD)



AC_MSG_CHECKING([Compile with OMP support])
OMP=no
AC_ARG_WITH(omp,[;
  --with-omp            System has a working copy of OMP and appropriate variables set
  --without-omp         Do not compile with OMP],
  [OMP="yes"])

if test "x${OMP}" = "xyes" ; then
FCDEFINES="${FCDEFINES} -DSEP_OMP"
fi
AC_MSG_RESULT([$OMP])
AC_SUBST(FCDEFINES)

AC_MSG_CHECKING([whether compiling with SU support])

	AC_ARG_WITH(su, [  --with-su=DIR        Install SU 	compatibility option])

if test x$with_su = xyes ; then
  AC_MSG_ERROR([
*** Directory must be specified for --with-su])
fi

if test x$with_su = x ; then
AC_MSG_RESULT([no])
else
	SUINCLUDES=$with_su/include
	if test -x $SUINCLUDES ; then
		SUSEPLIB="-L$with_su/lib -lsepsu -lsuperset -lsep3d -lsep -lsu -lpar -lcwp"
		AC_DEFINE([SU_SUPPORT],,[Define if you want SU support])
		AC_SUBST(SUINCLUDES)
		AC_SUBST(SUSEPLIB)
		su=yes
		AC_SUBST(su)
    SUINCLUDES="-I${SUINCLUDES}"
    AC_MSG_RESULT([yes])
  else
    SUINCLUDES= " "
    AC_MSG_ERROR([Could not find su.h at $SUINCLUDES])
  fi
fi
AM_CONDITIONAL(HAVE_SU,test ${su} = "yes")

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

ACX_PTHREAD(PTHREAD=yes,PTHREAD=no)
AM_CONDITIONAL([PTHREADING], [test "x${PTHREAD}" = xyes])
if  test "${PTHREAD}" == no; then
PTHREAD_CC = ${CC}
PTHREAD_CFLAGS =
PTHREAD_LIBS =
AC_SUBST(PTHREAD_CC)
else
AC_DEFINE([HAVE_PTHREAD],,[Define if you have pthreads])
fi



AC_MSG_NOTICE([------------------------------------------])
AC_MSG_NOTICE([       Compiler characteristics Checks   ])
AC_MSG_NOTICE([------------------------------------------])

 if  test "${FC}" == no; then
   AC_MSG_NOTICE([ NO FORTRAN])
 else
   AC_LANG_PUSH(Fortran)
   if  test "${FC}" == vf90; then
     FC_ORIG=${FC}
     FC="\${top_builddir}/include/v_f90"
     AC_MSG_NOTICE([       Using vf90 no freeform,suffix check   ])
   else
     AC_FC_FREEFORM
     AC_FC_SRCEXT(f90)
   fi
   AC_LANG_POP
 fi
SEP_FC


if test -z "${SEPRAT}" ; then
SEPRAT="${basedir}/include/ratsep"
else
echo "SEPRAT set"
fi
AC_SUBST(SEPRAT)

if test -z "${SEPDOCIT}" ; then
SEPDOCIT="${basedir}/include/sep_doc_it"
else
echo "SEPDOCIT set"
fi
AC_SUBST(SEPDOCIT)

FCMODSUFFIX=`echo "$FCMODEXT"| sed 's/\*\.//g'`
AC_SUBST(FCMODSUFFIX)

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

FCFLAGS="${LOCFCFLAGS} ${FCFLAGS} ${FCINCFLAG}${basedir}/lib/corelibs/sep ${FCINCFLAG}${basedir}/lib/corelibs/sep3d ${FCINCFLAG}${basedir}/lib/corelibs/superset ${FCINCFLAG}${basedir}/lib/class/gee ${FCINCFLAG}${basedir}/lib/class/util ${FCINCFLAG}${basedir}/lib/util/sepaux ${FCINCFLAG}${basedir}/lib/util/math ${FCINCFLAG}${basedir}/lib/util/fft ${FCINCFLAG}${basedir}/lib/seis/velan ${FCINCFLAG}${basedir}/lib/seis/image ${FCINCFLAG}${basedir}/lib/seis/wei ${FCINCFLAG}${basedir}/lib/seis/filter ${FCINCFLAG}${basedir}/lib/seis/dip ${FCINCFLAG}${basedir}/lib/seis/model ${FCINCFLAG}${basedir}/lib/util/par   ${FCINCFLAG}${basedir}/lib/util/convert "

LDFLAGS="${LOCLDFLAGS} -L${basedir}/lib/corelibs/sep -L${basedir}/lib/corelibs/sep3d -L${basedir}/lib/corelibs/superset -L${vplotdir}/libvplot -L${basedir}/lib/graphics/glplot -L${basedir}/lib/class/gee -L${basedir}/lib/class/util -L${basedir}/lib/util/math -L${basedir}/lib/util/sepaux -L${basedir}/lib/util/fft -L${basedir}/lib/util/par -L${basedir}/lib/util/vector -L${basedir}/lib/util/convert -L${basedir}/lib/seis/travel -L${basedir}/lib/seis/velan -L${basedir}/lib/seis/filter -L${basedir}/lib/seis/image -L${basedir}/lib/seis/wei -L${basedir}/lib/seis/dip -L${basedir}/lib/util/cwp -L${basedir}/lib/seis/model "

FCFLAGS="${FCFLAGS} "

FCDEFINES="${FCDEFINES} ${DEFINES} -DSOURCE='\"'\${FULLSRC}/\$(notdir \$<)'\"'"
AC_SUBST(FCFLAGS_F90)

AC_SUBST(LDFLAGS)

CPPFLAGS="${CPPFLAGS} -I\${top_srcdir}/include -I\${top_builddir}/include -I\${basedir}/include -I\${top_srcdir}/../seplib_base/include -I\${top_srcdir}/../vplot/include ${X_CFLAGS} ${SUINCLUDES} ${CSOURCE}"




AC_CONFIG_FILES([include/fullpath:include/fullpath.csh.in],[chmod +x include/fullpath])
AC_CONFIG_FILES([util/cube/Scat],[chmod +x util/cube/Scat])
AC_CONFIG_FILES([util/vector/Math],[chmod +x util/vector/Math])
AC_CONFIG_FILES([util/info/atoF],[chmod +x util/info/atoF])
AC_CONFIG_FILES([util/unix/Sls],[chmod +x util/unix/Sls])
AC_CONFIG_FILES([util/unix/Smv3d],[chmod +x util/unix/Srm3d])
AC_CONFIG_FILES([util/unix/Srm3d],[chmod +x util/unix/Srm3d])
AC_CONFIG_FILES([util/unix/Zero],[chmod +x util/unix/Zero])
AC_CONFIG_FILES([util/vector/Cmplx],[chmod +x util/vector/Cmplx])
AC_CONFIG_FILES([util/vector/Cmult],[chmod +x util/vector/Cmult])
AC_CONFIG_FILES([util/vector/arithpar],[chmod +x util/vector/arithpar])
AC_CONFIG_FILES([seis/velan/Radial],[chmod +x seis/velan/Radial])
AC_CONFIG_FILES([seis/velan/NMO],[chmod +x seis/velan/NMO])
AC_CONFIG_FILES([seis/velan/LMO],[chmod +x seis/velan/LMO])
AC_CONFIG_FILES([seis/velan/Radnmo],[chmod +x seis/velan/Radnmo])
AC_CONFIG_FILES([seis/velan/Unmo],[chmod +x seis/velan/Unmo])
AC_CONFIG_FILES([converters/grafconv/pstogif],[chmod +x converters/grafconv/pstogif])
AC_CONFIG_FILES([converters/grafconv/vplot2gif],[chmod +x converters/grafconv/vplot2gif])
AC_CONFIG_FILES([converters/grafconv/vplot2mpeg],[chmod +x converters/grafconv/vplot2mpeg])
AC_CONFIG_FILES([converters/grafconv/vplot2ras],[chmod +x converters/grafconv/vplot2ras])
AC_CONFIG_FILES([converters/grafconv/Byte2mpeg],[chmod +x converters/grafconv/Byte2mpeg])

AC_CONFIG_FILES([Makefile include/Makefile util/Makefile util/cube/Makefile 
util/par/Makefile
util/info/Makefile util/header/Makefile util/unix/Makefile util/vector/Makefile
seis/Makefile seis/velan/Makefile seis/filter/Makefile seis/image/Makefile
seis/dip/Makefile
seis/model/Makefile seis/travel/Makefile converters/Makefile converters/grafconv/Makefile
converters/segy/Makefile converters/su/Makefile sep_graphics/Makefile])


AC_OUTPUT
