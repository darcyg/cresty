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

#include <ctype.h>
#include <stdlib.h>
#include <string.h>

#include "dict.h"
#include "log.h"

#define CRESTY_CONF_MAX_KEY_LEN 100
#define CRESTY_CONF_MAX_VAL_LEN 1024

struct cresty_dict *d = NULL;

const char *default_config[][2] = {
	{"log_level", "0"},
	{"port", "8080"}
};

void cresty_conf_upcase_key(const char *lower, char *upper);

cresty_result cresty_conf_init(int argc, char *argv[]) {
	d = cresty_dict_create(100);
	char upcase_key[CRESTY_CONF_MAX_KEY_LEN + 1];
	const char *value;

	if (d == NULL) return CRESTY_ERROR;

	int item_count = sizeof(default_config) / sizeof(const char *[2]);
	for (int i = 0; i < item_count; i++) {
		/* check to see if it was overridden in the environment */
		cresty_conf_upcase_key(default_config[i][0], upcase_key);
		value = getenv(upcase_key);

		if (value == NULL)
			value = default_config[i][1];

		cresty_conf_set(upcase_key, value);
	}

	return CRESTY_OK;
}

void cresty_conf_deinit() {
	if (d != NULL) cresty_dict_destroy(d);
}

const char* cresty_conf_get(const char *key) {
	char upcase_key[CRESTY_CONF_MAX_KEY_LEN + 1];

	/* we have to convert the key to uppercase */
	cresty_conf_upcase_key(key, upcase_key);

	const char *value;
	if (cresty_dict_check(d, upcase_key) == 0) {
		/* get it from the environment? */
		value = getenv(upcase_key);

		/* store it for later */
		if (value != NULL)
			cresty_dict_set(d, upcase_key, value);
	} else {
		value = cresty_dict_get(d, upcase_key);
	}

	return value;
}

int cresty_conf_set(const char *key, const char *value) {
	char upcase_key[CRESTY_CONF_MAX_KEY_LEN + 1];

	cresty_conf_upcase_key(key, upcase_key);
	return cresty_dict_set(d, upcase_key, value);
}

void cresty_conf_upcase_key(const char *lower, char *upper) {
	int i;
	for (i = 0; i < strlen(lower); i++) {
		upper[i] = toupper(lower[i]);
	}
	upper[i] = '\0';
}

/* vi: set ts=4: */
