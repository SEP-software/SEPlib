bin_SCRIPTS=Sep_cube
EXTRA_DIST = qt_cube.pro.in \
           Sep_cube.py.in\
           makefile \
           autopick.h \
           autopick_2d.h\
           auto_brown.h\
           auto_viteribi.h\
           autopick_menu.h \
           axis.h\
           bar_pt.h \
           buffer.h \
           byte_buffer.h \
           centerwindow.h \
           change.h \
           clip_bar.h \
           color_bar.h \
           clipwindow.h \
           contour.h \
           created_data.h \
           cube.h \
           cube_cut.h \
           dataset.h \
           datasets.h \
           draw_other.h \
           drawwindow.h \
           dynamic.h\
           fastmarch.h\
           float_mmap_buffer.h \
           float_buffer.h \
           float_1d.h\
           float_2d.h\
           help_menu.h \
           hypercube.h\
           hypercube_float.h\
           incore_data.h \
           interval_pick.h \
           io_func.h \
           l2_norm.h\
           lloyd.h\
           lloyd_1d.h\
           main_menu.h \
           menu_bar.h \
           menu_base.h \
           mode.h \
           mouse_func.h\
           mouse_orient.h\
           mouse_pick.h\
           mouse_region.h\
           mouse_zoom.h\
           multiple.h \
           my_colors.h\
           my_score.h\
           my_vector.h\
           navigate_menu.h \
           moved_out.h\
           move_semblance.h\
           nmo_semblance.h\
           nmoed.h\
           norm.h\
           norm_vector.h\
           orient_cube.h \
           orient_map.h \
           orientation_server.h \
           orient_menu.h \
           outcore_data.h \
           pairs_new.h\
           param_func.h\
           part_semb_data.h \
           partial_data.h \
           path.h\
           percentile.h\
           pick_bucket.h \
           pick_new.h \
           pick_menu.h \
           pick_draw.h \
           pick_plane_new.h \
           position.h \
           pqueue.h\
           region_menu.h \
           raster.h \
           region.h \
           region_data.h \
           segy_reg_io.h \
           seispak_io.h \
           seispak_reg_io.h \
           sep_params.h\
           sep_reg_mmap_io.h \
           sep_reg_io.h \
           simple_color.h \
           single.h \
           slice.h \
           slice_types.h \
           sreg.h\
           sregf.h\
           statuswindow.h \
           su_io.h \
           su_reg_io.h \
           surface_data.h\
           three_view.h \
           threeface.h \
           tmp_tree.h\
           trace_io.h \
           tree_info.h\
           updater.h \
           util.h \
           view.h \
           view_menu.h \
           viterbi.h\
           wiggle.h \
           autopick.cpp \
           autopick_2d.cpp\
           auto_brown.cpp\
           auto_viteribi.cpp\
           autopick_menu.cpp \
           axis.cpp\
           buffer.cpp \
           byte_buffer.cpp \
           centerwindow.cpp \
           change.cpp \
           clipwindow.cpp \
           clip_bar.cpp \
           color_bar.cpp\
           contour.cpp \
           created_data.cpp \
           cube.cpp \
           cube_cut.cpp \
           dataset.cpp \
           datasets.cpp \
           draw_other.cpp \
           drawwindow.cpp \
           dynamic.cpp\
           fastmarch.cpp\
           float_1d.cpp\
           float_2d.cpp\
           float_mmap_buffer.cpp \
           float_buffer.cpp \
           help_menu.cpp \
           hypercube.cpp\
           hypercube_float.cpp\
           incore_data.cpp \
           interval_pick.cpp \
           io_func.cpp \
           l2_norm.cpp\
           lloyd.cpp\
           lloyd_1d.cpp\
           main.cpp \
           main_menu.cpp \
           menu_bar.cpp \
           menu_base.cpp \
           mode.cpp \
           mouse_func.cpp\
           mouse_orient.cpp\
           mouse_pick.cpp\
           mouse_region.cpp\
           mouse_zoom.cpp\
           multiple.cpp \
           my_colors.cpp \
           moved_out.cpp\
           move_semblance.cpp\
           nmo_semblance.cpp\
           nmoed.cpp\
           navigate_menu.cpp \
           norm_vector.cpp \
           orient_cube.cpp \
           orient_map.cpp \
           orientation_server.cpp \
           orient_menu.cpp \
           outcore_data.cpp \
           pairs_new.cpp\
           param_func.cpp\
           part_semb_data.cpp \
           partial_data.cpp \
           path.cpp\
           percentile.cpp\
           pick_menu.cpp \
           pick_new.cpp \
           pick_bucket.cpp\
           pick_draw.cpp\
           pick_plane_new.cpp\
           position.cpp \
           pqueue.cpp\
           region.cpp \
           region_menu.cpp \
           region_data.cpp \
           cuemake_image_collection.cpp \
           qrc_qt_cube.cpp \
           raster.cpp \
           segy_reg_io.cpp \
           seispak_reg_io.cpp \
           sep_params.cpp \
           sep_reg_mmap_io.cpp \
           sep_reg_io.cpp \
           simple_color.cpp \
           single.cpp \
           slice.cpp \
           slice_types.cpp \
           sreg.cpp\
           sregf.cpp\
           statuswindow.cpp \
           su_reg_io.cpp \
           surface_data.cpp \
           three_view.cpp \
           threeface.cpp \
           tmp_tree.cpp\
           trace_io.cpp \
           updater.cpp \
           util.cpp \
           view.cpp \
           view_menu.cpp\
           viterbi.cpp\
           wiggle.cpp
#bin_SCRIPTS = 

#bin_PROGRAMS = qt_cube

QMAKE_EXT_OBJ=.$(OBJEXT)

qt-project.pro:
	$(QMAKE) -project -o $@

Makefile.qmake: qt_cube.pro
	$(QMAKE) \
                 QMAKE_EXT_OBJ="$(QMAKE_EXT_OBJ)" \
                 QMAKE_CXX="libtool --mode=compile --tag=CXX $(CXX)" QMAKE_CXXFLAGS="$(CXXFLAGS)" \
                 QMAKE_LINK="libtool --mode=link --tag=CXX $(CXX) $(X_PRE_LIBS) $(LDFLAGS)" \
                 QMAKE_LIBS_X11="$(X_PRE_LIBS) $(LDFLAGS)" \
                 QMAKE_INSTALL_PROGRAM="libtool --mode=install install -m 755 -p " \
                 -o Makefile.qmake qt_cube.pro
#	$(QMAKE) QMAKE_CXX="$(CXX) $(CXXFLAGS)" QMAKE_LINK="$(CXX) $(X_PRE_LIBS) $(LDFLAGS)" CXXFLAGS="$(CXXFLAGS)" -o Makefile.qmake qt_cube.pro

installSEP:
	libtool --mode=install install -m 755 -p qt_cube $(bindir)/qt_cube

all-local: Makefile.qmake
	$(MAKE) -f Makefile.qmake $(AM_MAKEFLAGS) all

install-exec-local: Makefile.qmake
	$(MAKE) -f Makefile.qmake $(AM_MAKEFLAGS) install
	
install-data-local: Makefile.qmake
	@rm -f ${bindir}/qt_cube
	@-@LN_S@ ${addprefix ${bindir}/, qt_cube.app/Contents/MacOS/qt_cube  qt_cube}

check-local: Makefile.qmake
	$(MAKE) -f Makefile.qmake $(AM_MAKEFLAGS) test

clean-local: Makefile.qmake
	$(MAKE) -f Makefile.qmake $(AM_MAKEFLAGS) clean
	rm -f  Makefile.qmake qt_cube
