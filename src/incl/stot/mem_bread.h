#ifndef stot_lib_mem_bread_h
#define stot_lib_mem_bread_h

#include "bread.h"

#ifndef BUFSIZ
#define BUFSIZ 512
#endif

typedef struct {
	Bread bread;
	// Impl fields
	int _index;
	int _len;
	const char* _input;
	char _buffer[BUFSIZ];
} MemBread;

void MemBread_init(MemBread* mem_bread);
void MemBread_setMockInput(MemBread* mem_bread, const char* input);

#endif