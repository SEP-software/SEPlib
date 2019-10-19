
set(FORTRANSEP 
Dip_azim.F90sep  
#Seis_vel.F90sep
)

set(CSEP
Box.csep       Dots.csep    Grey.csep	      Operplot.csep  
Contour.csep   Ftplot.csep  Histogram.csep    Overlay.csep   Thplot.csep
Cubeplot.csep  Graph.csep   Merge_field.csep    Wiggle.csep
)


if(CMAKE_Fortran_COMPILER)
FOREACH(fort ${FORTRANSEP})
  STRING(REGEX REPLACE ".F90sep\$" ".f90" fortFile "${fort}")
  STRING(REGEX REPLACE ".F90sep\$" "" prog "${fort}")
  set(PROGS "${PROGS} ${prog}")
   ADD_CUSTOM_COMMAND(OUTPUT  "${fortFile}"
     COMMAND  ${CMAKE_CURRENT_SOURCE_DIR}/../include/sep_doc_it <${CMAKE_CURRENT_SOURCE_DIR}/${fort} -fortran   |${CMAKE_CURRENT_SOURCE_DIR}/../include/spp ${FORTRAN_FLAGS}  >${fortFile}
     DEPENDS "${fort}")
    ADD_EXECUTABLE(${prog}  ${prog}.f90)
  install(TARGETS ${prog} DESTINATION bin)
ENDFOREACH(fort)
TARGET_LINK_LIBRARIES(Dip_azim glplot vplot sep3d sep)
#TARGET_LINK_LIBRARIES(Seis_vel glplot vplot sep3d sep)
endif(CMAKE_Fortran_COMPILER)


FOREACH(cprog ${CSEP})
  STRING(REGEX REPLACE ".csep\$" ".c" fortFile "${cprog}")
  STRING(REGEX REPLACE ".csep\$" "" prog "${cprog}")
  set(PROGS "${PROGS} ${prog}")
   ADD_CUSTOM_COMMAND(OUTPUT  "${fortFile}"
     COMMAND  ${CMAKE_CURRENT_SOURCE_DIR}/../include/sep_doc_it <${CMAKE_CURRENT_SOURCE_DIR}/${cprog} -C  >${fortFile}
     DEPENDS "${cprog}")
    ADD_EXECUTABLE(${prog}  ${prog}.c)
  install(TARGETS ${prog} DESTINATION bin)
    set_target_properties (${prog} PROPERTIES COMPILE_DEFINITIONS SOURCE="${CMAKE_CURRENT_SOURCE_DIR}/${prog}.c")
ENDFOREACH(cprog)



TARGET_LINK_LIBRARIES(Box glplot vplot sep3d sep)
TARGET_LINK_LIBRARIES(Dots glplot vplot sep3d sep)
TARGET_LINK_LIBRARIES(Grey glplot vplot sep3d sep)
TARGET_LINK_LIBRARIES(Operplot glplot vplot sep3d sep)
TARGET_LINK_LIBRARIES(Contour glplot vplot sep3d sep)
TARGET_LINK_LIBRARIES(Ftplot  glplot vplot sep3d sep)
TARGET_LINK_LIBRARIES(Histogram glplot vplot sep3d sep)
TARGET_LINK_LIBRARIES(Overlay  glplot vplot sep3d sep)
TARGET_LINK_LIBRARIES(Thplot  glplot vplot sep3d sep)
TARGET_LINK_LIBRARIES(Cubeplot glplot vplot sep3d sep)
TARGET_LINK_LIBRARIES(Graph glplot vplot sep3d sep)
TARGET_LINK_LIBRARIES(Merge_field glplot vplot sep3d sep)
TARGET_LINK_LIBRARIES(Wiggle glplot vplot sep3d sep)

install(FILES ${progs} DESTINATION bin)

