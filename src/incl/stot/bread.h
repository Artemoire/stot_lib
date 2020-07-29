#ifndef stot_lib_bread_h
#define stot_lib_bread_h

#include <stdbool.h>
#include <stdio.h>

typedef struct vtable_Bread _vtable_Bread;

typedef bool (*f_Bread_action)(_vtable_Bread*);
typedef bool (*f_Bread_open)(_vtable_Bread*, const char*);

typedef struct {
	f_Bread_open f_open;
	f_Bread_action f_update;
	f_Bread_action f_close;
} vtable_Bread;

// Virtual reading from a intermediary buffer, implementation specifies size of buffer
typedef struct
{
	vtable_Bread interface;
	char* buffer;
} Bread;

#endif