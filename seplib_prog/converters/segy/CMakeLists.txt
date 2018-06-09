project(SEPLIB-prog-converters-segy)
cmake_minimum_required(VERSION 2.8)

include_directories("${CMAKE_CURRENT_BINARY_DIR}/../../../seplib_base/lib/corelibs")
include_directories("${CMAKE_CURRENT_SOURCE_DIR}/../../../seplib_base/include")

include_directories("${CMAKE_CURRENT_SOURCE_DIR}/../../include")
include_directories("${CMAKE_CURRENT_BINARY_DIR}/../../../seplib_base/lib/seis/image")
#include_directories("/opt/geotrans3.3/CCS/src/dtcc/CoordinateSystems/misc")
#include_directories("/opt/geotrans3.3/CCS/src/dtcc/CoordinateSystems/utm")
#include_directories("/opt/geotrans3.3/CCS/src/dtcc/CoordinateTuples")
#include_directories("/opt/geotrans3.3/CCS/src/dtcc/CoordinateTuples")
#include_directories("/opt/geotrans3.3/CCS/src/dtcc/Enumerations")
#include_directories("/opt/geotrans3.3/CCS/src/dtcc/Exception")
#include_directories("/opt/geotrans3.3/CCS/src/dtcc")
#include_directories("/opt/tdb-1.2.12/include")

set(FORTRANSEP 
)

set(KMLSRCS
segykml.cpp
)

if(SU_LIBRARIES)
include_directories(${SU_INCLUDES})
set(CSEP
Segy2sep.csep Sep2segy.csep
)
endif(SU_LIBRARIES)


FOREACH(fort ${FORTRANSEP})
  STRING(REGEX REPLACE ".F90sep\$" ".f90" fortFile "${fort}")
  STRING(REGEX REPLACE ".F90sep\$" "" prog "${fort}")
  set(PROGS "${PROGS} ${prog}")
   ADD_CUSTOM_COMMAND(OUTPUT  "${fortFile}"
     COMMAND  ${CMAKE_CURRENT_SOURCE_DIR}/../../../seplib_base/include/sep_doc_it <${CMAKE_CURRENT_SOURCE_DIR}/${fort} -fortran   |${CMAKE_CURRENT_SOURCE_DIR}/../../../seplib_base/tools/spp/spp ${FORTRAN_FLAGS}  >${fortFile}
     DEPENDS "${fort}")
    ADD_EXECUTABLE(${prog}  ${prog}.f90)
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

#FOREACH(cppprog ${KMLSRCS})
#  STRING(REGEX REPLACE ".cpp\$" "" prog "${cppprog}")
##  ADD_EXECUTABLE(${prog} ${cppprog})
#  install(TARGETS ${prog} DESTINATION bin)
#ENDFOREACH(cppprog)

#TARGET_LINK_LIBRARIES(segykml /opt/geotrans3.3/CCS/linux_64/libMSPdtcc.a /opt/tdb-1.2.12/bin/default/libtdb.a)

if(SU_LIBRARIES)
TARGET_LINK_LIBRARIES(Segy2sep  sepsu ${SU_LIBRARIES} superset   sep3d sep)
TARGET_LINK_LIBRARIES(Sep2segy  sepsu ${SU_LIBRARIES} superset  sep3d sep)
endif(SU_LIBRARIES)
install(FILES ${progs} DESTINATION bin)

