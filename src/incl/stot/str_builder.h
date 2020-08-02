#ifndef stot_lib_str_builder_h
#define stot_lib_str_builder_h

#include <stdbool.h>

#include "transient_stack.h"
#include "str.h"

typedef struct {
	tstack* _ts;
	str* state;
} ts_str_builder;

bool ts_str_builder_init(ts_str_builder* builder, tstack* ts);
bool ts_str_builder_append(ts_str_builder* builder, const char* data, size_t len);
void ts_str_builder_destroy(ts_str_builder* builder);

#endif