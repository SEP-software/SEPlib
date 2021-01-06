cmake_minimum_required(VERSION 3.4)
project(SEPLIB-base-tool-makedepend)



set(SCRIPTS vp_Movie   vp_SideBySideAniso
vp_Overlay		      vp_SideBySideIso
pstexpen	vp_OverUnderAniso
vp_annotate vp_Unrotate
Rasterize	vp_OverUnderIso)

install(PROGRAMS ${SCRIPTS} DESTINATION bin)

