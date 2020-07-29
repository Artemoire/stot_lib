#include "stot_test.h"

#include "stot/hash.h"

#include <stdio.h>
#include <stdlib.h>

static size_t fnv_1a(lp_string* key)
{
	size_t hash = 2166136261u;

	for (size_t i = 0; i < key->len; i++) {
		hash ^= key->data[i];
		hash *= 16777619;
	}

	return hash;
}

static void init() {
	HashSet set;

	HashSet_init(&set);
	ASSRT_EQ(set.cap, 31);
	ASSRT_EQ(set.cnt, 0);
	ASSRT_EQ(set.stage, 5);
	ASSRT_NEQ(set.entries, NULL);

	HashSet_destroy(&set);
	ASSRT_EQ(set.cap, 0);
	ASSRT_EQ(set.cnt, 0);
	ASSRT_EQ(set.stage, 0);
	ASSRT_EQ(set.entries, NULL);
}

static void insertion_1()
{
	lp_string in = { 12, "Hello There!" };
	
	HashSet set;

	HashSet_init(&set);
	HashSet_Entry *out = HashSet_insert(&set, &in);
	ASSRT_EQ(out->key, &in);
	ASSRT_EQ(set.cnt, 1);

	HashSet_destroy(&set);
}

static void insertion_2_copy()
{
	lp_string in_1 = { 12, "Hello There!" };
	lp_string in_2 = { 12, "Hello There!" };

	HashSet set;
	HashSet_init(&set);

	HashSet_Entry *out_1 = HashSet_insert(&set, &in_1);
	HashSet_Entry *out_2 = HashSet_insert(&set, &in_2);

	ASSRT_EQ(set.cnt, 1);
	ASSRT_EQ(out_1, out_2);
	
	HashSet_destroy(&set);
}

static void insertion_3_col() // Should pass if the collided strings are correctly inserted
{
	// Overflowing hash so need different input for x64 and x86
#ifdef _WIN64
	lp_string in_1 = { 1, "z" };
	lp_string in_2 = { 1, "e" };
#else	
	lp_string in_1 = { 1, "I" };
	lp_string in_2 = { 1, "4" };
#endif

	HashSet set;
	HashSet_init(&set);

	ASSRT_EQ(fnv_1a(&in_1) % 31, fnv_1a(&in_2) % 31);
	HashSet_Entry *out_1 = HashSet_insert(&set, &in_1);
	HashSet_Entry *out_2 = HashSet_insert(&set, &in_2);

	ASSRT_EQ(set.cnt, 2);
	ASSRT_EQ(out_1->key, &in_1);
	ASSRT_EQ(out_2->key, &in_2);

	HashSet_destroy(&set);
}

static void deletion()
{
	lp_string in = { 15, "General Kenobi!" };

	HashSet set;
	HashSet_init(&set);

	HashSet_Entry *out = HashSet_insert(&set, &in);
	HashSet_remove(&set, &in);

	ASSRT_EQ(set.cnt, 0);
	ASSRT_EQ(out->hash, 0);
	ASSRT_NEQ(out->key, &in);

	HashSet_destroy(&set);
}

static void entry_reuse()
{
	lp_string in = { 15, "General Kenobi!" };

	HashSet set;
	HashSet_init(&set);

	HashSet_Entry *out_1 = HashSet_insert(&set, &in);
	HashSet_remove(&set, &in);
	HashSet_Entry *out_2 = HashSet_insert(&set, &in);

	ASSRT_EQ(set.cnt, 1);
	ASSRT_EQ(out_1, out_2);

	HashSet_destroy(&set);
}

void test_Hash()
{
	TEST_FUNC(test_Hash, init);
	TEST_FUNC(test_Hash, insertion_1);
	TEST_FUNC(test_Hash, insertion_2_copy);
	TEST_FUNC(test_Hash, insertion_3_col);
	TEST_FUNC(test_Hash, deletion);
	TEST_FUNC(test_Hash, entry_reuse);
}