
lib_LTLIBRARIES = libpspen.la libpspen_sep.la

BASE = psarea.c psreset.c psattr.c psplot.c pstext.c pserase.c \
psraster_dumb.c psvector.c psraster_smart.c ps.h psdoc.h psfonts.h

libpspen_sep_la_SOURCES = $(BASE) psconf_SEP.c psopen_SEP.c psclose_SEP.c
libpspen_sep_la_CPPFLAGS = $(CF77DEFINES) -DSEP

libpspen_la_SOURCES = ${BASE} psconf.c psopen.c psclose.c

