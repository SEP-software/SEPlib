include ${SEPINC}/SEP.top
PREPROCESS=yes#whether or not preprocess with cpp
UF90LIBS = -lsep2df90  #not included as a standard library

all:	${BINDIR}/scale_it.x

scaled.H: scale_it.x ../unscaled.HH
	${BINDIR}/scale_it.x scale=1000. < ../unscaled.HH >scaled.H


test: scaled.H
	@echo "Attr of unscaled "
	Attr <../unscaled.HH
	@echo "Attr of scaled version should be scaled 1000."
	Attr <scaled.H

clean:	jclean

include ${SEPINC}/SEP.bottom
