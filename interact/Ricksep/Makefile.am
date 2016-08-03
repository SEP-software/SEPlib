
EXTRA_DIST = main.csep

bin_SCRIPTS = Rickvelan Rick4d Rickmulti

bin_PROGRAMS = Ricksep

Ricksep_SOURCES = axis.c color.c colorbar.c data.c draw.c edit.c help.c \
main.c map.c movie.c pick.c pik.c plane.c region.c render.c section.c \
ui_canvas.c ui_menu.c ui_panel.c ui_window.c view.c ano.c rotated.c \
search.c rgrow.c semb.c dummy.c grab_param.c \
data.h main.h pik.h region.h view.h axis.h draw.h map.h \
plane.h render.h xd.h color.h gridhd.h movie.h rargs.h section.h edit.h \
colorbar.h help.h pick.h rargsf.h ui.h ano.h rotated.h func.h rick.h 

Ricksep_LDADD = $(MYLIBS) $(TOOLKIT_LIBS) -L../../seplib_base/lib/util/par -lseppar -lm 


main.c: main.csep

SUFFIXES = .csep

.csep.c:
	$(SEPDOCIT) -C < $< > $@

