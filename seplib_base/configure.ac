
AC_PREREQ(2.57)

AC_INIT([seplib-base],[8.0.1],[bob@sep.stanford.edu])
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
AC_MSG_NOTICE([       Program Checks   ])
AC_MSG_NOTICE([------------------------------------------])
AC_PROG_CC(cc egcs gcc)
AC_PROG_FC(f90 pgf90 ifort ifc f95 xlf)
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
if test "$AWK" = "gawk" ; then
	AWK="gawk  -W compat"
fi

AM_PROG_LEX
if test "${LEX}" = "flex" ; then
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
AC_MSG_NOTICE([       SEP Specific options])
AC_MSG_NOTICE([------------------------------------------])

AC_PREFIX_DEFAULT(/usr/local/SEP)

FIND_SEP_ARCH


AC_MSG_CHECKING([whether compiling ../ or ./  ])
AC_ARG_WITH(relative,[
  --with-relative       Directory containing binaries])

if test x"$with_relative" = x ; then
RELATIVE="BOOP"
BASE="."
else
RELATIVE=$with_relative
BASE=".."
fi

if test "$RELATIVE" = "BOOP" ; then
if test "$0" = ../configure; then
  RELATIVE=`pwd| sed -e 's/.*\///'`
else
	RELATIVE="NONE"
fi
fi
AC_SUBST(RELATIVE)
AC_MSG_RESULT([$RELATIVE])
AC_MSG_CHECKING([whether compiling with SU support])

AC_ARG_WITH(su, [  --with-su=DIR        Install SU  compatibility option])
if test "x${with_su}" = "xyes" ; then
  AC_MSG_ERROR([
*** Directory must be specified for --with-su])
fi

if test "x${with_su}" = "x" ; then
AC_MSG_RESULT(no)
su=no
else
  SUINCLUDES=$with_su/include
  if test -x "$SUINCLUDES" ; then
    CPPFLAGS="-I$SUINCLUDES ${CPPFLAGS}"
    AC_DEFINE([SU_SUPPORT],,[Define if you want SU support])
    AC_SUBST(SUINCLUDES)
    su=yes
    AC_SUBST(su)
    AC_MSG_RESULT(yes)
  else
    su=no
    AC_MSG_ERROR([Could not find su.h at $SUINCLUDES])
  fi
fi
AM_CONDITIONAL([HAVE_SU],test  x"${su}" = x"yes")

AC_MSG_CHECKING([whether compiling the entire SEPlib package])
FULLSEP=no
AC_ARG_WITH(fullsep,[;
  --with-fullsep       Installing full SEPlib package
  --without-fullsep    Installing individual SEP packages],
  ,[with_fullsep="yes"])

FULLSEP=$with_fullsep
AC_SUBST(FULLSEP)
AC_MSG_RESULT([$FULLSEP])

AC_MSG_CHECKING([whether compiling with MPI])
AC_ARG_WITH(mpi,[;
  --with-mpi            System has a working copy of MPI and appropriate variables set
  --without-mpi         Do not compile with MPI],
  [MPI="yes"])
AC_MSG_RESULT($MPI)

AM_CONDITIONAL([HAVE_MPI], [test "x${MPI}" = xyes])
AM_CONDITIONAL([HAVE_SWIG], [test "x${SWIG}" != xno])
#if test "x${SWIG}" != "xno" ; then
#AC_PYTHON_DEVEL
#SWIG_PYTHON
#fi



AC_MSG_CHECKING([whether compiling with omp])
AC_ARG_WITH(omp,[;
  --with-omp            System has a working copy of OMP and appropriate variables set
  --without-omp         Do not compile with OMP],
  [OMP="yes"],[OMP="no"])
AC_MSG_RESULT($OMP)

AC_MSG_CHECKING([whether compiling with fftw])
AC_ARG_WITH(fftw,[;
  --with-fftw            System has a working copy of FFTW and appropriate variables set
  --without-fftw         Do not compile with FFTW],
  [FFTW="yes"])
AC_MSG_RESULT($FFTW)
AC_ARG_VAR([FFTW_FCLD],[Fortran compiler flag to be included for FFTW support])

if test "x${MPI}" = "xyes" ; then
MPI_FLAGS="${MPI_FLAGS} -DSEP_MPI"
fi

AC_SUBST(MPIFCLIBS)
AC_SUBST(MPI_FLAGS)

if test "x${FFTW}" = "xyes" ; then
FCDEFINES="${FCDEFINES} -DUSE_FFTW"
fi

if test "x${OMP}" = "xyes" ; then
FCDEFINES="${FCDEFINES} -DSEP_OMP"
AC_SUBST(OMP_FCFLAGS)
fi

if test -z "$DEFAULT_DOC_PATH"; then
if test "$0" = ../configure; then
DEFAULT_DOC_PATH=`cd ..;pwd`
else
DEFAULT_DOC_PATH=`pwd`
fi
fi
AC_SUBST(DEFAULT_DOC_PATH)
FULLSRC="\$(strip \$(shell \${top_builddir}/include/fullpath \${srcdir}))"
AC_SUBST(FULLSRC)

