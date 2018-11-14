#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.69])
AC_INIT([hhbot], [1.0], [chipz68q@gmail.com])
AC_CONFIG_AUX_DIR([build-aux])
AC_CONFIG_MACRO_DIR([m4])
AM_INIT_AUTOMAKE
AM_PROG_AR
LT_INIT
AC_CONFIG_SRCDIR([src/main.c])
AC_CONFIG_HEADERS([config.h])

# Checks for programs.
AC_PROG_CC
AC_PROG_INSTALL

# Checks for libraries.
PKG_CHECK_MODULES([PKGGTK], [gtk+-3.0])
PKG_CHECK_MODULES([LIBSOUP], [libsoup-2.4 >= 2.26])
#AC_SUBST(LIBSOUP_CFLAGS)
#AC_SUBST(LIBSOUP_LIBS)

# Checks for typedefs, structures, and compiler characteristics.

AC_CONFIG_FILES([Makefile
                 lib/Makefile
                 src/Makefile])
AC_OUTPUT
