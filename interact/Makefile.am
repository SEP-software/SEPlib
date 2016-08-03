
ACLOCAL_AMFLAGS = -I m4

m4sources = m4/ac_check_ftype.m4 m4/ac_module_extensions_fc.m4 \
m4/ac_path_motif.m4 m4/ac_path_motif_direct.m4 m4/find_sep_arch.m4 \
m4/make_gmake.m4 m4/sep_fc.m4 m4/sep_lib_defs.m4

EXTRA_DIST = $(m4sources)

SUBDIRS = include 
if FOUND_MOTIF
SUBDIRS+=Ricksep RickMovie
endif
if HAVE_QT
SUBDIRS +=qt_cube # vtk
endif
