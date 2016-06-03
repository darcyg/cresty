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
#include "conf.h"

#include <string.h>

#include "dict.h"

typedef struct {
	unsigned short log_level;
} cresty_config;

cresty_dict *d = NULL;

cresty_result cresty_conf_init(int argc, char *argv[]) {
	d = cresty_dict_create();
	if (d == NULL) return CRESTY_ERROR;

	return CRESTY_OK;
}

void cresty_conf_destroy() {
	if (d != NULL) cresty_dict_destroy(d);
}

const char* cresty_conf_get(const char *name) {
	return NULL;
}

int cresty_conf_get_int(const char *name) {
	if (strcmp(name, "log_level") == 0 || strcmp(name, "log_level") == 0) {
		return 0;
	} else {
		return -1;
	}
}
/* vi: set ts=4: */
