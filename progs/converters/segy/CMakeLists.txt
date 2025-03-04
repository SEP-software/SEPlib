project(SEPLIB-prog-converters-segy)
cmake_minimum_required(VERSION 3.10)

if (CCS_INCLUDES)
if (TDB_INCLUDE)
include_directories(${CCS_INCLUDES})
include_directories(${TDB_INCLUDE})
endif (TDB_INCLUDE)
endif (CCS_INCLUDES)

set(FORTRANSEP 
)

if (CCS_INCLUDES)
if (TDB_INCLUDE)
set(KMLSRCS
segykml.cpp
)
endif (TDB_INCLUDE)
endif (CCS_INCLUDES)

if(SU_LIBRARIES)
include_directories(${SU_INCLUDES})
set(CSEP
Segy2sep.csep Sep2segy.csep
)
endif(SU_LIBRARIES)

find_package(Tdb)
find_package(CCS)


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

FOREACH(cppprog ${KMLSRCS})
  STRING(REGEX REPLACE ".cpp\$" "" prog "${cppprog}")
   message(${prog})
    ADD_EXECUTABLE(${prog} ${cppprog})
  install(TARGETS ${prog} DESTINATION bin)
ENDFOREACH(cppprog)

if (CCS_INCLUDES)
if (TDB_INCLUDE)
#TARGET_LINK_LIBRARIES(segykml ${CCS_LIBRARIES} ${TDB_LIBRARY})
endif (TDB_INCLUDE)
endif (CCS_INCLUDES)

if(SU_LIBRARIES)
TARGET_LINK_LIBRARIES(Segy2sep  sepsu ${SU_LIBRARIES} superset   sep3d sep)
TARGET_LINK_LIBRARIES(Sep2segy  sepsu ${SU_LIBRARIES} superset  sep3d sep)
endif(SU_LIBRARIES)
install(FILES ${progs} DESTINATION bin)

