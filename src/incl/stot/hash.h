#ifndef stot_lib_hash_table_h
#define stot_lib_hash_table_h

#include <stdint.h>
#include <stdbool.h>

#include "lp_string.h"

typedef struct {
	uint32_t hash;
	lp_string* key;
} HashSet_Entry;

typedef struct {
	uint8_t stage;
	size_t cap;
    size_t cnt;
	HashSet_Entry* entries;
} HashSet;

void HashSet_init(HashSet* set);
void HashSet_destroy(HashSet* set);

HashSet_Entry* HashSet_insert(HashSet* set, lp_string* key);
bool HashSet_remove(HashSet* set, lp_string* key);

lp_string** HashSet_keys(HashSet* set);

#endif