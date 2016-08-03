

lib_LTLIBRARIES = 
if HAVE_FORTRAN
lib_LTLIBRARIES += libsepmodelf90.la
endif

libsepmodelf90_la_SOURCES = data.f90 extrapolation.f90 \
extrapolation_type.f90 image.f90 kernal.f90 slow.f90 wave.f90 \
wavelet_mod.f90 rtm_section.f90

libsepmodelf90_la_LIBADD = $(FFTW_FCLD) \
    ../../corelibs/sep3d/libsep3d.la \
    ../../corelibs/sep/libsep.la \
    $(FCLIBS) -lm

EXTRA_DIST = data.f90s image.f90s slow.f90s  \
extrapolation.f90s kernal.f90s wave.f90s  wavelet_mod.f90s \
extrapolation_type.f90s rtm_section.f90s

# Modules dependencies
image.o: extrapolation_type.o rtm_section.o
wavelet_mod.o: extrapolation_type.o
slow.o: extrapolation_type.o
wave.o: extrapolation_type.o
extrapolation.o: slow.o data.o wavelet_mod.o kernal.o wave.o image.o
data.o: extrapolation_type.o rtm_section.o
kernal.o: extrapolation_type.o

# Modules dependencies for libtool
image.lo: extrapolation_type.lo rtm_section.lo
wavelet_mod.lo: extrapolation_type.lo
slow.lo: extrapolation_type.lo
wave.lo: extrapolation_type.lo
extrapolation.lo: slow.lo data.lo wavelet_mod.lo kernal.lo wave.lo image.lo
data.lo: extrapolation_type.lo rtm_section.lo
kernal.lo: extrapolation_type.lo


data.f90: data.f90s
image.f90: image.f90s
slow.f90: slow.f90s
extrapolation.f90: extrapolation.f90s
kernal.f90: kernal.f90s
wave.f90: wave.f90s
wavelet_mod.f90: wavelet_mod.f90s 
extrapolation_type.f90: extrapolation_type.f90s
rtm_section.f90: rtm_section.f90s

include $(top_srcdir)/include/fortran.rules


