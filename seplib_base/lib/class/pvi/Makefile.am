
lib_LTLIBRARIES = 
if HAVE_FORTRAN
lib_LTLIBRARIES += libseppvif90.la
endif

libseppvif90_la_LIBADD = ../util/libsepclassutilf90.la ../../corelibs/superset/libsuperset.la ../../corelibs/sep3d/libsep3d.la ../../corelibs/sep/libsep.la $(FCLIBS) -lm

libseppvif90_la_SOURCES = pvi.f90 \
advance.f90 burg2.f90 burg.f90 butter.f90 causint2.f90 cgmeth.f90 cgstep.f90 cinjof.f90 cinlof.f90 cinloip.f90 cinloi.f90 cinloiwt.f90 conjnull.f90 contrunc.f90 convin.f90 convolve.f90 deghost.f90 ftderivslow.f90 ftlagslow.f90 hestenes.f90 hope.f90 imo1.f90 imospray.f90 iner.f90 interp0.f90 invstack.f90 kolmogoroff.f90 leak.f90 leaky.f90 lomoplan.f90 misfip.f90 miss1.f90 miss2.f90 missif.f90 mkwallwt.f90 moplan.f90 mpwave.f90 nonstat2.f90 nonstat.f90 parcel.f90 patch.f90 pe2.f90 polydiv.f90 polyft.f90 pop.f90 puck.f90 scaleit.f90 shaper.f90 slider.f90 slowft.f90 tris.f90 vspray.f90 wavekill1.f90 wcontrunc.f90 zero.f90



include $(top_srcdir)/include/fortran.rules

# module dependencies 

PHONY : FORCE

FORCE: ;

clean-local: 
	$(RM) -f $(patsubst %.r90,%.f90,$(wildcard *.r90))

update: FORCE
	cp $(addprefix $(GEEHOME)/,$(SRCS)) .
	chmod 666 $(SRCS)

