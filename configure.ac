AC_PREREQ([2.69])

AC_INIT([Tomlin], [0.0.1], [https://github.com/dutch/tomlin/issues], [],
[https://github.com/dutch/tomlin])
AC_CONFIG_SRCDIR([libtomlin/libtomlin.hpp])
AC_CONFIG_AUX_DIR([build-aux])
AC_CONFIG_MACRO_DIR([m4])

AM_INIT_AUTOMAKE([1.14 foreign -Wall -Werror -Wno-portability])
AM_SILENT_RULES([yes])

AC_PROG_CXX
AX_BOOST_BASE
LT_INIT

AC_CONFIG_HEADERS([config.h])
AC_CONFIG_FILES([Makefile tomlin.pc libtomlin/Makefile])

AC_OUTPUT
