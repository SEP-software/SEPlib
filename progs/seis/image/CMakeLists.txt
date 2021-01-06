cmake_minimum_required(VERSION 3.4)

find_package(Boost REQUIRED)
find_package(TBB REQUIRED)

set(FORTRANSEP AMO.F90sep Lloyd_vel.F90sep Stolt.F90sep)

if(FFTWF_LIBRARIES)
  set(FORTRANSEP
      ${FORTRANSEP}
      CAM.F90sep
      Phase.F90sep
      OFF2ANG.F90sep
      SRM.F90sep)
endif(FFTWF_LIBRARIES)

set(CSEP Kirch_2d_depth.csep)
set(CXXSEP Kirch_3d_time.cppsep)

#include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../libs/seis/image-cpp)

if(CMAKE_Fortran_COMPILER)

  foreach(fort ${FORTRANSEP})
    string(REGEX
           REPLACE ".F90sep\$"
                   ".f90"
                   fortFile
                   "${fort}")
    string(REGEX
           REPLACE ".F90sep\$"
                   ""
                   prog
                   "${fort}")
    set(PROGS "${PROGS} ${prog}")
    add_custom_command(
      OUTPUT "${fortFile}"
      COMMAND ${CMAKE_CURRENT_SOURCE_DIR}/../../include/sep_doc_it
              <${CMAKE_CURRENT_SOURCE_DIR}/${fort} -fortran
              |${CMAKE_CURRENT_SOURCE_DIR}/../../../libs/include/spp ${FORTRAN_FLAGS}
              >${fortFile}
      DEPENDS "${fort}")
    add_executable(${prog} ${prog}.f90)
    install(TARGETS ${prog} DESTINATION bin)
  endforeach(fort)
  set_property(TARGET AMO PROPERTY LINKER_LANGUAGE Fortran)
  target_link_libraries(AMO sepimage sepfft seppar superset sep3d sep m)
  target_link_libraries(Lloyd_vel sepwei sepfft sepgeef90 seppar superset sep3d sep)
  set_property(TARGET Stolt PROPERTY LINKER_LANGUAGE Fortran)
  target_link_libraries(Stolt sepimage sepmath sepaux superset sep3d sep m)
  if(FFTWF_LIBRARIES)
    set_property(TARGET SRM PROPERTY LINKER_LANGUAGE Fortran)
    target_link_libraries(SRM
                          sepimage
                          sepmath
                          sepaux
                          superset
                          sep3d
                          sep
                          ${FFTWF_LIBRARIES}
                          m)
    set_property(TARGET OFF2ANG PROPERTY LINKER_LANGUAGE Fortran)

    target_link_libraries(OFF2ANG
                          sepimage
                          sepmath
                          sepaux
                          superset
                          sep3d
                          sep
                          ${FFTWF_LIBRARIES}
                          m
                          ${FFTW_LIBRARIES}
                          m)

    target_link_libraries(CAM
                          sepwei
                          sepfft
                          seppar
                          superset
                          sep3d
                          sep
                          ${FFTWF_LIBRARIES}
                          m)
    target_link_libraries(Phase
                          sepwei
                          sepfft
                          seppar
                          superset
                          sep3d
                          sep
                          ${FFTWF_LIBRARIES}
                          m)
  endif(FFTWF_LIBRARIES)

endif(CMAKE_Fortran_COMPILER)

foreach(cprog ${CSEP})
  string(REGEX
         REPLACE ".csep\$"
                 ".c"
                 fortFile
                 "${cprog}")
  string(REGEX
         REPLACE ".csep\$"
                 ""
                 prog
                 "${cprog}")
  set(PROGS "${PROGS} ${prog}")
  add_custom_command(OUTPUT "${fortFile}"
                     COMMAND ${CMAKE_CURRENT_SOURCE_DIR}/../../include/sep_doc_it
                             <${CMAKE_CURRENT_SOURCE_DIR}/${cprog} -C
                             >${fortFile}
                     DEPENDS "${cprog}")
  add_executable(${prog} ${prog}.c)
  install(TARGETS ${prog} DESTINATION bin)
  set_target_properties(
    ${prog}
    PROPERTIES COMPILE_DEFINITIONS
               SOURCE="${CMAKE_CURRENT_SOURCE_DIR}/${prog}.c")
endforeach(cprog)

find_package(Threads)
target_link_libraries(Kirch_2d_depth
                      sepcwp
                      septravel
		      sepfft
                      sepaux
                      sepmath
                      superset
                      sep3d
                      sep
                      m)

#add_executable(Kirch_3d_time Kirch_3d_time.cpp)
#target_link_libraries(Kirch_3d_time
#                      sepImageCpp
#                      tbb
#                      ${CMAKE_THREAD_LIBS_INIT}
#                      ${TCMALLOC_LIB})
#install(TARGETS Kirch_3d_time DESTINATION bin)

install(PROGRAMS ${progs} DESTINATION bin)
set(SCRIPTS  Kirch_3d_time)
FOREACH(prg ${SCRIPTS})
   configure_file (
  "${CMAKE_CURRENT_SOURCE_DIR}/${prg}.py"
  "${CMAKE_CURRENT_BINARY_DIR}/${prg}"
  )
   install(PROGRAMS  ${CMAKE_CURRENT_BINARY_DIR}/${prg} DESTINATION bin)
ENDFOREACH(prg)

install(PROGRAMS ${progs} DESTINATION bin)
