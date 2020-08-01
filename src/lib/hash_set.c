#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#include "stot/hash.h"
#include "hash_internal.h"

static str * deleted_key = (str*)1;

static size_t fnv_1a(str* key)
{
	size_t hash = 2166136261u;

	for (size_t i = 0; i < key->len; i++) {
		hash ^= key->buffer[i];
		hash *= 16777619;
	}

	return hash;
}

static size_t fnv_1(str* key)
{
	size_t hash = 2166136261u;

	for (size_t i = 0; i < key->len; i++) {
		hash *= 16777619;
		hash ^= key->buffer[i];
	}

	return hash;
}

static inline bool _key_equal(HashSet_Entry* entry, size_t hash, str* key)
{
	return entry->hash == hash && entry->key->len == key->len && strncmp(entry->key->buffer, key->buffer, key->len) == 0;
}

static HashSet_Entry* _HashSet_find_entry(HashSet* set, size_t hash_a, str* key)
{
	const size_t hash_b = fnv_1(key);

	HashSet_Entry *candidate = &set->entries[hash_a % set->cap];
	HashSet_Entry *deleted = NULL;

	uint32_t collisions = 1;
	while (candidate->key != NULL) {
		if (_key_equal(candidate, hash_a, key)) { // found the key return self
			return candidate;
		}
		else if (candidate->key == deleted_key && deleted == NULL) {
			deleted = candidate;
		}

		candidate = &set->entries[(hash_a + collisions++ * (hash_b + 1)) % set->cap];
	}

	return (deleted == NULL) ? candidate : deleted;
}

void HashSet_init(HashSet* set)
{
	set->cap = 31;
	set->cnt = 0;
	set->stage = 5;
	set->entries = calloc(32, sizeof(HashSet_Entry));
}

void HashSet_destroy(HashSet* set)
{
	set->cap = 0;
	set->cnt = 0;
	set->stage = 0;
	free(set->entries);
	set->entries = NULL;
}

static void _HashSet_scale(HashSet* set)
{
	size_t prevCap = set->cap;
	HashSet_Entry *prevEntries = set->entries;

	// TODO: MaxStage ?
	set->cap = (1 << set->stage) - plt2n_diff_table[set->stage];
	set->cnt = 0;
	set->entries = calloc((1 << set->stage), sizeof(HashSet_Entry));

	for (size_t i = 0; i < prevCap; i++) {
		HashSet_Entry* entry = &prevEntries[i];
		if (entry->key != NULL && entry->key != deleted_key) {
			HashSet_Entry *new_entry = _HashSet_find_entry(set, entry->hash, entry->key); // should return empty always
			new_entry->hash = entry->hash;
			new_entry->key = entry->key;
		}
	}

	free(prevEntries);
}

HashSet_Entry* HashSet_insert(HashSet* set, str* key)
{
	const size_t hash_a = fnv_1a(key);

	// TODO: max stage ?
	if ((set->cnt * 100 / set->cap) >= 75)
	{
		set->stage++;
		_HashSet_scale(set);
	}

	HashSet_Entry *entry = _HashSet_find_entry(set, hash_a, key);

	if (entry->key == NULL || entry->key == deleted_key) {
		set->cnt++;
		entry->hash = hash_a;
		entry->key = key;
	}

	return entry;
}

bool HashSet_remove(HashSet* set, str* key)
{
	const size_t hash_a = fnv_1a(key);

	HashSet_Entry *entry = _HashSet_find_entry(set, hash_a, key);

	if (entry->key != NULL && entry->key != deleted_key) {
		entry->hash = 0;
		entry->key = deleted_key;

		set->cnt--;
		// TODO: scale down?

		return true;
	}

	return false;
}

str** HashSet_keys(HashSet* set)
{
	str** arr = malloc(sizeof(str *) * set->cnt);
	size_t k = 0;
	for (size_t i = 0; i < set->cap; ++i) {

		if (set->entries[i].key != NULL && set->entries[i].key != deleted_key) {
			arr[k++] = set->entries[i].key;
		}
	}
	return arr;
}
