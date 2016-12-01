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
#include <stdlib.h>

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
 *         return 0;
 *     }
 */
#define TU_TEST(test_name) int test_name(char *message)

/*
 * Asserts the condition under test.  If the test fails, this will
 * immediately return.  Ensure any cleanup has already been performed.
 */

#define TU_ASSERT(test) do { \
	snprintf(message, MAX_TEST_MESSAGE, #test); \
	if (!test) return 1; \
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
		if (tests[i]->test_func((char*)&test_message) == 0) { \
			printf("ok "); \
		} else { \
			printf("not ok "); \
		} \
		printf("%d - %s -> %s\n", i + 1, tests[i]->name, test_message); \
		free(tests[i]); \
	} \
} while (0)
/* #define TU_STUB_FUNC(RTN, NAME) \ */
/* 	void stub_func() { \ */
/* 		printf("foo\n"); \ */
/* 		printf("RTN: " #RTN "\n"); \ */
/* 		printf("name: " #NAME "\n"); \ */
/* 	} */


#define TU_STUB_FUNC0(RTN, NAME) \
	typedef RTN (* _ ## NAME)(); \
	_ ## NAME stubbed_ ## NAME; \
	RTN NAME() { \
		if (stubbed_ ## NAME == NULL) { \
			fprintf(stderr, "function not stubbed: " #NAME "\n"); \
			exit(1); \
		} \
		return (*stubbed_ ## NAME)(); \
	}

#define TU_STUB_FUNC1(RTN, NAME, ARG_TYPE0) \
	typedef RTN (* _ ## NAME)(ARG_TYPE0 arg0); \
	_ ## NAME stubbed_ ## NAME = NULL; \
	RTN NAME(ARG_TYPE0 arg0) { \
		if (stubbed_ ## NAME == NULL) { \
			fprintf(stderr, "function not stubbed: " #NAME "\n"); \
			exit(1); \
		} \
		return (*stubbed_ ## NAME)(arg0); \
	}

#define TU_STUB_FUNC2(RTN, NAME, ARG_TYPE0, ARG_TYPE1) \
	typedef RTN (* _ ## NAME)(ARG_TYPE0 arg0, ARG_TYPE1 arg1); \
	_ ## NAME stubbed_ ## NAME = NULL; \
	RTN NAME(ARG_TYPE0 arg0, ARG_TYPE1 arg1) { \
		if (stubbed_ ## NAME == NULL) { \
			fprintf(stderr, "function not stubbed: " #NAME "\n"); \
			exit(1); \
		} \
		return (*stubbed_ ## NAME)(arg0, arg1); \
	}

#define TU_STUB_FUNC3(RTN, NAME, ARG_TYPE0, ARG_TYPE1, ARG_TYPE2) \
	typedef RTN (* _ ## NAME)(ARG_TYPE0 arg0, ARG_TYPE1 arg1, ARG_TYPE2 arg2); \
	_ ## NAME stubbed_ ## NAME = NULL; \
	RTN NAME(ARG_TYPE0 arg0, ARG_TYPE1 arg1, ARG_TYPE2 arg2) { \
		if (stubbed_ ## NAME == NULL) { \
			fprintf(stderr, "function not stubbed: " #NAME "\n"); \
			exit(1); \
		} \
		return (*stubbed_ ## NAME)(arg0, arg1, arg2); \
	}

#define ARGS_RSEQ() 10,9,8,7,6,5,4,3,2,1,0
#define ARGS(rtn, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, N, ...) N
#define ARGSN_(...) ARGS(__VA_ARGS__)
#define ARGSN(...) ARGSN_(__VA_ARGS__, ARGS_RSEQ())
#define TU_STUB_FUNC(N, ...) TU_STUB_FUNC ## N(__VA_ARGS__)
#define TU_STUB_(N, ...) TU_STUB_FUNC(N, __VA_ARGS__)
#define TU_MAKESTUB(...) TU_STUB_(ARGSN(__VA_ARGS__), __VA_ARGS__)

#define TU_SET_STUB(TARGET, SOURCE) stubbed_ ## TARGET = &SOURCE

#endif /* __TUNIT_H_INCLUDED __ */
