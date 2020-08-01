#include <stdio.h>
#include <stdlib.h>

#include <string.h>

#include "stot/str.h"

void str_raw(str* _str, const char* data)
{
	size_t data_size = strnlen(data, 65535); // TODO: why 65535
	const size_of_str = sizeof(char) * (data_size + 1);
	_str->buffer = malloc(size_of_str); // data .. '\0'	
	_str->cap = data_size;
	_str->len = data_size;
	_str->raw = true;
	memcpy_s(_str->buffer, size_of_str, data, size_of_str);
}

void str_buffer_copy(str* _str, size_t len, const char* data)
{
	_str->buffer = malloc(sizeof(char) * len + 1);
	_str->cap = len;
	_str->len = len;
	_str->raw = false;
	memcpy_s(_str->buffer, len * sizeof(char), data, len * sizeof(char));
	_str->buffer[len] = '\0'; // c_str ftw
}