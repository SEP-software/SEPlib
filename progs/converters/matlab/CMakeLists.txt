project(SEPLIB-prog-converters-matlab)
cmake_minimum_required(VERSION 3.10)



set(FORTRANSEP 
)

set(CSRCS
Sep2Mat.c
)


FOREACH(fort ${FORTRANSEP})
  STRING(REGEX REPLACE ".F90sep\$" ".f90" fortFile "${fort}")
  STRING(REGEX REPLACE ".F90sep\$" "" prog "${fort}")
  set(PROGS "${PROGS} ${prog}")
   ADD_CUSTOM_COMMAND(OUTPUT  "${fortFile}"
     COMMAND  ${CMAKE_CURRENT_SOURCE_DIR}/../../include/sep_doc_it <${CMAKE_CURRENT_SOURCE_DIR}/${fort} -fortran   |${CMAKE_CURRENT_SOURCE_DIR}/../../libs/include/spp ${FORTRAN_FLAGS}  >${fortFile}
     DEPENDS "${fort}")
    ADD_EXECUTABLE(${prog}  ${prog}.f90)
ENDFOREACH(fort)


FOREACH(cprog ${CSRCS})
  STRING(REGEX REPLACE ".c\$" "" prog "${cprog}")
  set(PROGS "${PROGS} ${prog}")
    ADD_EXECUTABLE(${prog}  ${prog}.c)
    set_target_properties (${prog} PROPERTIES COMPILE_DEFINITIONS SOURCE="${CMAKE_CURRENT_SOURCE_DIR}/${prog}.c")
  install(TARGETS ${prog} DESTINATION bin)
ENDFOREACH(cprog)

TARGET_LINK_LIBRARIES(Sep2Mat   sep3d sep)

install(FILES ${progs} DESTINATION bin)

