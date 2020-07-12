#include <stdio.h>

#include "assrt.h"

#define IS_NEW_TEST() prev_test_suite == curr_suite_name && prev_test_func == curr_func_name

static bool test_failed;

static const char* curr_suite_name;
static const char* curr_func_name;
static int total;
static int passed;

void fail_test()
{
	if (!test_failed) {
		passed--;
		test_failed = true;
	}
}

void test_func(const char* suite_name, const char* func_name, TestFunc test_func)
{
	total++;
	passed++;
	test_failed = false;
	curr_suite_name = suite_name;
	curr_func_name = func_name;
	test_func();
}

void _assrt_tru(bool x)
{
	if (!x) {		
		fail_test();
		fprintf(stderr, "%s::%s - FAILED\n", curr_suite_name, curr_func_name);
	}
}

void _assrt_eq(void* a, void* b)
{
	if (a != b) {
		fail_test();
		fprintf(stderr, "%s::%s - FAILED\n", curr_suite_name, curr_func_name);
	}
}

void _assrt_neq(void* a, void* b)
{
	if (a == b) {
		fail_test();
		fprintf(stderr, "%s::%s - FAILED\n", curr_suite_name, curr_func_name);
	}
}

void test_conclude()
{
	fprintf(stderr, "[%d/%d] TESTS PASSED\n", passed, total);
}