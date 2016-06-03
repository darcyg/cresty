AC_PREREQ([2.61])

AC_INIT([cresty], [0.0.1], [vmizzle@gmail.com])
AC_CONFIG_SRCDIR([src/main.c])
AC_CONFIG_HEADERS([config.h])

AM_INIT_AUTOMAKE([-Wall -Werror foreign subdir-objects])

AC_PROG_CC
AC_PROG_INSTALL

AC_CHECK_HEADERS([stdlib.h sys/socket.h unistd.h])

AC_FUNC_MALLOC
AC_CHECK_FUNCS([socket])

AC_CONFIG_FILES([
				 Makefile
				 src/Makefile
])

AC_OUTPUT
