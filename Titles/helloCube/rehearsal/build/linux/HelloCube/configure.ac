dnl Process this file with autoconf to produce a configure script.

AC_PREREQ(2.59)
AC_INIT(helloCube, 1.0)
AC_PROG_CC
AC_PROG_CXX

dnl AC_CANONICAL_SYSTEM

AM_INIT_AUTOMAKE()

: ${CXXFLAGS=-g -O0}

AC_SUBST([LOG4CXX_CFLAGS])
AC_SUBST([LOG4CXX_LIBS])

AC_ARG_WITH([log4cxx],
	[AS_HELP_STRING([--with-log4cxx], [enable log4cxx logging])],
	[],
	[with_log4cxx=no])

AS_IF([test "x$with_log4cxx" != xno],
	[
	PKG_CHECK_MODULES([LOG4CXX], [liblog4cxx])
	AM_CONDITIONAL(HAVE_LOG4CXX, true)
	AC_DEFINE(HAVE_LOG4CXX,[],[Use log4cxx])
	], [
	AM_CONDITIONAL(HAVE_LOG4CXX, false)
	])

AC_CONFIG_FILES(Makefile src/Makefile)
AC_OUTPUT