#FILE SIZE LIMIT
AC_MSG_CHECKING([whether file size should be automatically limited])
AC_ARG_WITH(file-2gb,[;
Limit file sizes to 2gb

  --with-file-2gb        Limit filesize to 2GB
  --without-file-2gb ],
[MAX_FILE="yes"], [MAX_FILE="no"])

if test "$MAX_FILE" = yes; then
AC_DEFINE([FILE_2GB],,[Define if you want to limit file sizes 2 GB])
fi
AC_SUBST(MAX_FILE)
AC_MSG_RESULT([$MAX_FILE])




AC_MSG_NOTICE([------------------------------------------])
AC_MSG_NOTICE([       Header files Checks   ])
AC_MSG_NOTICE([------------------------------------------])
AC_HEADER_DIRENT
AC_HEADER_STDC
AC_HEADER_SYS_WAIT
AC_CHECK_HEADERS(fcntl.h limits.h sgtty.h sys/file.h sys/ioctl.h sys/time.h termio.h unistd.h  sys/types.h  sys/socket.h rpc/rpc.h rpc/types.h sys/tape.h sys/utsname.h sys/param.h)
AC_CHECK_HEADERS(errno.h stdlib.h sys/stat.h)
AC_C_BIGENDIAN
AC_FUNC_ALLOCA
AC_TYPE_OFF_T
AC_TYPE_PID_T
AC_TYPE_SIZE_T
AC_TYPE_SIGNAL
AC_CHECK_MEMBERS([struct stat.st_rdev])
AC_HEADER_TIME
AC_STRUCT_TM
AC_TYPE_UID_T



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

#Fortran cpp
OCPP="/lib/cpp -P"
DEFINES="${DEFINES} -D${SEP_ARCH}"
AC_SUBST(DEFINES)
CPPFLAGS="${CPPFLAGS} ${DEFINES}  "
CSOURCE="-DSOURCE='\"'\${FULLSRC}/\$(notdir \$<)'\"' ${X_CFLAGS}"
AC_SUBST(CPPFLAGS)
AC_SUBST(CFLAGS)
FCDEFINES="${FCDEFINES} ${DEFINES} -D${SEP_ARCH}"
AC_SUBST(FCDEFINES)

AC_SUBST(LIBS)
if test -z "$CCLD"; then
	CCLD="\${CC}"
fi

AC_SUBST(CC)
AC_SUBST(CCLD)
SEP_FC
SEPRAT="\${top_builddir}/include/ratsep"
AC_SUBST(SEPRAT)



AC_SUBST(HAVE_FC)
FCMODSUFFIX=`echo "$FCMODEXT"| sed 's/\*\.//g'`
AC_SUBST(FCMODSUFFIX)
AM_CONDITIONAL(HAVE_FC, test "$HAVE_FC" = "yes")


AC_MSG_NOTICE([------------------------------------------])
AC_MSG_NOTICE([       Library function checks   ])
AC_MSG_NOTICE([------------------------------------------])
AC_FUNC_FSEEKO
AC_CHECK_LIB(fl,yywrap,LEXLIB=-lfl,[echo " "],-lc)
AC_CHECK_LIB(l,yywrap,LEXLIB=-ll,[echo " "],-lc)
AC_SUBST(LEXLIB)
LIBS="-lm ${LIBS}"
AC_FUNC_MEMCMP
AC_FUNC_SETVBUF_REVERSED
AC_TYPE_SIGNAL
AC_FUNC_VPRINTF
AC_FUNC_FORK([])
AC_CHECK_FUNCS(ftime getcwd gethostname gettimeofday re_comp regcmp regcomp socket strcspn strdup strerror strstr uname)



AC_MSG_NOTICE([------------------------------------------])
AC_MSG_NOTICE([       System service checks   ])
AC_MSG_NOTICE([------------------------------------------])

AC_ISC_POSIX
AC_SYS_LONG_FILE_NAMES
AC_SYS_LARGEFILE
AC_PATH_X
AC_PATH_XTRA

AC_MSG_NOTICE([------------------------------------------])
AC_MSG_NOTICE([       Set final variables   ])
AC_MSG_NOTICE([------------------------------------------])

OCPPFLAGS="-I\${SEPINCDIR} ${CPPFLAGS}"
AC_SUBST(OCPPFLAGS)
CPPFLAGS="${CPPFLAGS} -I\${top_srcdir}/include -I\${top_builddir}/include ${X_CFLAGS} ${CSOURCE} ${CFCDEFINES}"

