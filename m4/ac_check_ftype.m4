
dnl AC_CHECK_FTYPE(fprog,CFFLAG,FLIBS,FDEFS,FCFLAGS)

AC_DEFUN([AC_CHECK_FTYPE],[
run_it=`echo "[$1] -version"`
eval $run_it 1>/dev/null 2> in.v1
run_it=`echo "[$1] --version"`
eval $run_it 1>in.v2 2> in.v4
run_it=`echo "[$1] -what"`
eval $run_it 1>/dev/null 2> in.v3
run_it=`echo "[$1] -V"`
eval $run_it 1>in.v5 2> /dev/null
run_it=`echo "[$1] -V"`
eval $run_it 1>/dev/null 2>in.v6
run_it=`echo "echo [$1] "`
eval $run_it 1>in.v9 2>/dev/null
run_it=`echo "[$1] -dryrun"`
eval $run_it 1>in.v7 2>/dev/null
echo >> junk.f90
run_it=`echo "[$1] -V junk.f90"`
eval $run_it 2>in.v8 1>/dev/null
rm junk.f90

if test "[$1]" = "fort77" -a "$SEP_ARCH" = "LINUX" ; then
	$2="$[$2] -Dgnu -Df2cFortran"
	$3="$[$3] -ffixed-line-length-none -ff90 -fdollar-ok"
	$4="$[$4] -lg2c -lm  "
fi

if ( eval "grep -i ardent in.v4") ; then
	$2="$[$2] -DARDENT"
fi
if ( eval "grep -i ardent in.v2") ; then
	$2="$[$2] -DARDENT"
fi
if ( eval "grep -i ardent in.v1") ; then
	$2="$[$2] -DARDENT"
fi

if ( eval "grep -i vast in.v7") ; then
	vastsiera=1
	$2="$[$2] -Dgnu -Df2cFortran"
	$3="$[$3] -ffixed-line-length-none -ff90 -fdollar-ok -fargument-noalias -fno-globals "
	$4="$[$4] -lm "
else
	if ( eval "grep -i numerical in.v1") ; then
		$2="$[$2] -DNAGf90Fortran"
		$5="$[$5] -free -mismatch"
        else
        if ( eval "grep -i IBM in.v5 |grep -i fortran") ; then
          $5="$[$5] -qsuffix=f=f90 -qfree -qextname"
          if  test "$SEP_ARCH" = "RS6000" ; then
	    $2="$[$2] -DIBMR2Fortran"
          else
	    $2="$[$2] -DXLFGCC"
          fi
	else
		if ( eval "grep -i g95 in.v2") ; then
			$2="$[$2] -Dgnu -Df2cFortran"
			$4="$[$4] -lm  "
		fi
	fi
	fi
if ( eval "grep -i absoft in.v8") ; then
#	$2="$[$2] -DAbsoftUNIXFortran"
	$2="$[$2] -DAbsoftProFortran"
	$4="$[$4] -lU77"
	FCINCFLAG="-p"
fi
if ( eval "grep -i intel in.v6" || eval "grep -i intel in.v5" ); then
	$2="$[$2] -DpgiFortran"
	$4="$[$4] -lm"
fi
if ( eval "grep -i portland in.v5") ; then
	$2="$[$2] -DpgiFortran"
	$3="$[$3] "
fi
if test "${SEP_ARCH}" = "DEC" -o "${SEP_ARCH}" = "DECALPHA" ; then
	if ( eval "grep -i DEC in.v3") ; then
		$2="$[$2] -DDECFortran"
	fi
fi
if ( eval "grep -i portland in.v5") ; then
	$2="$[$2] -DpgiFortran"
fi
if test "${SEP_ARCH}" = "DECALPHA" ; then
	$4="$[$4] -lUfor -lfor -lFutil -lm -lots"
fi
if test "${SEP_ARCH}" = "CRAY" ; then
	$3="$[$3] -DSIGFNC_RTN_VOID -DUSG"
fi
if test "${SEP_ARCH}" = "HP700" ; then
	$2="$[$2] -Dextname"
	$5="$[$5] -v +e +es +ppu"
	$4="$[$4] -lBSD -lm -lcl -lc"
fi
if ( eval "grep -i gfortran in.v9") ; then
	$2="$[$2]  -Df2cFortran -Dgfortran"
fi
# if test "${SEP_ARCH}" = "LINUX" ; then
#   $4="$[$4] -lf2c -lm  -lf2c"
# fi
#end of vast
fi
rm -f in.v1 in.v2 in.v3 in.v4 in.v5 in.v6 in.v7 in.v8 in.v9
])

