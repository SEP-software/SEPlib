EXTRA_DIST=dipinteg_3Dcos.f90s 
lib_LTLIBRARIES =  
if HAVE_FORTRAN
lib_LTLIBRARIES += libsepdipf90.la 
endif

libsepdipf90_la_LIBADD = $(FFTW_FCLD) \
   ../../class/gee/libsepgeef90.la \
   ../../class/util/libsepclassutilf90.la \
   ../../corelibs/superset/libsuperset.la \
   ../../corelibs/sep3d/libsep3d.la \
   ../../corelibs/sep/libsep.la $(FCLIBS) -lm

libsepdipf90_la_SOURCES = allder3d.f90 divide.f90 grad3_dip.f90 \
allpass3d.f90 find_slope_mod.f90  igrad3_epst.f90 \
model_mask.f90 igrad2_2d_reg.f90 ztrans_mod.f90 dipinteg_3Dcos.f90 \
dipinteg_effic.f90 super_chain_mod.f90


super_chain_mod.o:  igrad2_2d_reg.o model_mask.o igrad3_epst.o


include $(top_srcdir)/include/fortran.rules

