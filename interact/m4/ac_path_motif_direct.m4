dnl
dnl Check if Motif is here somewhere
dnl

AC_DEFUN([AC_PATH_MOTIF_DIRECT],[
test -z "$motif_direct_test_library" && motif_direct_test_library=Xm
test -z "$motif_direct_test_function" && motif_direct_test_function=XmCreatePushButton
test -z "$motif_direct_test_include" && motif_direct_test_include=Xm/Xm.h
  for ac_dir in               \
    /usr/include/Motif1.2     \
    /usr/OpenMotif/include     \
    /usr/Motif1.2/include     \
    /usr/lesstif20/include    \
    /usr/lesstif/include      \
    /usr/lesstif*/include     \
    /usr/motif/include        \
    /usr/X11R6/include        \
    /usr/X11R5/include        \
    /usr/include/X11R6        \
    /usr/include/X11R5        \
    /usr/local/X11R6/include  \
    /usr/local/X11R5/include  \
    /usr/local/include/X11R6  \
    /usr/local/include/X11R5  \
    /usr/X11/include          \
    /usr/include/X11          \
    /usr/local/X11/include    \
    /usr/local/include/X11    \
    /usr/X386/include         \
    /usr/x386/include         \
    /usr/XFree86/include/X11  \
    /usr/dt/include           \
    /usr/openwin/include      \
    /opt/openwin/include      \
    /usr/include              \
    /usr/local/include        \
    /usr/local/include/Xm     \
    /usr/unsupported/include  \
    /usr/athena/include       \
    /sw/include   \
    /usr/local/x11r5/include  \
    /usr/lpp/Xamples/include  \
    ; \
  do
    if test -r "$ac_dir/$motif_direct_test_include"; then
      no_motif= ac_motif_includes=$ac_dir
      break
    fi
  done

dnl Check for the libraries.
dnl See if we find them without any special options.
dnl Don't add to $LIBS permanently.
ac_save_LIBS="$LIBS"
LIBS="-l$motif_direct_test_library $LIBS"
dnl First see if replacing the include by lib works.
for ac_dir in `echo "$ac_motif_includes" | sed s/include/lib/` \
    /usr/lib/Motif1.2     \
    /usr/OpenMotif/lib    \
    /usr/Motif1.2/lib     \
    /usr/motif/lib        \
    /usr/X11R6/lib        \
    /usr/X11R5/lib        \
    /usr/lib/X11R6        \
    /usr/lib/X11R5        \
    /usr/local/X11R6/lib  \
    /usr/local/X11R5/lib  \
    /usr/local/lib/X11R6  \
    /usr/local/lib/X11R5  \
    /usr/X11/lib          \
    /usr/lib/X11          \
    /usr/local/X11/lib    \
    /usr/X386/lib         \
    /usr/x386/lib         \
    /usr/XFree86/lib/X11  \
    /sw/lib               \
    /usr/dt/lib           \
    /usr/openwin/lib      \
    /opt/openwin/lib      \
    /usr/lib              \
    /usr/lib64            \
    /usr/local/lib        \
    /usr/local/lib64      \
    /usr/unsupported/lib  \
    /usr/athena/lib       \
    /usr/local/x11r5/lib  \
    /usr/lpp/Xamples/lib  \
    ; \
do
  for ac_extension in a so sl; do
    if test -r $ac_dir/lib${motif_direct_test_library}.$ac_extension; then
      no_motif= ac_motif_libraries=$ac_dir
      break 2
    fi
  done
done
LIBS=$ac_save_LIBS
])


