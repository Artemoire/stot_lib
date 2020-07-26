#include "stot_test.h"

#include "stot/hash.h"

#include <stdio.h>
#include <stdlib.h>


void test1()
{
	const char* a = "test_Black";
	const char* a1 = "test_Hello";

	lp_string *lp_a = lp_string_copy(10, a);
	lp_string *lp_a1 = lp_string_copy(10, a1);
	HashSet set;
	HashSet_init(&set);

	lp_string *b = HashSet_insert(&set, lp_a);
	lp_string *c = HashSet_insert(&set, lp_a1);
	printf("%d\n", lp_a == b);

	lp_string** arr = HashSet_keys(&set);
	printf("%d\n", lp_a == arr[0]);
	printf("%d\n", lp_a1 == arr[1]);

	free(lp_a);
	free(lp_a1);
	free(arr);

	HashSet_destroy(&set);

}

void test_Hash()
{
	TEST_FUNC(test_Hash, test1);
}