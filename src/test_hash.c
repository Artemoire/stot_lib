#include "stot_test.h"

#include "stot/hash.h"

#include <stdio.h>
#include <stdlib.h>

#define STR(x) { false, sizeof(x) - 1, sizeof(x) - 1, x }

static size_t fnv_1a(str* key)
{
	size_t hash = 2166136261u;

	for (size_t i = 0; i < key->len; i++) {
		hash ^= key->buffer[i];
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
	str in = STR("Hello There!");
	
	HashSet set;

	HashSet_init(&set);
	HashSet_Entry *out = HashSet_insert(&set, &in);
	ASSRT_EQ(out->key, &in);
	ASSRT_EQ(set.cnt, 1);

	HashSet_destroy(&set);
}

static void insertion_2_copy()
{
	str in_1 = STR("Hello There!");
	str in_2 = STR("Hello There!");

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
	str in_1 = STR("z");
	str in_2 = STR("e");
#else	
	str in_1 = STR("I");
	str in_2 = STR("4");
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
	str in = STR("General Kenobi!");

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
	str in = STR("General Kenobi!");

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