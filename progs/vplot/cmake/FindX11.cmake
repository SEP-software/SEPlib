# - Find X11
# Find X11 includes and library
#
#  X11_INCLUDES    - where to find su.h
#  X11_LIBRARIES   - List of libraries when using SU.
#  X11_FOUND       - True if SU found.

if (X11_INCLUDES)
  # Already in cache, be silent
  set (X11_FIND_QUIETLY TRUE)
endif (X11_INCLUDES)


find_path (X11_INCLUDES X11/Intrinsic.h HINTS ${X11_PATH}/include  PATH /opt/local/include)

find_library (X11_LIBRARIES HINTS /opt/local/lib  HINTS ${X11_PATH}/lib  NAMES X11)
#find_library (SUCWP_LIB HINTS $ENV{CWPROOT}/lib  NAMES cwp)
#find_library (SUPAR_LIB HINTS $ENV{CWPROOT}/lib  NAMES par)
#if(SU_LIB)
#if(SUCWP_LIB)
#if(SUPAR_LIB)
#set(SU_LIBRARIES ${SU_LIB} ${SUPAR_LIB} ${SUCWP_LIB})
#endif(SUPAR_LIB)
#endif(SUCWP_LIB)
#endif(SU_LIB)


# handle the QUIETLY and REQUIRED arguments and set SU_FOUND to TRUE if
# all listed variables are TRUE
include (FindPackageHandleStandardArgs)
find_package_handle_standard_args (X11 DEFAULT_MSG X11_INCLUDES)

mark_as_advanced (X11_INCLUDES X11_LIBRARIES)
