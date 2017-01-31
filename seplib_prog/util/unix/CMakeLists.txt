project(SEPLIB-prog-util-header)
cmake_minimum_required(VERSION 2.8)

include_directories("${CMAKE_CURRENT_BINARY_DIR}/../../../seplib_base/lib/corelibs")
include_directories("${CMAKE_CURRENT_SOURCE_DIR}/../../../seplib_base/include")
include_directories("${CMAKE_CURRENT_SOURCE_DIR}/../../include")

set(FORTRANSEP  )

set(CSEP
Scp3d.csep)



FOREACH(fort ${FORTRANSEP})
  STRING(REGEX REPLACE ".F90sep\$" ".f90" fortFile "${fort}")
  STRING(REGEX REPLACE ".F90sep\$" "" prog "${fort}")
  set(PROGS "${PROGS} ${prog}")
   ADD_CUSTOM_COMMAND(OUTPUT  "${fortFile}"
     COMMAND  ${CMAKE_CURRENT_SOURCE_DIR}/../../../seplib_base/include/sep_doc_it <${CMAKE_CURRENT_SOURCE_DIR}/${fort} -fortran  >${fortFile}
     DEPENDS "${fort}"
  install(TARGETS ${prog} DESTINATION bin)
     )
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

TARGET_LINK_LIBRARIES(Scp3d superset sep3d sep)
set(SCRIPTS Sls	 Smv3d	    Srm3d     Zero)

macro(makeLink src dest target)
 add_custom_target(${target} ALL
   COMMAND ${CMAKE_COMMAND} -E create_symlink ${src} ${dest}
    DEPENDS  ${src} COMMENT "mklink ${src} -> ${dest}")
   set(LINKS ${LINKS} ${dest})
endmacro()

makelink(Srm3d Rm3d rm3d_link)
makelink(Srm3d Rm rm_link)
makelink(Scp3d Cp3d Cp3d_link)
makelink(Scp3d Cp cp_link)
makelink(Sls Ls ls_link)


install(PROGRAMS ${progs} ${SCRIPTS} DESTINATION bin)

