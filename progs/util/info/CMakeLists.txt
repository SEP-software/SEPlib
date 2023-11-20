project(SEPLIB-prog-util-header)
cmake_minimum_required(VERSION 3.10)
include_directories(${SEPCONFIGDIR}/sep)

set(FORTRANSEP Attr3dhead.F90sep Dis3dhead.F90sep 
)

set(CSEP
 Datapath.csep     Disfil.csep  In3d.csep
Attr.csep	    Get.csep	  Sdd.csep
)


if(CMAKE_Fortran_COMPILER)
FOREACH(fort ${FORTRANSEP})
  STRING(REGEX REPLACE ".F90sep\$" ".f90" fortFile "${fort}")
  STRING(REGEX REPLACE ".F90sep\$" "" prog "${fort}")
  set(PROGS "${PROGS} ${prog}")
   ADD_CUSTOM_COMMAND(OUTPUT  "${fortFile}"
     COMMAND  ${CMAKE_CURRENT_SOURCE_DIR}/../../include/sep_doc_it <${CMAKE_CURRENT_SOURCE_DIR}/${fort} -fortran  >${fortFile}
     DEPENDS "${fort}")
  ADD_EXECUTABLE(${prog} ${fortFile})
  install(TARGETS ${prog} DESTINATION bin)
ENDFOREACH(fort)
endif(CMAKE_Fortran_COMPILER)

FOREACH(cprog ${CSEP})
  STRING(REGEX REPLACE ".csep\$" ".c" fortFile "${cprog}")
  STRING(REGEX REPLACE ".csep\$" "" prog "${cprog}")
  set(PROGS "${PROGS} ${prog}")
   ADD_CUSTOM_COMMAND(OUTPUT  "${fortFile}"
     COMMAND  ${CMAKE_CURRENT_SOURCE_DIR}/../../include/sep_doc_it <${CMAKE_CURRENT_SOURCE_DIR}/${cprog} -C  >${fortFile}
     DEPENDS "${cprog}")
    ADD_EXECUTABLE(${prog}  ${prog}.c)
    set_target_properties (${prog} PROPERTIES COMPILE_DEFINITIONS SOURCE="${CMAKE_CURRENT_SOURCE_DIR}/${prog}.c")
  install(TARGETS ${prog} DESTINATION bin)
ENDFOREACH(cprog)

if(CMAKE_Fortran_COMPILER)
set_property(TARGET Dis3dhead PROPERTY LINKER_LANGUAGE Fortran)
set_property(TARGET Attr3dhead PROPERTY LINKER_LANGUAGE Fortran)
TARGET_LINK_LIBRARIES(Dis3dhead sepaux sepmath superset sep3d sep sep3d sep)
TARGET_LINK_LIBRARIES(Attr3dhead sepaux sepmath superset sep3d sep sep3d sep  m)
MESSAGE("SEE FORTRAN COMPILER")
endif(CMAKE_Fortran_COMPILER)

TARGET_LINK_LIBRARIES(Datapath superset sep3d sep)
TARGET_LINK_LIBRARIES(Disfil superset sep3d sep)
TARGET_LINK_LIBRARIES(In3d superset sep3d sep)
TARGET_LINK_LIBRARIES(Attr superset sep3d sep pthread m)

TARGET_LINK_LIBRARIES(Get superset sep3d sep)
TARGET_LINK_LIBRARIES(Sdd superset sep3d sep)


install(PROGRAMS ${progs} DESTINATION bin)

if(SYMLINK_FOUND)
install_symlink( "In3d" "${CMAKE_INSTALL_PREFIX}/bin/In" )
if(NOT CMAKE_HOST_APPLE)
if(NOT APPLE)
install_symlink( "Sdd" "${CMAKE_INSTALL_PREFIX}/bin/Dd" )
endif(NOT APPLE)
endif(NOT CMAKE_HOST_APPLE)
endif(SYMLINK_FOUND)

