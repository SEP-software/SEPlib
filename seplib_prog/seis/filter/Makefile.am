
EXTRA_DIST = Again.csep Edit.F90sep Gpow.csep Median.F90sep Pef.F90sep \
Txdec.F90sep Agc.csep Energy.csep Miss.F90sep Smooth.csep Balance.csep \
Envelope.F90sep Halfint.F90sep Spectra.csep Bandpass.csep FFT5D.F90sep \
Helicon.F90sep Mute3d.F90sep Tpow.csep Cfft.F90sep Filter.csep Interp.csep \
Mute.F90sep  Ft3d.csep Lpfilt.csep  \
Trcamp.csep Fx2d.F90sep Noise.F90sep Transf.F90sep Transf_fftw.F90sep MostlyCausal.F90sep Cwt.csep

bin_PROGRAMS = Balance Agc Interp Trcamp Energy Bandpass Smooth Tpow  Cwt
if HAVE_FORTRAN
bin_PROGRAMS += Median Transf Helicon FFT5D Mute3d Pef Miss  Edit \
  Fx2d Txdec Envelope Halfint Ft3d  Mute Noise  Cfft Filter Spectra   Transf_fftw MostlyCausal 
endif

LDADD = $(SEPFILTER) $(SEPMATH) $(SEPLIB3D) -lm
LD_SEPLIBF90 = $(SEPLIBF90) $(FCLIBS) 
LD_GEEF90 = $(GEEF90) $(CLASSUTILF90) $(SEPFFTF90) $(SEPLIB2DF90) $(FCLIBS) -lm
LD_SEPLIB3DF90 = $(SEPLIB3DF90) $(FCLIBS)
LD_SUPERSETF90 = $(SUPERSETF90) $(SEPLIB2DF90)


Edit_SOURCES = Edit.f90
Fx2d_SOURCES = Fx2d.f90


Ft3d_CFLAGS = $(CFLAGS) ${CFCDEFINES} -I$(top_srcdir)/tools/cfortran
Ft3d_LDADD = ${SEPFFTF90} ${SEPLIB} ${SEPMATHF90} ${SEPLIB2DF90} -lm

Fx2d_LDADD = ${SEPLIB2DF90} $(LD_SEPLIBF90) 

FFT5D_SOURCES = FFT5D.f90
FFT5D_LDADD = $(SEPFFTF90) $(SEPAUXF90) $(SEPLIB2DF90) ${SEPMATHF90} $(FFTW_FCLD) $(FCLIBS)

Cfft_SOURCES = Cfft.f90
Cfft_LDADD =  $(SEPLIB2DF90) $(LD_SEPLIBF90)

%M.F90sep: %.F90sep
	cp $*.F90sep $@

Halfint_SOURCES = Halfint.f90
Halfint_LDADD = $(SEPFFTF90) ${SEPFILTERF90} $(GEEF90) $(CLASSUTILF90) ${SEPLIB2DF90} ${SEPAUXF90} \
	${SEPMATHF90} ${SEPLIBF90} $(FCLIBS)

MostlyCausal_SOURCES = MostlyCausal.f90
MostlyCausal_LDADD = $(SEPFFTF90) ${SEPFILTERF90} $(GEEF90) $(CLASSUTILF90) ${SEPLIB2DF90} ${SEPAUXF90} \
	${SEPMATHF90} ${SEPLIBF90} $(FCLIBS)

Txdec_SOURCES = Txdec.f90
Txdec_LDADD =  ${SEPLIB2DF90} $(LD_SEPLIBF90) 

Edit_LDADD = ${SEPLIB2DF90} $(LD_SEPLIBF90)

Envelope_SOURCES = Envelope.f90
Envelope_LDADD = ${SEPFFTF90} ${SEPFILTERF90} $(GEEF90) $(CLASSUTILF90) ${SEPLIB2DF90} ${SEPAUXF90} \
	${SEPMATHF90} $(LD_SEPLIBF90) 

Mute3d_SOURCES = Mute3d.f90
Mute3d_LDADD = $(GEEF90) $(CLASSUTILF90) $(LD_SUPERSETF90) $(LD_SEPLIBF90) ${FCLIBS}

