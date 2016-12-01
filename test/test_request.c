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
#include "tunit.h"
/*
#include "../src/request.c"

#include <string.h>

static char *message = "GET /api/test HTTP/1.1\r\n" \
						"User-Agent: TUnit\r\n" \
						"\r\n";

TU_TEST(request_parse_incomplete) {
	struct cresty_request *r = cresty_request_create();
	TU_ASSERT(r->complete == 0);
	cresty_request_destroy(r);
	return 0;
}

TU_TEST(request_parse_partial) {
	struct cresty_request *r = cresty_request_create();
	cresty_request_parse(r, "GET /api/test HTTP/1.1\r\n");
	TU_ASSERT(r->complete == 0);
	TU_ASSERT(strncmp(r->method, "GET", 3) == 0);
	cresty_request_destroy(r);
}

TU_TEST(request_parse_size_limit) {
	char *overflowing[100000];
	memset(overflowing, 'a', sizeof(overflowing) - 1);
	struct cresty_request *r = cresty_request_create();
	TU_ASSERT(cresty_request_parse(r, message) == CRESTY_ERROR);
	cresty_request_destroy(r);
	return 0;
}
*/

int main(int argc, char *argv[]) {
	/*
	TU_BEGIN();
	TU_ADD(request_parse_incomplete);
	TU_ADD(request_parse_partial);
	TU_ADD(request_parse_size_limit);
	TU_RUN();
	*/

	return 0;
}
