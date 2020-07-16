#include "stot_test.h"

#include "stot/hash.h"

#include <stdio.h>
#include <stdlib.h>


void test1()
{
	const char* a = "test_Black";
	const char* a1 = "test_Hello";
	HashSet set;
	HashSet_init(&set);
	const char* b = HashSet_insert(&set, a, 10);
	const char* c = HashSet_insert(&set, a1, 10);
	printf("%d\n", a == b);
	HashSet_destroy(&set);
}

void test_Hash()
{
	TEST_FUNC(test_Hash, test1);
}