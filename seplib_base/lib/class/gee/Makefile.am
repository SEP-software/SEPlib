
lib_LTLIBRARIES = 
if HAVE_FORTRAN
lib_LTLIBRARIES += libsepgeef90.la
endif

libsepgeef90_la_LIBADD = ../../corelibs/superset/libsuperset.la ../../corelibs/sep3d/libsep3d.la ../../corelibs/sep/libsep.la $(FCLIBS) -lm

libsepgeef90_la_SOURCES = arnoldi.f90 autocorr.f90 bigsolver.f90\
bin2.f90 binpull1.f90 binpull2.f90 bound.f90 box.f90 broyden.f90\
cartesian.f90 causint.f90 cdoubint.f90 cdstep.f90 cgmeth.f90 cgstep.f90\
chain.f90 combine.f90 compress.f90 conjgrad.f90 conv.f90 copy.f90 createhelixmod.f90\
createmshelixmod.f90 createnhelixmod.f90 crosswilson.f90 ddot.f90\
deburst1.f90 dottest.f90 double.f90 fixbad.f90 fold.f90 gauss.f90 gdecon.f90\
gmres.f90 grad2fill.f90 hconest.f90 helderiv.f90 heliarr.f90 helicon.f90\
helix.f90 helixcartmod.f90 helocut.f90 hipass.f90 hypotenuse.f90\
hypotenusei.f90 icaf1.f90 icai1.f90 igrad1.f90 igrad2.f90 imospray.f90\
int1.f90 int2.f90 interp.f90 interp_new.f90 invint1.f90 invint2.f90\
invstack.f90 irls.f90 iwilson.f90 lace.f90 lapfac.f90 lapfill2.f90\
laplac2.f90 leakint.f90 leakint2.f90 levint.f90 light.f90 lint.f90 lint1.f90\
lint2.f90 llist.f90 loconvol.f90 lolace.f90 lomis.f90 lopef.f90 lsqr.f90\
mask1.f90 mask2i.f90 matmult.f90 medbin2.f90 micaf1.f90 mis1.f90 mis2.f90\
misif.f90 misinput.f90 mkwallwt.f90 mshconest.f90 mshelicon.f90 mshelix.f90\
msmis2.f90 mspef.f90 nbound.f90 nhconest.f90 nhelicon.f90 nhelix.f90\
nicaf1.f90 nmis2.f90 nmisinput.f90 normbin.f90 npef.f90 npolydiv.f90\
parcel.f90 partan.f90 patch.f90 patching.f90 paul.f90 pef.f90 pefconv.f90\
pefest.f90 peftc.f90 polydiv.f90 precsolver.f90 print.f90 quantile.f90 \
random.f90 rediameter.f90 refine2.f90 regrid.f90 regsolver.f90 random2.f90\
scaletrace.f90 signoi.f90 smallsolver.f90 spraysum.f90 steepdip.f90\
steering.f90 tcaf1.f90 tcai1.f90 tent.f90 \
tridiag.f90 triple.f90 tvdec.f90 tvdecon.f90 unbox.f90\
unwrap.f90 vrms2int.f90 vrsolver.f90 weight.f90 weightsolver.f90 wilson.f90\
tcai2.f90 npolydiv2.f90 solver_smp.f90 solver_reg.f90\
solver_prc.f90 smallchain.f90 solver_tiny.f90 solver_report.f90 nfilt_io.f90



include $(top_srcdir)/include/fortran.rules

# module dependencies 

