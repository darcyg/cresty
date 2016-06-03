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
#ifndef __DICT_H_INCLUDED__
#define __DICT_H_INCLUDED__

#include "cresty.h"

typedef struct cresty_dict_item_ {
	char *key;
	char *value;
	struct cresty_dict_item_ *next;
} cresty_dict_item;

typedef struct {
	unsigned int size;
	cresty_dict_item **items;
} cresty_dict;

cresty_dict*  cresty_dict_create(unsigned int size);
void          cresty_dict_destroy(cresty_dict *d);

char*         cresty_dict_get(cresty_dict *d, const char *key);
cresty_result cresty_dict_set(cresty_dict *d, const char *key, const char *value);
int           cresty_dict_check(cresty_dict *d, const char *key);

#endif /* __DICT_H_INCLUDED__ */

/* vi: set ts=4: */
