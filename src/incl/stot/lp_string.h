#ifndef stot_lib_lp_string_h
#define stot_lib_lp_string_h

#include <stddef.h>

typedef struct {
	size_t len;
	char data[];
} lp_string;

typedef struct {
	size_t len;
	char data[512];
} lp_string_b512;

lp_string* lp_string_copy(size_t len, const char* data);

#endif