cdstep.o: ddot.o llist.o
triangle1.o: helicon.o polydiv.o
polydiv.o: helix.o
heliarr.o: helicon.o
signoi.o: helicon.o polydiv.o bigsolver.o cgstep.o
mshelix.o: helix.o
wilson.o: helicon.o polydiv.o
createnhelixmod.o: createhelixmod.o nhelix.o nbound.o
peftc.o: tcai1.o tcaf1.o
invstack.o: imospray.o cgstep.o smallsolver.o
lomis.o: mask1.o
crosswilson.o: helicon.o polydiv.o
tvdec.o: leakint2.o nicaf1.o
broyden.o: ddot.o llist.o
invint1.o: lint1.o tcai1.o cgstep.o solver_reg.o
box.o: helix.o cartesian.o
invint2.o: lint1.o helicon.o polydiv.o cgstep.o
deburst1.o: copy.o icai1.o bigsolver.o cgstep.o
createmshelixmod.o: mshelix.o createhelixmod.o bound.o
createhelixmod.o: helix.o cartesian.o
autocorr.o: helix.o compress.o
mshelicon.o: mshelix.o helicon.o
helicon.o: helix.o
tvdecon.o: tvdec.o cgstep.o bigsolver.o
lace.o: createhelixmod.o bound.o pef.o cartesian.o
lapfill2.o: laplac2.o cgstep.o bigsolver.o
bound.o: cartesian.o helicon.o regrid.o
tent.o: cartesian.o
combine.o: patch.o gauss.o mkwallwt.o
steepdip.o: helix.o cartesian.o
rediameter.o: helix.o box.o unbox.o
helderiv.o: lapfac.o helicon.o
patch.o: cartesian.o
imospray.o: hypotenusei.o
helocut.o: lapfac.o helicon.o polydiv.o
iwilson.o: helicon.o polydiv.o
npolydiv.o: nhelix.o
nmisinput.o: nhelicon.o
parcel.o: patch.o
nhelix.o: helix.o
normbin.o: int2.o interp.o
unbox.o: helix.o cartesian.o
compress.o: helix.o
fixbad.o: quantile.o mis2.o helicon.o 
gdecon.o: icaf1.o cgstep.o bigsolver.o
levint.o: tcai1.o peftc.o lint1.o cgstep.o bigsolver.o tcai2.o
mkwallwt.o: patch.o
lopef.o: patch.o misinput.o pef.o
conv.o: helix.o compress.o
misif.o: peftc.o tcai1.o cgstep.o bigsolver.o
misinput.o: helicon.o
partan.o: ddot.o
pef.o: hconest.o cgstep.o bigsolver.o
mspef.o: mshconest.o cgstep.o bigsolver.o
loconvol.o: helicon.o
nhelicon.o: nhelix.o
bigsolver.o: chain.o arnoldi.o llist.o ddot.o
steering.o: helix.o
pefconv.o: helicon.o hconest.o
mshconest.o: mshelix.o hconest.o
hconest.o: helix.o
vrms2int.o: causint.o cgstep.o bigsolver.o weight.o
nbound.o: nhelix.o
pefest.o: quantile.o helicon.o misinput.o pef.o
lint.o: tridiag.o
light.o: igrad1.o
nmis2.o: nhelicon.o npolydiv.o mask1.o cgstep.o bigsolver.o
print.o: box.o helix.o cartesian.o
grad2fill.o: igrad2.o cgstep.o bigsolver.o
cgmeth.o: matmult.o cgstep.o solver_tiny.o
mis1.o: tcai1.o
refine2.o: lint2.o
solver_smp.o: smallchain.o solver_report.o
mis2.o: mask1.o helicon.o polydiv.o cgstep.o solver_smp.o solver_prc.o \
solver_reg.o
solver_reg.o: smallchain.o
solver_smp.o: smallchain.o
solver_prc.o: smallchain.o
msmis2.o: mshelicon.o cgstep.o bigsolver.o
arnoldi.o: ddot.o llist.o
unwrap.o: cgstep.o igrad2.o smallsolver.o
regrid.o: helix.o cartesian.o
nfilt_io.o: regrid.o nhelix.o
patch.o: cartesian.o
lapfac.o: wilson.o
mask2i.o: mask1.o helicon.o heliarr.o cgstep.o regsolver.o
npef.o: nhconest.o npolydiv.o cgstep.o bigsolver.o npolydiv2.o
leakint2.o: leakint.o
cdoubint.o: causint.o chain.o
patching.o: patch.o mkwallwt.o
laplac2.o: igrad2.o
lolace.o: createhelixmod.o bound.o pef.o cartesian.o patch.o
gmres.o: ddot.o llist.o
nhconest.o: nhelix.o
npolydiv2.o: npolydiv.o

