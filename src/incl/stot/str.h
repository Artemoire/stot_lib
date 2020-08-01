#ifndef stot_lib_lp_string_h
#define stot_lib_lp_string_h

#include <stddef.h>
#include <stdbool.h>

typedef struct {
	bool raw;
	size_t len;
	size_t cap;
	char* buffer;
} str;

void str_raw(str* _str, const char* data);
void str_buffer_copy(str* _str, size_t len, const char* data);

#endif