#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#include "stot/hash.h"
#include "hash_internal.h"

static const char * deleted_key = (const char*)1;

static uint32_t fnv_1a(const char* key, uint32_t len)
{
	uint32_t hash = 2166136261u;

	for (int i = 0; i < len; i++) {
		hash ^= key[i];
		hash *= 16777619;
	}

	return hash;
}

static uint32_t fnv_1(const char* key, uint32_t len)
{
	uint32_t hash = 2166136261u;

	for (int i = 0; i < len; i++) {
		hash *= 16777619;
		hash ^= key[i];
	}

	return hash;
}

static inline bool key_equal(_HSetEntry* entry, uint32_t hash, uint32_t len, const char* key)
{
	return entry->hash == hash && entry->len == len && strncmp(entry->key, key, len) == 0;
}

void HashSet_init(HashSet* set)
{
	set->cap = 31;
	set->cnt = 0;
	set->stage = 5;
	set->entries = calloc(32, sizeof(_HSetEntry));
}

void HashSet_destroy(HashSet* set)
{
	// Need to free keys since took ownership
	for (int i = 0; i < set->cap; i++) {
		const char* key = set->entries[i].key;
		if (key != NULL && key != deleted_key) free(key);
	}

	set->cap = 0;
	set->cnt = 0;
	set->stage = 0;	
	free(set->entries);
	set->entries = NULL;
}

static void _HashSet_scale(HashSet* set)
{
	uint32_t prevCap = set->cap;
	_HSetEntry *prevEntries = set->entries;

	// TODO: MaxStage ?
	set->cap = (1 << set->stage) - plt2n_diff_table[set->stage];
	set->cnt = 0;
	set->entries = calloc((1 << set->stage), sizeof(_HSetEntry));

	for (int i = 0; i < prevCap; i++) {
		_HSetEntry* entry = &prevEntries[i];
		if (entry->key != NULL && entry->key != deleted_key) {
			_HashSet_insert(set, false, entry->hash, entry->len, entry->key);
		}
	}

	free(prevEntries);
}

static const char* _HashSet_insert(HashSet* set, bool copy, uint32_t hash_a, uint32_t len, const char* key)
{
	const uint32_t hash_b = fnv_1(key, len);

	if ((set->cnt * 100 / set->cap) >= 75)
	{
		set->stage++;
		_HashSet_scale(set);
	}

	_HSetEntry *candidate = &set->entries[hash_a % set->cap];
	uint32_t collisions = 1;
	while (candidate->key != NULL && candidate->key != deleted_key) {
		if (key_equal(candidate, hash_a, len, key))
			return candidate->key; // Key is already in the set so return the string literal
		candidate = &set->entries[(hash_a + collisions++ * (hash_b + 1)) % set->cap];
	}

	if (!copy) return key; // when resizing don't retake your own ownership

	// Key is not in set so need to insert
	char* keyCopy = malloc(len + 1);
	memcpy_s(keyCopy, len, key, len);
	keyCopy[len] = '\0'; // cstr's ftw
	// Copy Entry Data to candidate which is either empty or a deleted entry
	candidate->hash = hash_a;
	candidate->key = keyCopy;
	candidate->len = len;

	return (const char*)keyCopy;
}

const char* HashSet_insert(HashSet* set, const char* key, uint32_t len)
{
	const uint32_t hash_a = fnv_1a(key, len);
	return _HashSet_insert(set, false, hash_a, len, key);
}

const char** HashSet_toKeyArray(HashSet* set)
{
	const char** array = malloc(set->cnt);
	HashSet_destroy(set);
	return array;
}