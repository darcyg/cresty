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

typedef enum {
	CRESTY_DICT_ITEM_STRING,
	CRESTY_DICT_ITEM_BOOLEAN,
	CRESTY_DICT_ITEM_INT
} cresty_dict_item_type;

typedef struct cresty_dict_item_ {
	cresty_dict_item_type type;
	void * data;
	struct cresty_dict_item_ *next;
} cresty_dict_item;

typedef struct {
	cresty_dict_item *head;
} cresty_dict;

cresty_dict* cresty_dict_create();
void cresty_dict_destroy(cresty_dict *d);

#endif /* __DICT_H_INCLUDED__ */

/* vi: set ts=4: */
