cmake_minimum_required(VERSION 2.8)


set(FORTRANSEP 
Hypint.F90sep	 Hypsum.F90sep	Nmo3d.F90sep	Vconvert.F90sep  Vslan.F90sep
Hypmovie.F90sep  MCvfit.F90sep	Stretch.F90sep	Velan3d.F90sep
)

set(CSEP
Velan.csep
)
if(CMAKE_Fortran_COMPILER)
FOREACH(fort ${FORTRANSEP})
  STRING(REGEX REPLACE ".F90sep\$" ".f90" fortFile "${fort}")
  STRING(REGEX REPLACE ".F90sep\$" "" prog "${fort}")
  set(PROGS "${PROGS} ${prog}")
   ADD_CUSTOM_COMMAND(OUTPUT  "${fortFile}"
     COMMAND  ${CMAKE_CURRENT_SOURCE_DIR}/../../include/sep_doc_it <${CMAKE_CURRENT_SOURCE_DIR}/${fort} -fortran   |${CMAKE_CURRENT_SOURCE_DIR}/../../../libs/include/spp ${FORTRAN_FLAGS}  >${fortFile}
     DEPENDS "${fort}")
    ADD_EXECUTABLE(${prog}  ${prog}.f90)
  install(TARGETS ${prog} DESTINATION bin)
ENDFOREACH(fort)
set_property(TARGET Hypint PROPERTY LINKER_LANGUAGE Fortran)
TARGET_LINK_LIBRARIES(Hypint  sepvelan sepfilter sepfft sepmath sep3d sep)
set_property(TARGET Hypsum PROPERTY LINKER_LANGUAGE Fortran)
TARGET_LINK_LIBRARIES(Hypsum  sepvelan sepfilter sepfft sepmath sep3d sep)
set_property(TARGET Nmo3d PROPERTY LINKER_LANGUAGE Fortran)
TARGET_LINK_LIBRARIES(Nmo3d  sepvelan sepfft sepgeef90 sepfilter sepaux sepmath superset sep3d sep)
set_property(TARGET Vconvert PROPERTY LINKER_LANGUAGE Fortran)
TARGET_LINK_LIBRARIES(Vconvert  sepvelan sepfilter  sepfft sepaux sepmath sep3d sep)
set_property(TARGET Hypmovie PROPERTY LINKER_LANGUAGE Fortran)
TARGET_LINK_LIBRARIES(Hypmovie  sepvelan  sepfilter  sepfft sepmath sep3d sep)
set_property(TARGET MCvfit PROPERTY LINKER_LANGUAGE Fortran)
TARGET_LINK_LIBRARIES(MCvfit  sepvelan sepfilter  sepfft sepaux sepmath sepvectorOps sep3d sep)
set_property(TARGET Stretch PROPERTY LINKER_LANGUAGE Fortran)
TARGET_LINK_LIBRARIES(Stretch  sepvelan sepfilter  sepfft sepaux sepmath sep3d sep)
set_property(TARGET Velan3d PROPERTY LINKER_LANGUAGE Fortran)
TARGET_LINK_LIBRARIES(Velan3d  sepvelan sepfilter sepfft sepgeef90 sepaux sepmath superset  sep3d sep)
set_property(TARGET Vslan PROPERTY LINKER_LANGUAGE Fortran)
TARGET_LINK_LIBRARIES(Vslan  sepvelan sepfilter sepfft sepmath sepaux sepmath sep3d sep ${FFTWF_LIBRARIES})
endif(CMAKE_Fortran_COMPILER)

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
TARGET_LINK_LIBRARIES(Velan  sepvelan sepfilter sepfft sepaux sepmath sep3d sep)



install(PROGRAMS  Unmo Radnmo Radial NMO LMO ${progs} DESTINATION bin)


