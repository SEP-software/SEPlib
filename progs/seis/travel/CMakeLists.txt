cmake_minimum_required(VERSION 2.8)



set(FORTRANSEP 
Gfgradz.F90sep	MTTmaps.F90sep
)

set(CSEP
FMeikonal.csep	Hwt2d.csep  Hwt3d.csep
)

if(CMAKE_Fortran_COMPILER)

FOREACH(fort ${FORTRANSEP})
  STRING(REGEX REPLACE ".F90sep\$" ".f90" fortFile "${fort}")
  STRING(REGEX REPLACE ".F90sep\$" "" prog "${fort}")
  set(PROGS "${PROGS} ${prog}")
   ADD_CUSTOM_COMMAND(OUTPUT  "${fortFile}"
     COMMAND  ${CMAKE_CURRENT_SOURCE_DIR}/../../include/sep_doc_it <${CMAKE_CURRENT_SOURCE_DIR}/${fort} -fortran   |${CMAKE_CURRENT_SOURCE_DIR}/../../../libs/include/spp ${FORTRAN_FLAGS}  >${fortFile}
     DEPENDS "${fort}")
    ADD_EXECUTABLE(${prog}  ${prog}.f90)
  install(TARGETS ${prog} DESTINATION bin)
ENDFOREACH(fort)

TARGET_LINK_LIBRARIES(MTTmaps  sepcwp superset sep3d sep)
TARGET_LINK_LIBRARIES(Gfgradz  sepcwp superset sep3d sep)
endif(CMAKE_Fortran_COMPILER)


FOREACH(cprog ${CSEP})
  STRING(REGEX REPLACE ".csep\$" ".c" fortFile "${cprog}")
  STRING(REGEX REPLACE ".csep\$" "" prog "${cprog}")
  set(PROGS "${PROGS} ${prog}")
   ADD_CUSTOM_COMMAND(OUTPUT  "${fortFile}"
     COMMAND  ${CMAKE_CURRENT_SOURCE_DIR}/../../include/sep_doc_it <${CMAKE_CURRENT_SOURCE_DIR}/${cprog} -C  >${fortFile}
     DEPENDS "${cprog}")
    ADD_EXECUTABLE(${prog}  ${prog}.c)
  install(TARGETS ${prog} DESTINATION bin)
    set_target_properties (${prog} PROPERTIES COMPILE_DEFINITIONS SOURCE="${CMAKE_CURRENT_SOURCE_DIR}/${prog}.c")
ENDFOREACH(cprog)



TARGET_LINK_LIBRARIES(FMeikonal  septravel sepfft sepaux sepmath sep3d sep)
TARGET_LINK_LIBRARIES(Hwt2d  septravel  sepfft sepaux sepmath superset sep3d sep m)
TARGET_LINK_LIBRARIES(Hwt3d  septravel sepfft sepaux sepmath superset sep3d sep m)


install(PROGRAMS ${progs} DESTINATION bin)

