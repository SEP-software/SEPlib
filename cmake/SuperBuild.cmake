
include (ExternalProject)

set_property (DIRECTORY PROPERTY EP_BASE Dependencies)

set (DEPENDENCIES)
set (EXTRA_CMAKE_ARGS)

# Use static linking to avoid issues with system-wide installations of Boost.
ExternalProject_Add (xorg_macros
  URL  https://github.com/freedesktop/xorg-macros/archive/util-macros-1.19.1.tar.gz
  CONFIGURE_COMMAND autoreconf -vif && ./configure  --prefix=${CMAKE_INSTALL_PREFIX}
  BUILD_COMMAND make
  BUILD_IN_SOURCE 1
  INSTALL_COMMAND make install
  )
ExternalProject_Add (xaw_build
  URL https://github.com/freedesktop/xorg-libXaw/archive/libXaw-1.0.13.tar.gz
  DEPENDS xorg_macros
  CONFIGURE_COMMAND autoreconf -vif -I ${CMAKE_INSTALL_PREFIX}/share/aclocal  && ./configure  --prefix=${CMAKE_INSTALL_PREFIX}
  BUILD_COMMAND make
  BUILD_IN_SOURCE 1
  INSTALL_COMMAND make install
  )
