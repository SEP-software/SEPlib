project(SEPLIB-interact-RickMovie)
cmake_minimum_required(VERSION 2.8)

include_directories("${CMAKE_CURRENT_BINARY_DIR}/../../seplib_base/lib/corelibs")
include_directories("${CMAKE_CURRENT_SOURCE_DIR}/../../seplib_base/include")
include_directories("${CMAKE_CURRENT_SOURCE_DIR}/../include")


set(CSEP
    sep_axis.c
    sep_colorbar.c
    sep_color.c
    sep_data.c
    sep_draw.c
    sep_edit.c
    sep_help.c
    sep_main.c
    sep_map.c
    sep_movie.c
    sep_pick.c
    sep_pik.c
    sep_plane.c
    sep_region.c
    sep_render.c
    sep_section.c
    sep_ui_canvas.c
    sep_ui_menu.c
    sep_ui_panel.c
    sep_ui_window.c
    sep_view.c
)


#ADD_EXECUTABLE(RickMovie ${CSEP})


#TARGET_LINK_LIBRARIES(RickMovie sep)

#install(FILES RickMovie DESTINATION bin)

