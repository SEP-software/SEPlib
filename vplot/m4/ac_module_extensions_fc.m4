
AC_DEFUN([AC_MODULE_EXTENSIONS_FC],[
AC_MSG_CHECKING([which extensions compiling a module with $FC generates])
AC_LANG_SAVE
AC_LANG(Fortran)

cat > conftest.$ac_ext <<EOF
module conftest
end module conftest
EOF
AC_TRY_EVAL(ac_compile)

changequote(, )dnl
FCMODEXT=`echo *conftest* CONFTEST* | sed \
-e "s/[a-zA-Z]*conftest//g" \
-e "s/CONFTEST//g" \
-e "s/\.$ac_ext//g" \
-e "s/\.$ac_objext//g" \
-e "s/\*//g" \
`
changequote([, ])dnl

AC_MSG_RESULT(`echo "$FCMODEXT"`)
FCMODEXT=`echo "$FCMODEXT" | sed 's/\./*./g'`
rm -f *conftest* CONFTEST*
AC_LANG_RESTORE
AC_SUBST(FCMODEXT)
])

