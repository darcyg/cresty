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

#include <netdb.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>

#include "log.h"

int cresty_socket_is_addr(const char *address);

struct cresty_socket* cresty_socket_create() {
	struct cresty_socket *s = malloc(sizeof(struct cresty_socket));
	if (s != NULL) {
		s->fd = -1;
		s->status = CRESTY_SOCKET_UNINITIALIZED;
	}
	return s;
}

cresty_result cresty_socket_init(struct cresty_socket *s) {
	int fd;

	if (s == NULL || s->status != CRESTY_SOCKET_UNINITIALIZED) return CRESTY_ERROR;

	fd = socket(AF_INET, SOCK_STREAM, 0);
	if (fd == -1) return CRESTY_ERROR;

	s->fd = fd;
	s->status = CRESTY_SOCKET_INITIALIZED;
	return CRESTY_OK;
}

void cresty_socket_destroy(struct cresty_socket *s) {
	if (s->status > CRESTY_SOCKET_INITIALIZED) {
		close(s->fd);
	}
	free(s);
}

cresty_result cresty_socket_bind(struct cresty_socket *s, const char *address, int port) {
	if (s->status != CRESTY_SOCKET_INITIALIZED) return CRESTY_ERROR;

	if (cresty_socket_is_addr(address) != 1) return CRESTY_ERROR;

	char host_address[100];
	struct hostent *hostinfo = gethostbyname(address);
	strncpy(host_address, hostinfo->h_addr_list[0], 100);

	struct sockaddr_in saddr;
	saddr.sin_family = AF_INET;
	saddr.sin_port = htons(port);
	saddr.sin_addr.s_addr = htonl(inet_addr(host_address));

	if (bind(s->fd, (struct sockaddr*)&saddr, sizeof(saddr)) != 0) return CRESTY_ERROR;

	s->status = CRESTY_SOCKET_BOUND;

	return CRESTY_OK;
}

cresty_result cresty_socket_listen(struct cresty_socket *s, int backlog) {

	if (s->status != CRESTY_SOCKET_BOUND) return CRESTY_ERROR;

	if (listen(s->fd, backlog) != 0) return CRESTY_ERROR;

	s->status = CRESTY_SOCKET_LISTENING;

	return CRESTY_OK;
}

void cresty_socket_shutdown(struct cresty_socket *s) {
	shutdown(s->fd, SHUT_WR);
}

int cresty_socket_is_addr(const char *address) {
	struct hostent *hostinfo = gethostbyname(address);

	return hostinfo != NULL ? 1 : 0;
}

/* vi: set ts=4: */
