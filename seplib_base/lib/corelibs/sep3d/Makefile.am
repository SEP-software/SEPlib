

lib_LTLIBRARIES =libsep3d.la

libsep3d_la_SOURCES = putnumberkeys.c putaxis.c getaxis.c getnumberaxes.c \
putkey.c putheadertag.c getheadertag.c getnumberkeys.c putgridtag.c \
getgridtag.c putgetgridwindow.c getheaderbytes.c getkeyindex.c getkeyname.c \
getkeytype.c getkeyfirstbyte.c getkeyfmt.c putvalbindex.c putvalbname.c \
putvalheaders.c getvalbindex.c getvalbname.c getvalheaders.c \
handle_file_pointers.c copykeys.c copy_grid.c init_3d.c sep_3d_close.c \
tag_is_pipe.c extractvalbyindex.c insertvalbyindex.c reorder.c reorder2.c
if HAVE_FORTRAN
libsep3d_la_SOURCES += sep3d.f90
libsep3d_la_LIBADD = ../sep/libsep.la $(FCLIBS) -lm
else
libsep3d_la_LIBADD = ../sep/libsep.la -lm
endif

libsep3d_la_CPPFLAGS =  -I../include

include $(top_srcdir)/include/fortran.rules

