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
#include "dict.h"

#include <stdlib.h>
#include <string.h>

#include "cresty.h"
#include "log.h"

unsigned int cresty_dict_hash(unsigned int size, const char *s);
cresty_dict_item* cresty_dict_fetch(cresty_dict *d, const char *key);

/*
 * Dict Item
 */
cresty_dict_item* cresty_dict_item_create(const char *key, const char *value) {
	cresty_dict_item *item;
	item = malloc(sizeof(cresty_dict_item));
	if (item == NULL) return NULL;

	item->key = malloc(strlen(key) + 1);
	if (item->key == NULL) {
		free(item);
		return NULL;
	}

	item->value = malloc(strlen(value) + 1);
	if (item->value == NULL) {
		free(item->key);
		free(item);
		return NULL;
	}

	strcpy(item->key, key);
	strcpy(item->value, value);
	return item;
}

void cresty_dict_item_destroy(cresty_dict_item *i) {
	if (i->key != NULL) free(i->key);
	if (i->value != NULL) free(i->value);
	free(i);
}

/*
 * Dict
 */
cresty_dict* cresty_dict_create(unsigned int size) {
	cresty_dict* d;

	d = malloc(sizeof(cresty_dict));
	if (d == NULL) return NULL;

	d->size = size;
	d->items = malloc(sizeof(cresty_dict_item*) * d->size);
	memset(d->items, 0, sizeof(cresty_dict_item*) * d->size);

	return d;
}

void cresty_dict_destroy(cresty_dict *d) {

	cresty_dict_item *next, *item;

	/* Free the items */
	for (int i = 0; i < d->size; i++) {
		next = d->items[i];
		while (next != NULL) {
			item = next;
			next = item->next;
			cresty_dict_item_destroy(item);
		}
	}
	free(d->items);

	/* Now free the dict itself */
	free(d);
}

char* cresty_dict_get(cresty_dict *d, const char *key) {
	cresty_dict_item *item;

	if ((item = cresty_dict_fetch(d, key)) == NULL) {
		debug("did not find item in get");
		return NULL;
	}

	return item->value;
}


cresty_result cresty_dict_set(cresty_dict *d, const char *key, const char *value) {
	cresty_dict_item *item;
	unsigned int hashval;

	if ((item = cresty_dict_fetch(d, key)) == NULL) {
		/* this key isn't stored */
		item = cresty_dict_item_create(key, value);
		if (item == NULL) return CRESTY_ERROR;

		hashval = cresty_dict_hash(d->size, key);
		item->next = d->items[hashval];
		d->items[hashval] = item;
	} else {
		/* this key already exists.  See if the new value will fit */
		if (strlen(value) > strlen(item->value)) {
			free(item->value);
			item->value = malloc(strlen(value) + 1);
			if (item->value == NULL) {
				free(item);
				return CRESTY_ERROR;
			}
		}
	}
	strcpy(item->value, value);
	return CRESTY_OK;
}

int cresty_dict_check(cresty_dict *d, const char *key) {
	if (cresty_dict_fetch(d, key) != NULL) return 1;

	return 0;
}

unsigned int cresty_dict_hash(unsigned int size, const char *s) {
	unsigned int hashval;
	for (hashval = 0; *s != '\0'; s++) {
		hashval = *s + 31 * hashval;
	}
	return hashval % size;
}

cresty_dict_item* cresty_dict_fetch(cresty_dict *d, const char *key) {
	cresty_dict_item *item;
	for (item = d->items[cresty_dict_hash(d->size, key)]; item != NULL; item = item->next) {
		/* we're at the right slot in the table */
		if (strcmp(key, item->key) == 0) {
			return item;
		}
	}
	return NULL;
}

/* vi: set ts=4: */
