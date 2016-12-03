project(SEPLIB-prog-util-header)
cmake_minimum_required(VERSION 2.8)

include_directories("${CMAKE_CURRENT_BINARY_DIR}/../../../seplib_base/lib/corelibs")
include_directories("${CMAKE_CURRENT_SOURCE_DIR}/../../../seplib_base/include")
include_directories("${CMAKE_CURRENT_SOURCE_DIR}/../../include")


set(FORTRANSEP Solver_ops.F90sep
)

set(CSEP
Clip.csep  Log.csep  Math_base.csep 
)


FOREACH(fort ${FORTRANSEP})
  STRING(REGEX REPLACE ".F90sep\$" ".f90" fortFile "${fort}")
  STRING(REGEX REPLACE ".F90sep\$" "" prog "${fort}")
  set(PROGS "${PROGS} ${prog}")
   ADD_CUSTOM_COMMAND(OUTPUT  "${fortFile}"
     COMMAND  ${CMAKE_CURRENT_SOURCE_DIR}/../../../seplib_base/include/sep_doc_it <${CMAKE_CURRENT_SOURCE_DIR}/${fort} -fortran  >${fortFile}
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
    set_target_properties (${prog} PROPERTIES COMPILE_DEFINITIONS SOURCE="${CMAKE_CURRENT_SOURCE_DIR}/${prog}.c")
    install(TARGETS ${prog} DESTINATION bin)
ENDFOREACH(cprog)



TARGET_LINK_LIBRARIES(Solver_ops sepaux superset sep3d sep)
TARGET_LINK_LIBRARIES(Clip superset sep3d sep)
TARGET_LINK_LIBRARIES(Log superset sep3d sep)
TARGET_LINK_LIBRARIES(Math_base superset sep3d sep)

macro(makeLink src dest target)
 add_custom_target(${target} ALL
   COMMAND ${CMAKE_COMMAND} -E create_symlink ${src} ${dest} 
    DEPENDS  ${src} COMMENT "mklink ${src} -> ${dest}")
   set(LINKS ${LINKS} ${dest})
endmacro()


makelink(Clip Scale clip_target)
makelink(Math_base Cadd cadd_lin)
makelink(Math_base Add add_lin)
makelink(Math_base Pow pow_link)
makelink(Math_base Gpow gpow_lin)
makelink(Math_base Cabs2 cabs2_link)
makelink(Math_base Cabs cabs_lin)
makelink(Math_base Conj conj_link)
makelink(Math_base Imag imag_link)
makelink(Math_base Real real_link)
makelink(Math_base Rtoc rtoc_link)
makelink(Math_base Cmplx cmplx_link)




install(PROGRAMS ${links} ${progs} arithpar DESTINATION bin)

