
lib_LTLIBRARIES = libxtpen.la libxtpen_sep.la

BASE = appdata.c xtclose.c xtframe.c xtpaint.c popup.c xtcolors.c \
xtgetpoint.c xtpixmap.c xtcommands.c xtinteract.c xtplot.c xtmessage.c \
xtpoint.c xtarea.c xtraster.c xtattr.c xterase.c

libxtpen_la_SOURCES = $(BASE) xtconf.c xtopen.c xt_dovplot.c \
xtcommands.h xtdoc.h xtframe.h xtpen.h xtpixmap.h
libxtpen_LDFLAGS = ${X_LIBS} ${X_PRE_LIBS} ${X_EXTRA_LIBS}

libxtpen_sep_la_SOURCES = $(BASE) xtconf_SEP.c xtopen_SEP.c xt_dovplot_SEP.c
libxtpen_sep_la_CPPFLAGS = $(CF77DEFINES) -DSEP
libxtpen_sep_LDFLAGS = ${X_LIBS} ${X_PRE_LIBS} ${X_EXTRA_LIBS}

