/*======================================================================*
 *                                                                      *
 *  Copyright (C) 2016 Josh Williams (vmizzle@gmail.com)                *
 *                                                                      *
 * Permission is hereby granted, free of charge, to any person          *
 * obtaining a copy of this software and associated documentation files *
 * (the "Software"), to deal in the Software without restriction,       *
 * including without limitation the rights to use, copy, modify, merge, *
 * publish, distribute, sublicense, and/or sell copies of the Software, *
 * and to permit persons to whom the Software is furnished to do so,    *
 * subject to the following conditions:                                 *
 *                                                                      *
 * The above copyright notice and this permission notice shall be       *
 * included in all copies or substantial portions of the Software.      *
 *                                                                      *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,      *
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF   *
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND                *
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS  *
 * BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN   *
 * ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN    *
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE     *
 * SOFTWARE.                                                            *
 *                                                                      *
 *======================================================================*/
#include "socket.h"

#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>

cresty_socket* cresty_socket_create() {
	cresty_socket *s = malloc(sizeof(cresty_socket));
	if (s != NULL) {
		s->fd = -1;
		s->status = CRESTY_SOCKET_UNINITIALIZED;
	}
	return s;
}

int cresty_socket_init(cresty_socket *s) {
	int fd;

	if (s == NULL || s->status != CRESTY_SOCKET_UNINITIALIZED) return -1;

	fd = socket(AF_INET, SOCK_STREAM, 0);
	if (fd == -1) {
		return -1;
	} else {
		s->fd = fd;
		s->status = CRESTY_SOCKET_INITIALIZED;
		return 0;
	}
}

void cresty_socket_destroy(cresty_socket *s) {
	if (s->status > CRESTY_SOCKET_INITIALIZED) {
		close(s->fd);
	}
	free(s);
}
