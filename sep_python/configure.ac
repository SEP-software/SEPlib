
AC_PREREQ(2.57)

AC_INIT([sep-python],[8.0.1],[bob@sep.stanford.edu])

AC_CONFIG_SRCDIR([Makefile.am])
AC_CONFIG_HEADERS([include/sitedef.h])

AC_CANONICAL_TARGET

AM_INIT_AUTOMAKE([foreign 1.8 dist-bzip2])

dnl Avoid generating makefile rules to rebuild maintainer-only files by
dnl default. Maintainers may override this default and generate these
dnl makefile rules using the `--enable-maintainer-mode' configure option.
AM_MAINTAINER_MODE


AC_MSG_NOTICE([------------------------------------------])
AC_MSG_NOTICE([       Program Checks   ])
AC_MSG_NOTICE([------------------------------------------])

AC_MSG_NOTICE([------------------------------------------])
AC_MSG_NOTICE([       SEP Specific options   ])
AC_MSG_NOTICE([------------------------------------------])
AC_PREFIX_DEFAULT(/usr/local/SEP)
FIND_SEP_ARCH
AC_MSG_NOTICE([------------------------------------------])
AC_MSG_NOTICE([       Header files Checks   ])
AC_MSG_NOTICE([------------------------------------------])

AC_MSG_NOTICE([------------------------------------------])
AC_MSG_NOTICE([       Compiler characteristics Checks   ])
AC_MSG_NOTICE([------------------------------------------])

AC_MSG_NOTICE([------------------------------------------])
AC_MSG_NOTICE([       Library function checks   ])
AC_MSG_NOTICE([------------------------------------------])

AC_MSG_NOTICE([------------------------------------------])
AC_MSG_NOTICE([       System service checks   ])
AC_MSG_NOTICE([------------------------------------------])

AC_MSG_NOTICE([------------------------------------------])
AC_MSG_NOTICE([       Set final variables   ])
AC_MSG_NOTICE([------------------------------------------])




########################################
###############UTILITIES################
########################################


#DOC RULE STUFF

dnl THE FILES WE ARE GOING TO CREATE

base inversion operators programs flows
AC_CONFIG_FILES([Makefile include/Makefile])
AC_CONFIG_FILES([base/Makefile base/core/Makefile base/inversion/Makefile base/parallel/Makefile])
AC_CONFIG_FILES([util/Makefile util/cube/Makefile util/vector/Makefile])
AC_CONFIG_FILES([util/rep/Makefile])
AC_CONFIG_FILES([seis/Makefile seis/filter/Makefile seis/image/Makefile
seis/model/Makefile])
AC_CONFIG_FILES([flows/Makefile])
AC_CONFIG_FILES([programs/Makefile programs/seis/Makefile ])
AC_CONFIG_FILES([programs/seis/image/Makefile programs/seis/model/Makefile])
AC_CONFIG_FILES([programs/seis/filter/Makefile])
AC_CONFIG_FILES([programs/util/Makefile programs/util/par/Makefile])
AC_CONFIG_FILES([programs/util/cube/Makefile programs/util/rep/Makefile])
#AC_CONFIG_FILES([scons/Makefile rules/Makefile])
AC_OUTPUT
