AM_CFLAGS = -Wall -Werror -pedantic

lib_LIBRARIES = libcresty.a

libcresty_a_SOURCES = conf.c \
				 conn.c \
				 cresty.c \
				 dict.c \
				 log.c \
				 request.c \
				 socket.c

bin_PROGRAMS = cresty

cresty_SOURCES = main.c
cresty_LDADD = libcresty.a
