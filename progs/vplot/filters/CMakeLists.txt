
set(VPLOT_FONTDIR ${CMAKE_INSTALL_PREFIX}/include)



add_subdirectory(genlib)
add_subdirectory(utilities)
add_subdirectory(loclib)
add_subdirectory(tseplib)
add_subdirectory(xtlib)
add_subdirectory(pslib)
add_subdirectory(vplib)

if(NETPBM_FOUND)
add_subdirectory(raslib)
endif(NETPBM_FOUND)


set(BASE dovplot.c proc_vplot.c)
set(NOSEPPEN_BASE ${BASE}  main_vplot.c init_vplot.c)
set(SEPPEN_BASE ${BASE} init_vplot_SEP.c main_vplot_SEP.c)
ADD_EXECUTABLE(xtpen ${NOSEPPEN_BASE})
TARGET_LINK_LIBRARIES(xtpen xt_pen  genlib vplotutil loclib  vplot ${X11_XAW} ${X11_XT} ${X11_LIBRARIES} m)

ADD_EXECUTABLE(Sxtpen ${SEPPEN_BASE})
TARGET_LINK_LIBRARIES(Sxtpen xt_pen_SEP   ${X11_XAW} ${X11_XT} ${X11_LIBRARIES} m)


ADD_EXECUTABLE(vppen ${NOSEPPEN_BASE})
TARGET_LINK_LIBRARIES(vppen vp_pen m)

ADD_EXECUTABLE(Svppen ${SEPPEN_BASE})
TARGET_LINK_LIBRARIES(Svppen xt_pen_SEP )


ADD_EXECUTABLE(pspen ${NOSEPPEN_BASE})
TARGET_LINK_LIBRARIES(pspen ps_pen m  )

ADD_EXECUTABLE(Spspen ${SEPPEN_BASE})
TARGET_LINK_LIBRARIES(Spspen ps_pen_SEP)

if(NETPBM_FOUND)
ADD_EXECUTABLE(ppmpen ${NOSEPPEN_BASE})
TARGET_LINK_LIBRARIES(ppmpen ras_pen  m)

#ADD_EXECUTABLE(Sppmpen ${SEPPEN_BASE}  )
#TARGET_LINK_LIBRARIES(Sppmpen ras_pen_SEP sep m )
install(TARGETS  ppmpen Spspen pspen Svppen vppen Sxtpen xtpen  DESTINATION bin)
else(NETPBM_FOUND)
install(TARGETS  Spspen pspen Svppen vppen Sxtpen xtpen  DESTINATION bin)

endif(NETPBM_FOUND)

if(${SYMLINK_FOUND})
install_symlink("${CMAKE_INSTALL_PREFIX}/bin/Spspen" "${CMAKE_INSTALL_PREFIX}/bin/Pspen")
install_symlink("${CMAKE_INSTALL_PREFIX}/bin/Svppen" "${CMAKE_INSTALL_PREFIX}/bin/Vppen")
#install_symlink("Sxtpen" "${CMAKE_INSTALL_PREFIX}/bin/Xtpen")
install_symlink("${CMAKE_INSTALL_PREFIX}/bin/Sxtpen" "${CMAKE_INSTALL_PREFIX}/bin/Stube")
#install_symlink("xtpen" "${CMAKE_INSTALL_PREFIX}/bin/tube")
if(NETPBM_FOUND)
install_symlink("${CMAKE_INSTALL_PREFIX}/bin/Sppmpen" "${CMAKE_INSTALL_PREFIX}/bin/Pmpen")
endif(NETPBM_FOUND)
if(NOT APPLE)
if(NOT CMAKE_HOST_APPLE)
install_symlink("${CMAKE_INSTALL_PREFIX}/bin/Sxtpen" "${CMAKE_INSTALL_PREFIX}/bin/Tube")
endif(NOT CMAKE_HOST_APPLE)
endif(NOT APPLE)
endif(${SYMLINK_FOUND})

