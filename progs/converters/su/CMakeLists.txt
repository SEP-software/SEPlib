project(SEPLIB-prog-converters-su)
cmake_minimum_required(VERSION 2.8)


set(FORTRANSEP 
)

if(SU_LIBRARIES)
include_directories(${SU_INCLUDES})
set(CSEP
Sep2su.csep Su2sep.csep
)
endif(SU_LIBRARIES)




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


if(SU_LIBRARIES)
TARGET_LINK_LIBRARIES(Sep2su  sepsu superset   sep3d sep ${SU_LIBRARIES})
TARGET_LINK_LIBRARIES(Su2sep  sepsu superset  sep3d sep ${SU_LIBRARIES})
endif(SU_LIBRARIES)
install(FILES ${progs} DESTINATION bin)

