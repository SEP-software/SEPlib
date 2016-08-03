
lib_LTLIBRARIES = libvppen.la libvppen_sep.la

BASE = vpattr.c vperase.c vpopen.c vpclose.c vplogmessage.c vpplot.c \
vplogvector.c vppoly.c vptext.c vpmarker.c vpraster.c vpvector.c \
vpdovplot.c vpmessage.c vpreset.c vp.h vpdoc.h

libvppen_la_SOURCES = $(BASE) vpconf.c vpsepwhere.c

libvppen_sep_la_SOURCES = $(BASE) vpconf_SEP.c vpsepwhere_SEP.c
libvppen_sep_la_CPPFLAGS = $(CF77DEFINES) -DSEP

