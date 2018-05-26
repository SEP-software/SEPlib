# Find TDB (trivial database) include file and library for KML file output
#
#  TDB_INCLUDE    - Directories containing tdb.h
#  TDB_LIBRARY    - tdb Library
#  TDB_FOUND      - True if TDB found.

if (TDB_INCLUDE)
  # Already in cache, be silent
  set (TDB_FIND_QUIETLY TRUE)
endif (TDB_INCLUDE)

file (GLOB TDBDIRS "/opt/tdb*")
find_path (TDB_INCLUDE NAMES tdb.h PATHS ${TDBDIRS} PATH_SUFFIXES include)

find_library (TDB_LIB HINTS ${TDBDIRS} NAMES tdb PATH_SUFFIXES bin/default bin/shared)
if(TDB_LIB)
set(TDB_LIBRARY ${TDB_LIB})
endif(TDB_LIB)

# handle the QUIETLY and REQUIRED arguments and set TDB_FOUND to TRUE if
# all listed variables are TRUE
include (FindPackageHandleStandardArgs)
find_package_handle_standard_args (TDB DEFAULT_MSG TDB_LIBRARY TDB_INCLUDE)

mark_as_advanced (TDB_LIBRARY TDB_INCLUDE)
