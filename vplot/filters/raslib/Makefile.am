
lib_LTLIBRARIES = libraspen.la libraspen_sep.la

BASE = rasattr.c rasconf.c rasvector2.c raserase.c rasreset.c rasvector3.c \
rasvector.c rasvector4.c rasdoc.h raspen.h

libraspen_la_SOURCES = $(BASE) rasclose.c rasopen.c
libraspen_la_CPPFLAGS = $(PPM_INC)

libraspen_sep_la_SOURCES = $(BASE) rasclose_SEP.c rasopen_SEP.c
libraspen_sep_la_CPPFLAGS = $(CF77DEFINES) $(PPM_INC) -DSEP

