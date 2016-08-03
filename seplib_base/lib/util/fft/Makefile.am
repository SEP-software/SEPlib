
EXTRA_DIST = fortstubs.c  fake_fftw.f90s


lib_LTLIBRARIES = libsepfft.la
if HAVE_FORTRAN
lib_LTLIBRARIES += libsepfftf90.la
libsepfftf90_la_SOURCES = sep_fft.f90 cvfft90.c rfft.f90 fake_fftw.f90 \
ft1axis.f90 ftnew.f90 fth.f90 ftu.f90 ft2axis.f90 ftlib1.f90 rowcc.f90 \
fftwflag.f90 fftw.f90
libsepfftf90_la_LIBADD = libsepfft.la ../../corelibs/sep/libsep.la $(FCLIBS) -lm
endif

libsepfft_la_SOURCES = cefft.c refft.c rvfft.c

libsepfft_la_LIBADD = ../../corelibs/sep/libsep.la $(FCLIBS) -lm



include $(top_srcdir)/include/fortran.rules

