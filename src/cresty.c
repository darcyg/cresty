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
#include "cresty.h"

#include <errno.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>

#include "conf.h"
#include "log.h"
#include "socket.h"

struct cresty_socket *s;

int pipes[2];

void sighandler(int sig) {
	debug("signal handler fired");
	if (sig == SIGINT) {

		if (write(pipes[1], "EXIT\n", 5) != 5) {
			error("Error writing to pipe");
		} else {
			debug("shutdown signal sent");
		}
	}
}

cresty_result cresty_init(int argc, char *argv[]) {

	/* Initialize the configuration */
	if (cresty_conf_init(argc, argv) != CRESTY_OK) return CRESTY_ERROR;

	/* Create the listening socket */
	s = cresty_socket_create();
	if (s == NULL) {
		error("Unable to create cresty_socket.");
		return -1;
	}

	if (cresty_socket_init(s) != CRESTY_OK) {
		error("Error initializing socket.");
		cresty_socket_destroy(s);
		return -1;
	}

	/* Put the socket into listening mode */
	const char *portc = cresty_conf_get("port");
	if (portc == NULL) return CRESTY_ERROR;
	int port = atoi(portc);
	if (port <= 0) return CRESTY_ERROR;

	if (cresty_socket_bind(s, "0.0.0.0", port) != CRESTY_OK) return CRESTY_ERROR;

	if (cresty_socket_listen(s, 5) != CRESTY_OK) return CRESTY_ERROR;

	/* setup the pipe for signal handling */
	if (pipe(pipes)) return CRESTY_ERROR;

	/* setup the signal handler for ctrl-c */
	struct sigaction handler;
	handler.sa_handler = sighandler;
	if (sigemptyset(&handler.sa_mask) < 0) {
		error("unable to setup signal handler");
		return CRESTY_ERROR;
	}
	handler.sa_flags = 0;
	if (sigaction(SIGINT, &handler, 0) < 0) {
		error("error setting up sigaction");
		return CRESTY_ERROR;
	}

	return CRESTY_OK;
}

void cresty_deinit() {
	cresty_socket_destroy(s);
	cresty_conf_deinit();
}

cresty_result cresty_main() {
	struct timeval seltime;

	seltime.tv_sec = 5;
	seltime.tv_usec = 0;
	fd_set readfds, writefds, excpfds;

	int exit = 0;
	int rc;

	while (exit == 0) {
		FD_ZERO(&readfds);
		FD_ZERO(&writefds);
		FD_ZERO(&excpfds);

		FD_SET(pipes[0], &readfds);
		FD_SET(s->fd, &readfds);

		rc = select(FD_SETSIZE, &readfds, &writefds, &excpfds, &seltime);
		if (rc == -1) {
			if (errno == EINTR) continue;
			error("error in select: %d", errno);
			break;
		}

		for (int i = 0; i < FD_SETSIZE; i++) {
			if (FD_ISSET(i, &readfds)) {
				if (i == pipes[0]) {
					debug("time to exit");
					cresty_socket_shutdown(s);
					exit = 1;
				}
			}
		}
	}

	return CRESTY_OK;
}

/* vi: set ts=4: */
