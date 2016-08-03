lib_LTLIBRARIES = libsepsergey.la

if HAVE_FORTRAN
lib_LTLIBRARIES +=  libsepsergeyf90.la
endif


libsepsergeyf90_la_SOURCES = fortstubs.c

libsepsergey_la_SOURCES =adjnull.c  dip3.c sergey_getpar.c \
c99.c          trianglen.c\
sergey_alloc.c     divn.c   mask6.c    simtab.c    \
conjgrad.c  weight.c\
allp3.c     sergey_error.c    \
decart.c    oc.c       tent2.c\
apfilt.c    sergey_file.c   \
ocpatch.c   triangle.c \
 pwdsl.c predict.c repeat.c files.c triangle1.c banded.c pwd.c

include $(top_srcdir)/include/fortran.rules

