# Find geotrans CCS include files and libraries for KML file output code(s)
#
#  CCS_INCLUDES   - List of directories containing 3 specific .h files
#  CCS_LIBRARIES  - List of libraries when using geotrans CCS.
#  CCS_FOUND      - True if CCS found.

if (CCS_INCLUDES)
  # Already in cache, be silent
  set (CCS_FIND_QUIETLY TRUE)
endif (CCS_INCLUDES)

file (GLOB GEOTRANSDIRS "/opt/geotrans*")
find_path (CCS_INCLUDES NAMES GeodeticCoordinates.h UTMCoordinates.h UTM.h PATHS ${GEOTRANSDIRS)})

find_library (CCS_LIBS HINTS ${GEOTRANSDIRS} NAMES MSPdtcc)
if(CCS_LIB)
set(CCS_LIBRARIES ${CCS_LIBS})
endif(CCS_LIB)


# handle the QUIETLY and REQUIRED arguments and set CCS_FOUND to TRUE if
# all listed variables are TRUE
include (FindPackageHandleStandardArgs)
find_package_handle_standard_args (CCS DEFAULT_MSG CCS_LIBRARIES CCS_INCLUDES)

mark_as_advanced (CCS_LIBRARIES CCS_INCLUDES)
