
lib_LTLIBRARIES = 
#if HAVE_FORTRAN
lib_LTLIBRARIES += libsepclassutilf90.la
#endif

libsepclassutilf90_la_LIBADD = ../../corelibs/sep/libsep.la $(FCLIBS) -lm

libsepclassutilf90_la_SOURCES = adjnull.f90 boxconv.f90 boxmo.f90 cadd.f90 causint.f90 cinterp1.f90 contran.f90 copy.f90 ctris.f90 diag.f90 ft1axis.f90 ft2axis.f90 ft3D.f90 fth.f90 ftu.f90 halfdifa.f90 ident.f90 igrad1.f90 matmult.f90 nmo1.f90 null.f90 pad2.f90 quantile.f90 rand01.f90 ruffen1.f90 signum.f90 simpleft.f90 spot0.f90 spot1.f90 stack1.f90 triangle2.f90 triangle.f90 zpad1.f90 classutil.f90

include $(top_srcdir)/include/fortran.rules

# module dependencies 

boxmo.o: adjnull.o null.o causint.o
boxmo.lo: adjnull.lo null.lo causint.lo
matmult.o: adjnull.o
matmult.lo: adjnull.lo
nmo1.o: adjnull.o
nmo1.lo: adjnull.lo
stack1.o: adjnull.o nmo1.o
stack1.lo: adjnull.lo nmo1.lo
triangle2.o: triangle.o
triangle2.lo: triangle.lo
triangle.o: boxconv.o
triangle.lo: boxconv.lo
zpad1.o: adjnull.o
zpad1.lo: adjnull.lo

PHONY : FORCE

FORCE: ;

clean-local: 
	$(RM) -f $(patsubst %.r90,%.f90,$(wildcard *.r90))

update: FORCE
	cp $(addprefix $(GEEHOME)/,$(SRCS)) .
	chmod 666 $(SRCS)
