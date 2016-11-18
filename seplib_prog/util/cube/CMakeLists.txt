project(SEPLIB-prog-util-cube)
cmake_minimum_required(VERSION 2.8)

include_directories("${CMAKE_CURRENT_BINARY_DIR}/../../../seplib_base/lib/corelibs")
include_directories("${CMAKE_CURRENT_SOURCE_DIR}/../../../seplib_base/include")
include_directories("${CMAKE_CURRENT_SOURCE_DIR}/../../include")

set(FORTRANSEP Fold3d.F90sep	 Stack3d.F90sep  )

set(CSEP
 Pad.csep      Reverse.csep      Transp.csep
Interleave.csep  Patch.csep    Scat3d.csep     Window3d.csep
	 Reshape.csep          )



FOREACH(fort ${FORTRANSEP})
  STRING(REGEX REPLACE ".F90sep\$" ".f90" fortFile "${fort}")
  STRING(REGEX REPLACE ".F90sep\$" "" prog "${fort}")
  set(PROGS "${PROGS} ${prog}")
   ADD_CUSTOM_COMMAND(OUTPUT  "${fortFile}"
     COMMAND  ${CMAKE_CURRENT_SOURCE_DIR}/../../../seplib_base/include/sep_doc_it <${CMAKE_CURRENT_SOURCE_DIR}/${fort} -fortran  >${fortFile}
     DEPENDS "${fort}"
     )
  ADD_EXECUTABLE(${prog} ${fortFile})
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
    set_target_properties (${prog} PROPERTIES COMPILE_DEFINITIONS SOURCE="${CMAKE_CURRENT_SOURCE_DIR}/${prog}.c")
  install(TARGETS ${prog} DESTINATION bin)
ENDFOREACH(cprog)

TARGET_LINK_LIBRARIES(Fold3d sepaux sep3d sep)
TARGET_LINK_LIBRARIES(Stack3d superset sep3d sep)
TARGET_LINK_LIBRARIES(Interleave  sep3d sep)
TARGET_LINK_LIBRARIES(Pad  sepaux sep3d sep)
TARGET_LINK_LIBRARIES(Reverse  sep3d sep)
TARGET_LINK_LIBRARIES(Transp superset  sep3d sep)
TARGET_LINK_LIBRARIES(Patch  sepaux sep3d sep)
TARGET_LINK_LIBRARIES(Scat3d  superset sep3d sep)
TARGET_LINK_LIBRARIES(Window3d  superset sep3d sep)
TARGET_LINK_LIBRARIES(Reshape  superset sep3d sep)


