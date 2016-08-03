
lib_LTLIBRARIES = 
if HAVE_FORTRAN
lib_LTLIBRARIES += libsepbeif90.la
endif

libsepbeif90_la_LIBADD = ../util/libsepclassutilf90.la ../../corelibs/superset/libsuperset.la ../../corelibs/sep3d/libsep3d.la ../../corelibs/sep/libsep.la $(FCLIBS) -lm

libsepbeif90_la_SOURCES =  bei.f90 \
aamig.f90 causint2.f90 \
cosmig.f90 dmokirch.f90 doubint.f90 dpbin2.f90 eiktau.f90  \
flathyp.f90 ft1axe.f90 gazadj.f90 \
kdmoslow.f90 kirchfast.f90 kirchslow.f90 \
lint1.f90 lmo.f90 matmul.f90 mutter1.f90 mutter.f90 nmo0.f90 \
phasemig.f90 phasemod.f90 rms2int.f90 \
rtris.f90 scale.f90 slowfit.f90 \
spotw.f90 stack0.f90 stoltmig.f90 stoltmod.f90 synmarine.f90 \
trimo.f90 tristack.f90 velsimp.f90 veltran.f90 \
vint2rms.f90 wavemovie.f90 zero.f90 


include $(top_srcdir)/include/fortran.rules

# module dependencies 

aamig.o: trimo.o
aamig.lo: trimo.lo
gazadj.o: eiktau.o
gazadj.lo: eiktau.lo
stack0.o: nmo0.o
stack0.lo: nmo0.lo
trimo.o: doubint.o spotw.o
trimo.lo: doubint.lo spotw.lo
tristack.o: trimo.o
tristack.lo: trimo.lo

PHONY : FORCE

FORCE: ;

clean-local: 
	$(RM) -f $(patsubst %.r90,%.f90,$(wildcard *.r90))

update: FORCE
	cp $(addprefix $(GEEHOME)/,$(SRCS)) .
	chmod 666 $(SRCS)

