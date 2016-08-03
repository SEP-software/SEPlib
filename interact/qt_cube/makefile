all:
	make -f Makefile Makefile.qmake
	make -f Makefile.qmake LINK=echo
	make -f Makefile.qmake OBJECTS="*.lo" TARGET="qt_cube"

install:
	rm -f Makefile.qmake
	make -f Makefile Makefile.qmake QMAKE_EXT_OBJ=".lo"
	make -f Makefile.qmake TARGET="qt_cube"
	make -f Makefile installSEP
	make -f Makefile install-binSCRIPTS

clean:
	-make -f Makefile.qmake clean
	rm -f *.lo
	rm -rf .libs
	rm -f Makefile.qmake
	rm -f qt_cube
