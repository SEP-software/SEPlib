# Find geotrans CCS include files and libraries for KML file output code(s)
#
#  CCS_INCLUDES   - List of directories containing specific .h files
#  CCS_LIBRARIES  - List of libraries when using geotrans CCS.
#  CCS_FOUND      - True if CCS found.

if (CCS_INCLUDES)
  # Already in cache, be silent
  set (CCS_FIND_QUIETLY TRUE)
endif (CCS_INCLUDES)

file (GLOB GEOTRANSDIRS "/opt/geotrans*")
find_path (CCS_INCLUDE1 NAMES CoordinateSystem.h
                        PATHS ${GEOTRANSDIRS}
                        PATH_SUFFIXES CCS/src/dtcc
                                      CCS/src/dtcc/CoordianteSystemParameters
                                      CCS/src/dtcc/CoordinateSystems/utm
                                      CCS/src/dtcc/CoordinateSystems/misc
                                      CCS/src/dtcc/CoordinateTuples
                                      CCS/src/dtcc/Enumerations
)
find_path (CCS_INCLUDE2 NAMES CoordinateType.h
                              DtccApi.h CoordinateTuple.h GeodeticCoordinates.h
                              UTMCoordinates.h UTM.h
                        PATHS ${GEOTRANSDIRS}
                        PATH_SUFFIXES CCS/src/dtcc
                                      CCS/src/dtcc/CoordianteSystemParameters
                                      CCS/src/dtcc/CoordinateSystems/utm
                                      CCS/src/dtcc/CoordinateSystems/misc
                                      CCS/src/dtcc/CoordinateTuples
                                      CCS/src/dtcc/Enumerations
)
find_path (CCS_INCLUDE3 NAMES DtccApi.h
                        PATHS ${GEOTRANSDIRS}
                        PATH_SUFFIXES CCS/src/dtcc
                                      CCS/src/dtcc/CoordianteSystemParameters
                                      CCS/src/dtcc/CoordinateSystems/utm
                                      CCS/src/dtcc/CoordinateSystems/misc
                                      CCS/src/dtcc/CoordinateTuples
                                      CCS/src/dtcc/Enumerations
)
find_path (CCS_INCLUDE4 NAMES CoordinateTuple.h
                        PATHS ${GEOTRANSDIRS}
                        PATH_SUFFIXES CCS/src/dtcc
                                      CCS/src/dtcc/CoordianteSystemParameters
                                      CCS/src/dtcc/CoordinateSystems/utm
                                      CCS/src/dtcc/CoordinateSystems/misc
                                      CCS/src/dtcc/CoordinateTuples
                                      CCS/src/dtcc/Enumerations
)
find_path (CCS_INCLUDE5 NAMES GeodeticCoordinates.h
                        PATHS ${GEOTRANSDIRS}
                        PATH_SUFFIXES CCS/src/dtcc
                                      CCS/src/dtcc/CoordianteSystemParameters
                                      CCS/src/dtcc/CoordinateSystems/utm
                                      CCS/src/dtcc/CoordinateSystems/misc
                                      CCS/src/dtcc/CoordinateTuples
                                      CCS/src/dtcc/Enumerations
)
find_path (CCS_INCLUDE6 NAMES UTMCoordinates.h
                        PATHS ${GEOTRANSDIRS}
                        PATH_SUFFIXES CCS/src/dtcc
                                      CCS/src/dtcc/CoordianteSystemParameters
                                      CCS/src/dtcc/CoordinateSystems/utm
                                      CCS/src/dtcc/CoordinateSystems/misc
                                      CCS/src/dtcc/CoordinateTuples
                                      CCS/src/dtcc/Enumerations
)
find_path (CCS_INCLUDE7 NAMES UTM.h
                        PATHS ${GEOTRANSDIRS}
                        PATH_SUFFIXES CCS/src/dtcc
                                      CCS/src/dtcc/CoordianteSystemParameters
                                      CCS/src/dtcc/CoordinateSystems/utm
                                      CCS/src/dtcc/CoordinateSystems/misc
                                      CCS/src/dtcc/CoordinateTuples
                                      CCS/src/dtcc/Enumerations
)

if (CCS_INCLUDE1)
if (CCS_INCLUDE2)
if (CCS_INCLUDE3)
if (CCS_INCLUDE4)
if (CCS_INCLUDE5)
if (CCS_INCLUDE6)
if (CCS_INCLUDE7)
set(CCS_INCLUDES
    ${CCS_INCLUDE1}
    ${CCS_INCLUDE2}
    ${CCS_INCLUDE3}
    ${CCS_INCLUDE4}
    ${CCS_INCLUDE5}
    ${CCS_INCLUDE6}
    ${CCS_INCLUDE7}
)
endif (CCS_INCLUDE7)
endif (CCS_INCLUDE6)
endif (CCS_INCLUDE5)
endif (CCS_INCLUDE4)
endif (CCS_INCLUDE3)
endif (CCS_INCLUDE2)
endif (CCS_INCLUDE1)

find_library (CCS_LIBS HINTS ${GEOTRANSDIRS} NAMES libMSPdtcc.a MSPdtcc PATH_SUFFIXES CCS/linux_64 CCS/linux)

if(CCS_LIBS)
set(CCS_LIBRARIES ${CCS_LIBS})
endif(CCS_LIBS)


# handle the QUIETLY and REQUIRED arguments and set CCS_FOUND to TRUE if
# all listed variables are TRUE
include (FindPackageHandleStandardArgs)
find_package_handle_standard_args (CCS DEFAULT_MSG CCS_LIBRARIES CCS_INCLUDES)

mark_as_advanced (CCS_LIBRARIES CCS_INCLUDES)
