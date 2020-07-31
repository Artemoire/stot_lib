#include <stdio.h>
#include <stdlib.h>

#include <string.h>

#include "stot/lp_string.h"

lp_string* lp_string_copy(size_t len, const char* data)
{
	lp_string* _new = malloc(sizeof(len) + sizeof(char)*(len + 1)); // len .. data .. '\0'

	memcpy(_new->data, data, len);
	_new->data[len] = '\0'; // c_str ftw
	_new->len = len;
	
	return _new;
}