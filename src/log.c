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
#include <stdio.h>
#include <stdarg.h>
#include <time.h>

#include "log.h"

static void log_timestamp(FILE *out) {
	char      buffer[200];
	time_t    t;
	struct tm *tmp, tmbuf;

	t = time(NULL);
	tmp = localtime_r(&t, &tmbuf);

	if (tmp != NULL) {
		if (strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", tmp) != 0)
			fprintf(out, "%s: ", buffer);
	}

}

static void log_file_details(FILE *out, const unsigned long line,
		const char *file, const char *function) {
	fprintf(out, "(%04lu@%-10.10s:%-15.15s): ", line, file, function);
}

void cresty_log_debug(const char *file, const char *function,
		const unsigned long line, const char *fmt, ...) {
	va_list   args;

	log_timestamp(stdout);
	fprintf(stdout, "DEBUG ");
	log_file_details(stdout, line, file, function);

	va_start(args, fmt);
	vfprintf(stdout, fmt, args);
	va_end(args);
	fprintf(stdout, "\n");
	fflush(stdout);
}

void cresty_log_error(const char *file, const char *function,
		const unsigned long line, const char *fmt, ...) {
	va_list   args;

	log_timestamp(stdout);
	fprintf(stdout, "ERROR ");
	log_file_details(stdout, line, file, function);

	va_start(args, fmt);
	vfprintf(stdout, fmt, args);
	va_end(args);
	fprintf(stdout, "\n");
	fflush(stdout);
}
/* vi: set ts=4: */
