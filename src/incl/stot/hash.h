#ifndef stot_lib_hash_table_h
#define stot_lib_hash_table_h

#include <stdint.h>

typedef struct {
	uint32_t hash;
	uint32_t len;
	const char* key;
} _HSetEntry;

typedef struct {
	uint8_t stage;
	uint32_t cap;
    uint32_t cnt;
	_HSetEntry* entries;
} HashSet;

void HashSet_init(HashSet* set);
void HashSet_destroy(HashSet* set);

const char* HashSet_insert(HashSet* set, const char* key, uint32_t len);

const char** HashSet_toKeyArray(HashSet* set);

#endif