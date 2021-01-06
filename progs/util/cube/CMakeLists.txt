project(SEPLIB-prog-util-cube)
cmake_minimum_required(VERSION 3.4)



set(FORTRANSEP Fold3d.F90sep Sort3d.F90sep  Stack3d.F90sep  )

set(CSEP
 Pad.csep      Reverse.csep      Transp.csep
Interleave.csep  Patch.csep    Scat3d.csep     Window3d.csep
SortByHdrs.csep	 Reshape.csep          )


if(CMAKE_Fortran_COMPILER)

FOREACH(fort ${FORTRANSEP})
  STRING(REGEX REPLACE ".F90sep\$" ".f90" fortFile "${fort}")
  STRING(REGEX REPLACE ".F90sep\$" "" prog "${fort}")
  set(PROGS "${PROGS} ${prog}")
   ADD_CUSTOM_COMMAND(OUTPUT  "${fortFile}"
     COMMAND  ${CMAKE_CURRENT_SOURCE_DIR}/../../include/sep_doc_it <${CMAKE_CURRENT_SOURCE_DIR}/${fort} -fortran  >${fortFile}
     DEPENDS "${fort}"
     )
  ADD_EXECUTABLE(${prog} ${fortFile})
  install(TARGETS ${prog} DESTINATION bin)
ENDFOREACH(fort)
set_property(TARGET Fold3d PROPERTY LINKER_LANGUAGE Fortran)
set_property(TARGET Sort3d PROPERTY LINKER_LANGUAGE Fortran)
set_property(TARGET Stack3d PROPERTY LINKER_LANGUAGE Fortran)

TARGET_LINK_LIBRARIES(Fold3d sepaux   sepfft sepmath ${FFTW_LIBRARIES} sep3d sep)
TARGET_LINK_LIBRARIES(Stack3d sepgeef90 superset sep3d sep)
TARGET_LINK_LIBRARIES(Sort3d sepaux sepmath sep3d sep)
if( ${SYMLINK_FOUND} )

install_symlink( "${CMAKE_INSTALL_PREFIX}/bin/Stack3d" "${CMAKE_INSTALL_PREFIX}/bin/Infill3d")
install_symlink( "${CMAKE_INSTALL_PREFIX}/bin/Stack3d" "${CMAKE_INSTALL_PREFIX}/bin/Stack")
install_symlink( "${CMAKE_INSTALL_PREFIX}/bin/Sort3d" "${CMAKE_INSTALL_PREFIX}/bin/Grid_fold")
endif( ${SYMLINK_FOUND} )

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

TARGET_LINK_LIBRARIES(Interleave  sep3d sep)
TARGET_LINK_LIBRARIES(Pad sepaux sepmath sep3d sep m)
TARGET_LINK_LIBRARIES(Reverse  sep3d sep)
TARGET_LINK_LIBRARIES(Transp superset  sep3d sep)
TARGET_LINK_LIBRARIES(Patch  sepaux sepmath sep3d sep m)
TARGET_LINK_LIBRARIES(Scat3d  superset sep3d sep)

TARGET_LINK_LIBRARIES(SortByHdrs sep3d sep)
TARGET_LINK_LIBRARIES(Window3d  superset sep3d sep)
TARGET_LINK_LIBRARIES(Reshape  superset sep3d sep)

install(PROGRAMS ${links} Scat DESTINATION bin)

if( ${SYMLINK_FOUND} )
install_symlink( "${CMAKE_INSTALL_PREFIX}/bin/Window3d" "${CMAKE_INSTALL_PREFIX}/bin/Window")
install_symlink( "${CMAKE_INSTALL_PREFIX}/bin/Stack3d" "${CMAKE_INSTALL_PREFIX}/bin/Stack")
install_symlink( "${CMAKE_INSTALL_PREFIX}/bin/Scat3d" "${CMAKE_INSTALL_PREFIX}/bin/Cat3d")

if(NOT CMAKE_HOST_APPLE)
if(NOT APPLE)
install_symlink( "${CMAKE_INSTALL_PREFIX}/bin/Scat3d" "${CMAKE_INSTALL_PREFIX}/bin/Cat")
endif(NOT APPLE)
endif(NOT CMAKE_HOST_APPLE)
endif( ${SYMLINK_FOUND} )

