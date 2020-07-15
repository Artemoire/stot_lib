#ifndef stot_lib_hash_table_h
#define stot_lib_hash_table_h

typedef struct {
    char* key;
    char* value;
} ht_item;

typedef struct {
    int size;
    int count;
    ht_item** items;
} ht_hash_table;

#endif