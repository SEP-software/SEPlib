# - Find SU
# Find the native SU includes and library
#
#  SU_INCLUDES    - where to find su.h
#  SU_LIBRARIES   - List of libraries when using SU.
#  SU_FOUND       - True if SU found.

if (SU_INCLUDES)
  # Already in cache, be silent
  set (SU_FIND_QUIETLY TRUE)
endif (SU_INCLUDES)

find_path (SU_INCLUDES su.h)

find_library (SU_LIB HINTS ${CWPROOT}  NAMES su)
find_library (SUCWP_LIB HINTS ${CWPROOT}  NAMES cwp)
find_library (SUPAR_LIB HINTS ${CWPROOT}  NAMES par)
if(SU_LIB)
if(SUCWP_LIB)
if(SUPAR_LIB)
set(SU_LIBRARIES ${SU_LIB} ${SUPAR_LIB} ${SUCWP_LIB})
endif(SUPAR_LIB)
endif(SUCWP_LIB)
endif(SU_LIB)


# handle the QUIETLY and REQUIRED arguments and set FFTW_FOUND to TRUE if
# all listed variables are TRUE
include (FindPackageHandleStandardArgs)
find_package_handle_standard_args (SU DEFAULT_MSG SU_LIBRARIES SU_INCLUDES)

mark_as_advanced (SU_LIBRARIES SU_INCLUDES)
