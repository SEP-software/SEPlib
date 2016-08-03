include ${SEPINC}/SEP.top

UCFLAGS= ${CF77DEFINES}  #the type of fortran compiler controls how strings,
                         #etc are handled.  CF77DEFINES contains info about
                         #the fortran77 compiler

all:	${BINDIR}/scale_it.x


#on most systems the f77 is the most appropriate cross-language
#compiler

${BINDIR}/scale_it.x:	 scale_it.o scale_trace.o
	${F77_LN} 


scaled.H: ${BINDIR}/scale_it.x ../unscaled.HH
	${BINDIR}/scale_it.x scale=1000. < ../unscaled.HH >scaled.H

test: scaled.H
	@echo "Attr of unscaled "
	Attr <../unscaled.HH
	@echo "Attr of scaled version should be scaled 1000."
	Attr <scaled.H


clean:	jclean
	

include ${SEPINC}/SEP.bottom
