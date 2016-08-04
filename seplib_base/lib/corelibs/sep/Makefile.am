      
#This is what i am calling sep_main_internal, should not
#be availabel to the outside world (e.g. no sep_main_external or fortstubs.)
#If needs to be their, move it to CUBE2, it will make it easier to
#decipher-Bob

CUBE1 = datapath.c expandnm.c fd_io.c file_io.c findnm.c sepfsize.c fullnm.c \
init_io.c isapipe.c isatape.c isclosed.c isordinary.c maketitle.c multifd_io.c \
noheader.c opensock.c redin.c redout.c sepstrindata.c sepstrinhead.c \
sepstrinoutdata.c sepstrinouthead.c sepstroutdata.c sepstrouthead.c \
sepstrsocketdata.c sepstrsockethead.c sepstrscrdata.c sepstrscrhead.c \
helixcart.c sepstrsync.c streamlist.c strformats.c septagstream.c sepfile.c  status.c

CUBE2 = auxclose.c auxin.c hclose.c hcount.c head.c input.c make_unpipe.c \
output.c sepwindow.c slice.c snap.c sreed.c srite.c sseek.c ssize.c sep_err.c \
sepdoc.c noieeeint.c puthead.c putlin.c sepalloc.c seploc.c tetch.c warn.c \
auxputhead.c separg.c fortran_junk.c

#This is what i am calling sep_pars_internal, should not
#be available to the outside world (e.g. no sep_pars_external or fortstubs.)
#If needs to be their, move it to CUBE2, it will make it easier to
#decipher-Bob

CUBE3 = sepgetpar_decode.c putch_format.c sepstrpar.c sepstrput.c sepgetpar_scan.l \
sepgetpar_string_store.c getnumberaxes.c getputaxis.c

CUBE4 = auxpar.c fetch.c hetch.c putch.c auxputch.c sepgetch.c initpar.c math.c

CUBE_CM5 = tmc_diskio.c set_hpf_io.c


lib_LTLIBRARIES = libsep.la

libsep_la_SOURCES = $(CUBE1) $(CUBE2) $(CUBE3) $(CUBE4)
libsep_la_CPPFLAGS = $(AM_CPPFLAGS) -DDEFAULT_DOC_PATH='"'@DEFAULT_DOC_PATH@'"' -I../include
libsep_la_LIBADD = -lm


sep.o: sep_mod.o
sep_io.o: sep_func.o
sep_par.o: sep_func.o
sep_mod.o: sep_io.o sep_par.o sep_func.o
sep_file.o: hypercube.o

if HAVE_FORTRAN
libsep_la_SOURCES += sep_func.f90 sep_io.f90 sep_par.f90  sep_mod.f90 sep.f90  
libsep_la_LIBADD += $(FCLIBS) -lm
endif


include $(top_srcdir)/include/fortran.rules

