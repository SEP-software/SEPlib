
EXTRA_DIST = params.h round.h vp_pc.h vp_plot.h vp_style.h  \
vp_stdfile.c fortstubs77.c fortstubs90.c

lib_LTLIBRARIES = libvplot.la
if HAVE_FORTRAN
lib_LTLIBRARIES +=  libvplotf90.la
endif

C_SOURCES = name_to_coltab.c vp_arc.c vp_area.c vp_arrow.c vp_bgroup.c vp_break.c \
vp_circle.c vp_clip.c vp_color.c vp_coltab.c vp_dash.c vp_draw.c vp_egroup.c \
vp_endplt.c vp_erase.c vp_fat.c vp_file.c vp_filep.c vp_fill.c vp_gtext.c \
vp_hatchload.c vp_message.c vp_move.c vp_orig.c vp_patload.c vp_pendn.c \
vp_penup.c vp_pline.c vp_plot.c vp_pmark.c vp_purge.c vp_rascol16tab.c \
vp_rascoltab.c vp_raster.c vp_scale.c vp_setdash.c vp_stretch.c vp_style.c \
vp_text.c vp_tfont.c vp_tjust.c vp_uarc.c vp_uarea.c vp_uarrow.c vp_ucircle.c vp_uclip.c \
vp_udraw.c vp_ufill.c vp_ugtext.c vp_umove.c vp_uorig.c vp_upendn.c \
vp_upline.c vp_uplot.c vp_upmark.c vp_uraster.c vp_utext.c vp_where.c \
vp_rastershort.c vp_fixpc.c


CAONLY_SOURCES = geth.c puth.c

CONLY_SOURCES = vp_stdfile.c

libvplot_la_SOURCES = $(C_SOURCES) $(CAONLY_SOURCES) $(CONLY_SOURCES)
libvplotf90_la_SOURCES = fortstubs90.c

libvplotf90_la_LIBADD = libvplot.la