cdstep.lo: ddot.lo llist.lo
triangle1.lo: helicon.lo polydiv.lo
polydiv.lo: helix.lo
heliarr.lo: helicon.lo
signoi.lo: helicon.lo polydiv.lo bigsolver.lo cgstep.lo
mshelix.lo: helix.lo
wilson.lo: helicon.lo polydiv.lo
createnhelixmod.lo: createhelixmod.lo nhelix.lo nbound.lo
peftc.lo: tcai1.lo tcaf1.lo
invstack.lo: imospray.lo cgstep.lo smallsolver.lo
lomis.lo: mask1.lo
crosswilson.lo: helicon.lo polydiv.lo
tvdec.lo: leakint2.lo nicaf1.lo
broyden.lo: ddot.lo llist.lo
invint1.lo: lint1.lo tcai1.lo cgstep.lo solver_reg.lo
box.lo: helix.lo cartesian.lo
invint2.lo: lint1.lo helicon.lo polydiv.lo cgstep.lo
deburst1.lo: copy.lo icai1.lo bigsolver.lo cgstep.lo
createmshelixmod.lo: mshelix.lo createhelixmod.lo bound.lo
createhelixmod.lo: helix.lo cartesian.lo
autocorr.lo: helix.lo compress.lo
mshelicon.lo: mshelix.lo helicon.lo
helicon.lo: helix.lo
tvdecon.lo: tvdec.lo cgstep.lo bigsolver.lo
lace.lo: createhelixmod.lo bound.lo pef.lo cartesian.lo
lapfill2.lo: laplac2.lo cgstep.lo bigsolver.lo
bound.lo: cartesian.lo helicon.lo regrid.lo
tent.lo: cartesian.lo
combine.lo: patch.lo gauss.lo mkwallwt.lo
steepdip.lo: helix.lo cartesian.lo
rediameter.lo: helix.lo box.lo unbox.lo
helderiv.lo: lapfac.lo helicon.lo
patch.lo: cartesian.lo
imospray.lo: hypotenusei.lo
helocut.lo: lapfac.lo helicon.lo polydiv.lo
iwilson.lo: helicon.lo polydiv.lo
npolydiv.lo: nhelix.lo
nmisinput.lo: nhelicon.lo
parcel.lo: patch.lo
nhelix.lo: helix.lo
cdoubint.lo: causint.lo chain.lo
normbin.lo: int2.lo interp.lo
unbox.lo: helix.lo cartesian.lo
compress.lo: helix.lo
fixbad.lo: quantile.lo mis2.lo helicon.lo 
gdecon.lo: icaf1.lo cgstep.lo bigsolver.lo
levint.lo: tcai1.lo peftc.lo lint1.lo cgstep.lo bigsolver.lo tcai2.lo
mkwallwt.lo: patch.lo
lopef.lo: patch.lo misinput.lo pef.lo
conv.lo: helix.lo compress.lo
misif.lo: peftc.lo tcai1.lo cgstep.lo bigsolver.lo
misinput.lo: helicon.lo
partan.lo: ddot.lo
pef.lo: hconest.lo cgstep.lo bigsolver.lo
mspef.lo: mshconest.lo cgstep.lo bigsolver.lo
loconvol.lo: helicon.lo
nhelicon.lo: nhelix.lo
bigsolver.lo: chain.lo arnoldi.lo llist.lo ddot.lo
steering.lo: helix.lo
pefconv.lo: helicon.lo hconest.lo
mshconest.lo: mshelix.lo hconest.lo
hconest.lo: helix.lo
micaf1.lo: 
vrms2int.lo: causint.lo cgstep.lo bigsolver.lo weight.lo
nbound.lo: nhelix.lo
pefest.lo: quantile.lo helicon.lo misinput.lo pef.lo
lint.lo: tridiag.lo
light.lo: igrad1.lo
nmis2.lo: nhelicon.lo npolydiv.lo mask1.lo cgstep.lo bigsolver.lo
print.lo: box.lo helix.lo cartesian.lo
grad2fill.lo: igrad2.lo cgstep.lo bigsolver.lo
cgmeth.lo: matmult.lo cgstep.lo solver_tiny.lo
mis1.lo: tcai1.lo
refine2.lo: lint2.lo
solver_smp.lo: smallchain.lo solver_report.lo
mis2.lo: mask1.lo helicon.lo polydiv.lo cgstep.lo solver_smp.lo solver_prc.lo \
solver_reg.lo
solver_reg.lo: smallchain.lo
solver_smp.lo: smallchain.lo
solver_prc.lo: smallchain.lo
msmis2.lo: mshelicon.lo cgstep.lo bigsolver.lo
arnoldi.lo: ddot.lo llist.lo
unwrap.lo: cgstep.lo igrad2.lo smallsolver.lo
regrid.lo: helix.lo cartesian.lo
nfilt_io.lo: regrid.lo nhelix.lo
patch.lo: cartesian.lo
lapfac.lo: wilson.lo
mask2i.lo: mask1.lo helicon.lo heliarr.lo cgstep.lo regsolver.lo
npef.lo: nhconest.lo npolydiv.lo cgstep.lo bigsolver.lo npolydiv2.lo
leakint2.lo: leakint.lo
patching.lo: patch.lo mkwallwt.lo
laplac2.lo: igrad2.lo
lolace.lo: createhelixmod.lo bound.lo pef.lo cartesian.lo patch.lo
gmres.lo: ddot.lo llist.lo
nhconest.lo: nhelix.lo
npolydiv2.lo: npolydiv.lo

PHONY : FORCE

FORCE: ;

update: FORCE
	cp $(addprefix $(GEEHOME)/,$(SRCS)) .
	chmod 666 $(SRCS)


