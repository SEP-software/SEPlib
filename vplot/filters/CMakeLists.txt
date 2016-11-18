project(SEPLIB-vplot-filters)
cmake_minimum_required(VERSION 2.8)

set(VPLOT_FONTDIR ${CMAKE_INSTALL_PREFIX}/include)


add_subdirectory(vplotfonts)
add_subdirectory(genlib)
add_subdirectory(utilities)
add_subdirectory(loclib)
add_subdirectory(tseplib)
add_subdirectory(xtlib)
add_subdirectory(pslib)
add_subdirectory(raslib)
add_subdirectory(vplib)

INCLUDE_DIRECTORIES(${X11_INCLUDE_DIR})
INCLUDE_DIRECTORIES(${CMAKE_CURRENT_SOURCE_DIR}/../../seplib_base/include)
INCLUDE_DIRECTORIES(${CMAKE_CURRENT_SOURCE_DIR}/../../seplib_prog/include)
set(BASE dovplot.c proc_vplot.c)
set(NOSEPPEN_BASE ${BASE}  main_vplot.c init_vplot.c)
set(SEPPEN_BASE ${BASE} init_vplot_SEP.c main_vplot_SEP.c)
ADD_EXECUTABLE(xtpen ${NOSEPPEN_BASE})
TARGET_LINK_LIBRARIES(xtpen xt_pen  genlib vplotutil loclib  vplot ${X11_XAW} ${X11_XT} ${X11_LIBRARIES} m)

ADD_EXECUTABLE(Sxtpen ${SEPPEN_BASE})
TARGET_LINK_LIBRARIES(Sxtpen xt_pen_SEP  genlib vplotutil loclib  vplot tseplib sep ${X11_XAW} ${X11_XT} ${X11_LIBRARIES} m)


ADD_EXECUTABLE(vppen ${NOSEPPEN_BASE})
TARGET_LINK_LIBRARIES(vppen vp_pen  genlib vplotutil loclib  vplot ${X11_XAW} ${X11_XT} ${X11_LIBRARIES} m)

ADD_EXECUTABLE(Svppen ${SEPPEN_BASE})
TARGET_LINK_LIBRARIES(Svppen xt_pen_SEP  genlib vplotutil loclib  vplot tseplib sep ${X11_XAW} ${X11_XT} ${X11_LIBRARIES} m)


ADD_EXECUTABLE(pspen ${NOSEPPEN_BASE})
TARGET_LINK_LIBRARIES(pspen ps_pen  genlib vplotutil loclib  vplot ${X11_XAW} ${X11_XT} ${X11_LIBRARIES} m)

ADD_EXECUTABLE(Spspen ${SEPPEN_BASE})
TARGET_LINK_LIBRARIES(Spspen ps_pen_SEP  genlib vplotutil loclib  vplot tseplib sep ${X11_XAW} ${X11_XT} ${X11_LIBRARIES} m)


ADD_EXECUTABLE(raspen ${NOSEPPEN_BASE})
TARGET_LINK_LIBRARIES(raspen ps_pen  genlib vplotutil loclib  vplot ${X11_XAW} ${X11_XT} ${X11_LIBRARIES} m)

ADD_EXECUTABLE(Sraspen ${SEPPEN_BASE})
TARGET_LINK_LIBRARIES(Sraspen ras_pen_SEP  genlib vplotutil loclib  vplot tseplib sep ${X11_XAW} ${X11_XT} ${X11_LIBRARIES} m)



