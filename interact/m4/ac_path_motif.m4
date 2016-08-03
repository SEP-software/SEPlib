
AC_DEFUN([AC_PATH_MOTIF],[
AC_REQUIRE_CPP()dnl

motif_includes=NONE
motif_libraries=NONE

AC_MSG_CHECKING(for Motif)
AC_ARG_WITH(motif, [  --with-motif            enable Motif tests])
if test "x$with_motif" = xno; then
  no_motif=yes
else
  if test "x$motif_includes" != xNONE && test "x$motif_libraries" != xNONE; then
    no_motif=
  else
AC_CACHE_VAL(ac_cv_path_motif,
[# One or both of these vars are not set, and there is no cached value.
no_motif=yes
AC_PATH_MOTIF_DIRECT

if test "$no_motif" = yes; then
  ac_cv_path_motif="no_motif=yes"
else
  ac_cv_path_motif="no_motif= ac_motif_includes=$ac_motif_includes ac_motif_libraries=$ac_motif_libraries"
fi])dnl
  fi
  eval "$ac_cv_path_motif"
fi # with_motif != no

if test "$no_motif" = yes; then
  AC_MSG_RESULT(no)
else
  test "x$motif_includes" = xNONE && motif_includes=$ac_motif_includes
  test "x$motif_libraries" = xNONE && motif_libraries=$ac_motif_libraries
  ac_cv_path_motif="no_motif= ac_motif_includes=$motif_includes ac_motif_libraries=$motif_libraries"
  AC_MSG_RESULT([libraries $motif_libraries, headers $motif_includes])
  CFLAGS="${CFLAGS} -I$motif_includes"
  LIBS="${LIBS} -L$motif_libraries -lXm "
  AC_PATH_XTRA
fi
])

