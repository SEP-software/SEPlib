# - Find FFTW
# Find the native FFTW includes and library
#
#  SU_INCLUDES    - where to find fftw3.h
#  SU_LIBRARIES   - List of libraries when using FFTW.
#  SU_FOUND       - True if FFTW found.

if (SU_INCLUDES)
  # Already in cache, be silent
  set (SU_FIND_QUIETLY TRUE)
endif (SU_INCLUDES)

find_path (SU_INCLUDES su.h)

find_library (SU_LIB HINTS ${CWP_ROOT}  NAMES su)
find_library (SUCWP_LIB HINTS ${CWP_ROOT}  NAMES cwp)
find_library (SUPAR_LIB HINTS ${CWP_ROOT}  NAMES par)
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
