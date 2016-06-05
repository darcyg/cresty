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

#include <stdlib.h>

struct cresty_request* cresty_request_create() {
	struct cresty_request *request = malloc(sizeof(struct cresty_request));
	request->complete = 0;
	return request;
}

void cresty_request_destroy(struct cresty_request *request) {
	free(request);
}

cresty_result cresty_request_parse(struct cresty_request *r, const char *message) {
	/* char *lines[1024]; /1* maximum lines for the request *1/ */
	/* start splitting this bad boy up */
	return CRESTY_OK;
}

/* vi: set ts=4: */
