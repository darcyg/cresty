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
#include "conf.h"
#include "log.h"
#include "socket.h"

cresty_socket *s;

cresty_result cresty_init(int argc, char *argv[]) {

	/* Initialize the configuration */
	if (cresty_conf_init(argc, argv) != CRESTY_OK) return CRESTY_ERROR;

	/* Create the listening socket */
	s = cresty_socket_create();
	if (s == NULL) {
		debug("Unable to create cresty_socket.");
		return -1;
	}

	if (cresty_socket_init(s) != CRESTY_OK) {
		debug("Error initializing socket.");
		cresty_socket_destroy(s);
		return -1;
	}

	debug("Socket initialized: %d", s->fd);

	return CRESTY_OK;
}

void cresty_destroy() {
	cresty_socket_destroy(s);
	cresty_conf_destroy();
}

/* vi: set ts=4: */
