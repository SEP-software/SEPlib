project(SEPLIB-interact-Ricksep)
cmake_minimum_required(VERSION 2.8)

include_directories("${CMAKE_CURRENT_BINARY_DIR}/../../seplib_base/lib/corelibs")
include_directories("${CMAKE_CURRENT_SOURCE_DIR}/../../seplib_base/include")
include_directories("${CMAKE_CURRENT_SOURCE_DIR}/../include")
include_directories("${MOTIF_INCLUDE_DIR}")


set(CSOURCES
ano.c
axis.c
colorbar.c
color.c
data.c
draw.c
dummy.c
edit.c
grab_param.c
help.c
main.c
map.c
movie.c
pick.c
pik.c
plane.c
region.c
render.c
rgrow.c
rotated.c
search.c
section.c
semb.c
ui_canvas.c
ui_menu.c
ui_panel.c
ui_window.c
view.c
)


ADD_EXECUTABLE(Ricksep ${CSOURCES})


TARGET_LINK_LIBRARIES(Ricksep ${MOTIF_LIBRARIES} ${XT_LIBRARIES} seppar sep m)

install(FILES Ricksep DESTINATION bin)

