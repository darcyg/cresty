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
#include "../src/conf.c"

/*
*/
TU_MAKESTUB(struct cresty_dict*, cresty_dict_create, unsigned int);
TU_MAKESTUB(cresty_result, cresty_dict_set, struct cresty_dict*, const char*, const char*);
TU_MAKESTUB(const char*, cresty_dict_get, struct cresty_dict*, const char*);
TU_MAKESTUB(void, cresty_dict_destroy, struct cresty_dict*);
TU_MAKESTUB(int, cresty_dict_has_key, struct cresty_dict*, const char*);

char dummy_struct[1];
struct cresty_dict* base_create(unsigned_int) {
	return &dummy_struct;
}

void base_destroy(struct cresty_dict *d) {}
cresty_result base_set(struct cresty_dict *d, const char *key, const char *v) {
	return CRESTY_OK;
}

const char* base_get(struct cresty_dict *d, const char *key) {
	return "bar";
}

int base_has_key(struct cresty_dict *d, const char *key) {
	return 1;
}


TU_TEST(conf_set) {

	TU_SET_STUB(cresty_dict_create, base_create);
	TU_SET_STUB(cresty_dict_destroy, base_destroy);
	TU_SET_STUB(cresty_dict_get, base_get);
	TU_SET_STUB(cresty_dict_set, base_set);
	TU_SET_STUB(cresty_dict_has_key, base_has_key);
	TU_ASSERT(cresty_conf_init(0, NULL) == CRESTY_OK);
	TU_ASSERT(cresty_conf_set("foo", "bar") == CRESTY_OK);
	TU_ASSERT(strncmp(cresty_conf_get("foo"), "bar", 3) == 0);
	cresty_conf_deinit();
	return 0;
}

int main(int argc, char *argv[]) {
	TU_BEGIN();
	TU_ADD(conf_set);
	TU_RUN();

	return 0;
}
