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
#include "request.h"

#include <string.h>
#include <stdlib.h>
#include "dict.h"

const char* cresty_request_parse_headers(struct cresty_request *r,
						const char *message);

struct cresty_request* cresty_request_create() {
	struct cresty_request *request = malloc(sizeof(struct cresty_request));
	request->complete = 0;
	memset(request->header_buffer, 0, sizeof(request->header_buffer));
	request->headers = cresty_dict_create(32);
	return request;
}

void cresty_request_destroy(struct cresty_request *request) {
	cresty_dict_destroy(request->headers);
	free(request);
}

cresty_result cresty_request_parse(struct cresty_request *r, const char *message) {

	if (r->state == CRESTY_REQUEST_INIT)
		r->state = CRESTY_REQUEST_HEADERS;

	if (r->state == CRESTY_REQUEST_HEADERS) {
		const char *rem = cresty_request_parse_headers(r, message);
		if (strlen(rem) >= strlen("\r\n") && strncmp(rem, "\r\n", 2) == 0) {
			/*
			 * Full headers found.  Move along.
			 */
			r->state = CRESTY_REQUEST_BODY;
		}
	}

	if (r->state == CRESTY_REQUEST_BODY) {
	}
	return CRESTY_OK;
}

const char* cresty_request_parse_headers(struct cresty_request *r, const char *message) {
	const char *pm;
	char *pc;
	int offset;

	pm = message;

	while (pm != NULL) {
		pc = strstr(pm, "\r\n");
		if (pc != NULL) {
			/*
			 * Found the end of a header.
			 */
			offset = pc - pm;

			/*
			 * Make sure we can fit it in our buffer.
			 */
			if (offset + strlen(r->header_buffer) > MAX_HEADER_LENGTH) {
				/* Do something really bad...terminate connection? */
			}

			/*
			 * Copy the data into our buffer, and null-terminate it
			 */
			pc = r->header_buffer + strlen(r->header_buffer);
			strncpy(pc, pm, offset);

			/*
			 * Full header found (maybe).  Check and store it.
			 */
			pc = strstr(r->header_buffer, ":");
			if (pc != NULL) {
				/* Woo-hoo!  We have a real header! */

			} else {
				/* Malformed.  Reject it. */
			}
			pm = pm + offset + strlen("\r\n");
		} else {
			if (strlen(r->header_buffer) + strlen(pm) > MAX_HEADER_LENGTH) {

			}
		}
	}
	return pm;
}

/* vi: set ts=4: */
