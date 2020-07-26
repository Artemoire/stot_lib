#ifndef stot_lib_hash_table_h
#define stot_lib_hash_table_h

#include <stdint.h>

#include "lp_string.h"

typedef struct {
	uint32_t hash;
	lp_string* key;
} _HSetEntry;

typedef struct {
	uint8_t stage;
	size_t cap;
    size_t cnt;
	_HSetEntry* entries;
} HashSet;

void HashSet_init(HashSet* set);
void HashSet_destroy(HashSet* set);

lp_string* HashSet_insert(HashSet* set, lp_string* key);

lp_string** HashSet_keys(HashSet* set);

#endif