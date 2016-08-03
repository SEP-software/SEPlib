RATF90=no #set to compile with old SEPlib f77 rules
include ${SEPINC}/SEP.top

all:	${BINDIR}/scale_it.x

scaled.H: ${BINDIR}/scale_it.x ../unscaled.HH
	${BINDIR}/scale_it.x scale=1000. < ../unscaled.HH >scaled.H

test: scaled.H
	@echo "Attr of unscaled "
	Attr <../unscaled.HH
	@echo "Attr of scaled version should be scaled 1000."
	Attr <scaled.H


clean:	jclean
	

include ${SEPINC}/SEP.bottom