Mute_SOURCES = Mute.f90
Mute_LDADD = $(LD_SEPLIBF90) ${SEPLIB2DF90} ${FCLIBS}

Filter_LDADD = $(SEPFFTF90) $(SEPMATH) $(SEPLIB) -lm

Cwp_LDADD = ${SEPFFTF90} ${SEPMATH} ${SEPLIB} $(SEPMATHF90) ${SEPLIB2DF90}  -lm

Spectra_LDADD = ${SEPFFTF90} ${SEPMATH} ${SEPLIB} $(SEPMATHF90) ${SEPLIB2DF90}  -lm

Pef_SOURCES = Pef.f90
Pef_LDADD = $(LD_GEEF90) ${SEPMATHF90}

Miss_SOURCES = Miss.f90
Miss_LDADD = $(LD_GEEF90) ${SEPMATHF90}

Helicon_SOURCES = Helicon.f90
Helicon_LDADD = $(LD_GEEF90) ${SEPMATHF90}


Transf_SOURCES = Transf.f90
Transf_LDADD = ${SEPFFTF90} $(LD_SUPERSETF90) $(GEEF90) $(CLASSUTILF90) ${SEPFILTERF90} ${SEPMATHF90} ${FCLIBS}

Transf_fftw_SOURCES = Transf_fftw.f90
Transf_fftw_LDADD = ${SEPFFTF90} $(LD_SUPERSETF90) $(GEEF90) $(CLASSUTILF90) ${SEPFILTERF90} ${SEPMATHF90} ${FFTW_FCLD}  ${FCLIBS}

Median_SOURCES = Median.f90
Median_LDADD = ${SEPAUXF90} ${LD_SEPLIB3DF90} $(SEPMATHF90) ${SEPLIB2DF90} ${FCLIBS}

Noise_SOURCES = Noise.f90
Noise_LDADD = $(SEPLIB2DF90) $(SEPMATHF90) $(LD_SEPLIB3DF90) 

Again.c: Again.csep
Agc.c: Agc.csep
Balance.c: Balance.csep
Bandpass.c: Bandpass.csep
Energy.c: Energy.csep
Filter.c: Filter.csep
Ft3d.c: Ft3d.csep
Interp.c: Interp.csep
Gpow.c: Gpow.csep
Lpfilt.c: Lpfilt.csep
Smooth.c: Smooth.csep
Cwp.c: Cwp.csep
Spectra.c: Spectra.csep
Tpow.c: Tpow.csep
Trcamp.c: Trcamp.csep

MostlyCausal.f90: MostlyCausal.f90s
MostlyCausal.f90s: MostlyCausal.F90sep
Edit.f90: Edit.f90s
Edit.f90s: Edit.F90sep
Transf.f90s: Transf.F90sep
Median.f90: Median.f90s
Median.f90s: Median.F90sep
Txdec.f90: Txdec.f90s
Txdec.f90s: Txdec.F90sep
Envelope.f90: Envelope.f90s
Envelope.f90s: Envelope.F90sep
Halfint.f90: Halfint.f90s
Halfint.f90s: Halfint.F90sep
Mute3d.f90: Mute3d.f90s
Mute3d.f90s: Mute3d.F90sep 
Cfft.f90: Cfft.f90s
Cfft.f90s: Cfft.F90sep
Mute.f90: Mute.f90s
Mute.f90s: Mute.F90sep
Fx2d.f90: Fx2d.f90s
Fx2d.f90s: Fx2d.F90sep
Noise.f90: Noise.f90s
Noise.f90s: Noise.F90sep
Transf.f90s: Transf.F90sep
Transf.f90: Transf.f90s
TransfM.f90: TransfM.f90s
TransfM.f90s: TransfM.F90sep
Transf_fftw.f90s: Transf_fftw.F90sep
Transf_fftw.f90: Transf_fftw.f90s

Miss.f90: Miss.f90s
Miss.f90s: Miss.F90sep
FFT5D.f90: FFT5D.f90s 
FFT5D.f90s: FFT5D.F90sep 
Pef.f90: Pef.f90s 
Pef.f90s: Pef.F90sep 
Helicon.f90: Helicon.f90s
Helicon.f90s: Helicon.F90sep

include $(top_srcdir)/include/fortran.rules

