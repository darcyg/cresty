AC_PREREQ([2.61])

AC_INIT([cresty], [0.0.1], [vmizzle@gmail.com])
AC_CONFIG_SRCDIR([src/main.c])
AC_CONFIG_HEADERS([config.h])

AM_INIT_AUTOMAKE([-Wall -Werror foreign subdir-objects])

AC_ARG_ENABLE(debug,
	AC_HELP_STRING([--disable-debug], [Compile without debug logging]),
		[ if test "$enableval" = yes ; then
			AC_DEFINE(DEBUG, 1, [Define as 1 to get debug logging.])
		fi ],
		[ enable_debug="yes";
		 AC_DEFINE(DEBUG, 1, [Define as 1 to get debug logging.])])

AC_PROG_CC
AC_PROG_CC_STDC
AC_PROG_INSTALL

AC_CHECK_HEADERS([ \
				  arpa/inet.h \
				  netdb.h \
				  netinet/in.h \
				  stddef.h \
				  stdlib.h \
				  string.h \
				  sys/socket.h \
				  unistd.h])

AC_FUNC_ERROR_AT_LINE
AC_FUNC_MALLOC
AC_CHECK_FUNCS([ \
				gethostbyname \
				localtime_r \
				memset \
				socket])

AC_CONFIG_FILES([
				 Makefile
				 src/Makefile
])

AC_OUTPUT
