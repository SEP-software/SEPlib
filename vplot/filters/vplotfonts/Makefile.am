

bin_PROGRAMS = makefont

FONTS = pen romanc romans cyrilc gothgbt gothgrt gothitt greekc greeks \
italicc italict math misc romand romant scriptc scripts

SRC = $(addsuffix .vplot_font,$(FONTS))
BIN = $(addsuffix .include,$(FONTS))
INC = $(addsuffix .bin,$(FONTS))
OUTPUT = $(BIN) $(INC)

noinst_SCRIPTS = $(BIN)

EXTRA_DIST = $(SRC)

makefont_LDADD = ../../libvplot/libvplot.la

%.bin %.include:	%.vplot_font
	./makefont $* < $*.vplot_font > $*.include
	cat $*_check $*_header $*_dim $*_addr $*_widthl \
		$*_widthr $*_symbol $*_svec $*_lig > $*.bin
	@RM@ $*_check $*_header $*_dim $*_addr $*_widthl \
		$*_widthr $*_symbol $*_svec $*_lig


install-data-local: ${BIN}
	${CP} ${OUTPUT} ${includedir}
	chmod 664 ${addprefix ${includedir}/, ${OUTPUT}}

clean-local: 
	-rm -rf *.bin *.include


uninstall-local:
	${TOUCH} ${addprefix ${includedir}/, ${OUTPUT}}
	${RM} ${addprefix ${includedir}/, ${OUTPUT}}
