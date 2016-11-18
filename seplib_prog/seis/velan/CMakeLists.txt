project(SEPLIB-prog-seis-filter)
cmake_minimum_required(VERSION 2.8)

include_directories("${CMAKE_CURRENT_BINARY_DIR}/../../../seplib_base/lib/corelibs")
include_directories("${CMAKE_CURRENT_SOURCE_DIR}/../../../seplib_base/include")

include_directories("${CMAKE_CURRENT_SOURCE_DIR}/../../include")
include_directories("${CMAKE_CURRENT_BINARY_DIR}/../../../seplib_base/lib/seis/image")

set(FORTRANSEP 
Hypint.F90sep	 Hypsum.F90sep	Nmo3d.F90sep	Vconvert.F90sep  Vslan.F90sep
Hypmovie.F90sep  MCvfit.F90sep	Stretch.F90sep	Velan3d.F90sep
)

set(CSEP
Velan.csep
)


FOREACH(fort ${FORTRANSEP})
  STRING(REGEX REPLACE ".F90sep\$" ".f90" fortFile "${fort}")
  STRING(REGEX REPLACE ".F90sep\$" "" prog "${fort}")
  set(PROGS "${PROGS} ${prog}")
   ADD_CUSTOM_COMMAND(OUTPUT  "${fortFile}"
     COMMAND  ${CMAKE_CURRENT_SOURCE_DIR}/../../../seplib_base/include/sep_doc_it <${CMAKE_CURRENT_SOURCE_DIR}/${fort} -fortran   |${CMAKE_CURRENT_SOURCE_DIR}/../../../seplib_base/tools/spp/spp ${FORTRAN_FLAGS}  >${fortFile}
     DEPENDS "${fort}")
    ADD_EXECUTABLE(${prog}  ${prog}.f90)
  install(TARGETS ${prog} DESTINATION bin)
ENDFOREACH(fort)


FOREACH(cprog ${CSEP})
  STRING(REGEX REPLACE ".csep\$" ".c" fortFile "${cprog}")
  STRING(REGEX REPLACE ".csep\$" "" prog "${cprog}")
  set(PROGS "${PROGS} ${prog}")
   ADD_CUSTOM_COMMAND(OUTPUT  "${fortFile}"
     COMMAND  ${CMAKE_CURRENT_SOURCE_DIR}/../../../seplib_base/include/sep_doc_it <${CMAKE_CURRENT_SOURCE_DIR}/${cprog} -C  >${fortFile}
     DEPENDS "${cprog}")
    ADD_EXECUTABLE(${prog}  ${prog}.c)
  install(TARGETS ${prog} DESTINATION bin)
    set_target_properties (${prog} PROPERTIES COMPILE_DEFINITIONS SOURCE="${CMAKE_CURRENT_SOURCE_DIR}/${prog}.c")
ENDFOREACH(cprog)



TARGET_LINK_LIBRARIES(Hypint  sepvelan sepfilter sep3d sep)
TARGET_LINK_LIBRARIES(Hypsum  sepvelan sepfilter sep3d sep)
TARGET_LINK_LIBRARIES(Nmo3d  sepvelan sepgeef90 sepaux sepmath superset sep3d sep)
TARGET_LINK_LIBRARIES(Vconvert  sepvelan sepaux sep3d sep)
TARGET_LINK_LIBRARIES(Velan  sepvelan sepaux sep3d sep)
TARGET_LINK_LIBRARIES(Hypmovie  sepvelan sepfilter sep3d sep)
TARGET_LINK_LIBRARIES(MCvfit  sepvelan sepaux sep3d sep)
TARGET_LINK_LIBRARIES(Stretch  sepvelan sepaux sep3d sep)
TARGET_LINK_LIBRARIES(Velan3d  sepvelan   sepgeef90 sepaux sepmath superset  sep3d sep)
TARGET_LINK_LIBRARIES(Vslan  sepvelan sepfft sepmath sepaux sep3d sep)

install(FILES  Unmo Radnmo Radial NMO LMO ${progs} DESTINATION bin)


