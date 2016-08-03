
AC_DEFUN([MAKE_GMAKE],[
AC_CHECK_PROGS(MAKE, gmake make, make)
run_it=`echo "$MAKE -v "`
eval $run_it 1>in.v1 2>in.v2
if ( eval "grep -i gnu in.v1") ; then
	rm -f in.v1 in.v2
	AC_MSG_NOTICE(Using gmake)
else
	rm -f in.v1 in.v2
	AC_MSG_ERROR(Require GNU Make)
fi
])

