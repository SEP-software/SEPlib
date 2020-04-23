
include (ExternalProject)

set_property (DIRECTORY PROPERTY EP_BASE Dependencies)

set (DEPENDENCIES)
set (EXTRA_CMAKE_ARGS)

# Use static linking to avoid issues with system-wide installations of Boost.
list (APPEND DEPENDENCIES flex_build)
ExternalProject_Add (flex_build
  URL https://github.com/westes/flex/files/981163/flex-2.6.4.tar.gz
  CONFIGURE_COMMAND ./configure  --prefix=${CMAKE_INSTALL_PREFIX}
  BUILD_COMMAND make 
  BUILD_IN_SOURCE 1
  INSTALL_COMMAND make install
  )
ExternalProject_Add (xaw_build
  URL https://github.com/freedesktop/xorg-libXaw/archive/libXaw-1.0.13.tar.gz
  CONFIGURE_COMMAND autoreconf -vif && ./configure  --prefix=${CMAKE_INSTALL_PREFIX}
  BUILD_COMMAND make
  BUILD_IN_SOURCE 1
  INSTALL_COMMAND make install
  )