FCFLAGS_F90="${FCFLAGS_F90} ${FCINCFLAG}\${top_builddir}/lib/corelibs/sep ${FCINCFLAG}\${top_builddir}/lib/corelibs/sep3d  ${FCINCFLAG}\${top_builddir}/lib/corelibs/superset ${FCINCFLAG}\${top_builddir}/lib/util/fft ${FCINCFLAG}\${top_builddir}/lib/util/math ${FCINCFLAG}\${top_builddir}/lib/util/sepaux ${FCINCFLAG}\${top_builddir}/lib/class/util ${FCINCFLAG}\${top_builddir}/lib/class/bei ${FCINCFLAG}\${top_builddir}/lib/class/pvi ${FCINCFLAG}\${top_builddir}/lib/class/gee ${FCINCFLAG}\${top_builddir}/lib/seis/filter ${FCINCFLAG}\${top_builddir}/lib/util/par"
F90FLAGS=" ${FCFLAGS_F90} ${F90FLAGS} -${FCINCFLAG}."
AC_SUBST(FCFLAGS_F90)

OFCPFLAGS="${FCPFLAGS}"
FCPFLAGS="${FCPFLAGS} ${F90SOURCE} -I. "
AC_SUBST(OFCPFLAGS)
AC_SUBST(OLDFLAGS)
AC_SUBST(OFCLDFLAGS)
AC_SUBST(OCPP)
LDFLAGS="${LDFLAGS}  ${LOCLDFLAGS}"
FCLDFLAGS="${FCLDFLAGS}  ${LOCLDFLAGS}"
AC_SUBST(FCPFLAGS)
AC_SUBST(FCFLAGS)

AC_SUBST(SUBDIRS)
AC_SUBST(bin_PROGRAMS)
#AC_PROG_CPP





dnl THE FILES WE ARE GOING TO CREATE


AC_CONFIG_FILES([include/fullpath:include/fullpath.csh.in],
                [chmod +x include/fullpath])
AC_CONFIG_FILES([include/ratsep:include/ratsep.pl.in],
                [chmod +x include/ratsep])
AC_CONFIG_FILES([include/sep_doc_it:include/sep_doc_it.pl.in],
                [chmod +x include/sep_doc_it])
AC_CONFIG_FILES([include/v_f90:include/v_f90.pl.in],
                [chmod +x include/v_f90])
AC_CONFIG_FILES([include/su.h include/segy.h])

AC_CONFIG_FILES([tools/pod2text/pod2text:tools/pod2text/pod2text.pl.in],
                [chmod +x tools/pod2text/pod2text])
AC_CONFIG_FILES([tools/autowriters/sat/satf.csh], [chmod +x tools/autowriters/sat/satf.csh])
AC_CONFIG_FILES([tools/autowriters/saw/sawf.csh], [chmod +x tools/autowriters/saw/sawf.csh])
AC_CONFIG_FILES([tools/spp/spp:tools/spp/spp.pl.in],[chmod +x tools/spp/spp])
AC_CONFIG_FILES([tools/keyword/Snoop],[chmod +x tools/keyword/Snoop])
AC_CONFIG_FILES([tools/keyword/key-word],[chmod +x tools/keyword/key-word])
AC_CONFIG_FILES([tools/makedepend/Makedepend:tools/makedepend/Makedepend.pl.in],
                [chmod +x tools/makedepend/Makedepend])
AC_CONFIG_FILES([tools/shortfort/shortfort],
                [chmod +x tools/shortfort/shortfort])
AC_CONFIG_FILES([tools/extractpod/ExtractPOD],
                [chmod +x tools/extractpod/ExtractPOD])
AC_CONFIG_FILES([tools/lop2f90/lop2f90],[chmod +x tools/lop2f90/lop2f90])

AC_CONFIG_FILES([lib/corelibs/sep/sepdoc.c lib/corelibs/superset/rite.inc
lib/util/sepaux/quick_sort_kernal.inc])

AC_CONFIG_FILES([Makefile include/Makefile tools/Makefile tools/pod2text/Makefile
tools/keyword/Makefile tools/ratfor77/Makefile tools/cfortran/Makefile
tools/setenviron/Makefile 
tools/fixnull/Makefile tools/autowriters/Makefile tools/autowriters/sat/Makefile
tools/autowriters/saw/Makefile tools/shortfort/Makefile tools/makedepend/Makefile
tools/extractpod/Makefile tools/lop2f90/Makefile tools/spp/Makefile lib/Makefile
lib/corelibs/Makefile lib/corelibs/include/Makefile lib/corelibs/sep/Makefile
lib/corelibs/sep3d/Makefile lib/corelibs/superset/Makefile lib/graphics/Makefile
lib/graphics/glplot/Makefile lib/class/Makefile lib/class/util/Makefile lib/class/bei/Makefile lib/class/pvi/Makefile lib/class/gee/Makefile lib/util/Makefile
lib/util/math/Makefile lib/util/sepaux/Makefile lib/util/convert/Makefile
lib/util/par/Makefile lib/util/fft/Makefile lib/util/vector/Makefile
lib/util/cwp/Makefile lib/seis/Makefile lib/seis/travel/Makefile lib/seis/wei/Makefile
lib/seis/velan/Makefile lib/seis/filter/Makefile lib/seis/image/Makefile
lib/seis/dip/Makefile lib/seis/model/Makefile])

AC_OUTPUT
