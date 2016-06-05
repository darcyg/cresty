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
#ifndef __TUNIT_H_INCLUDED__
#define __TUNIT_H_INCLUDED__

#include <stdio.h>

#define MAX_TEST_CASES 100
#define MAX_TEST_NAME 255
#define MAX_TEST_MESSAGE 255

typedef struct {
	char name[MAX_TEST_NAME + 1];
	char message[MAX_TEST_MESSAGE + 1];
	int (*test_func)(char *message);
} tu_test_case;

int           total_tests;
tu_test_case* tests[MAX_TEST_CASES];
char          test_message[MAX_TEST_MESSAGE + 1];

/*
 * Define a test to be run.  Example:
 *     TU_TEST(adds_numbers_correctly) {
 *         int x = add(1, 2);
 *         TU_ASSERT(x == 3);
 *     }
 */
#define TU_TEST(test_name) int test_name(char *message, int result)

#define TU_RESULT() result;

/*
 * Asserts the condition under test.  If the test fails, this will
 * immediately return.  Ensure any cleanup has already been performed.
 */

#define TU_ASSERT(test) do { \
	snprintf(message, MAX_TEST_MESSAGE, #test); \
	result = (test); \
} while (0)

/*
 * Starts a test block.  Call this at the beginning of your test suite.
 *
 *     TU_BEGIN();
 *       ..add some tests..
 *     TU_RUN();
 */
#define TU_BEGIN() do { total_tests = 0; } while (0)

#define TU_ADD(test) do { \
	tu_test_case* tc = malloc(sizeof(tu_test_case)); \
	memset(tc, 0, sizeof(tu_test_case)); \
	strncpy(tc->name, #test, MAX_TEST_NAME); \
	tc->test_func = test; \
	tests[total_tests] = tc; \
	total_tests++; \
} while (0)

#define TU_RUN() do { \
	printf("1..%d\n", total_tests); \
	for (int i = 0; i < total_tests; i++) { \
		if (tests[i]->test_func((char*)&test_message)) { \
			printf("ok "); \
		} else { \
			printf("not ok "); \
		} \
		printf("%d - %s -> %s\n", i + 1, tests[i]->name, test_message); \
		free(tests[i]); \
	} \
} while (0)

#endif /* __TUNIT_H_INCLUDED __ */
