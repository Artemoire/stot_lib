#include <string.h>

#include "stot/mem_bread.h"

bool open(Bread* bread, const char* filename)
{
	return true;
}

bool update(Bread* bread)
{
	MemBread* mem_bread = (MemBread*)bread;
	for (int i = 0; i < BUFSIZ; ++i) {
		if (mem_bread->_input[mem_bread->_index] != '\0') {
			mem_bread->_buffer[i] = mem_bread->_input[mem_bread->_index++];
		}
		else {
			mem_bread->_buffer[i] = '\0';
			return true;
		}
	}
	return true;
}

bool close(Bread* bread)
{
	return true;
}

static vtable_Bread mem_bread_interface = { open, update, close };

void MemBread_init(MemBread* mem_bread)
{
	mem_bread->bread.interface = mem_bread_interface;
	mem_bread->bread.buffer = &mem_bread->_buffer;
	mem_bread->_index = 0;
	mem_bread->_len = 0;
	mem_bread->_input = NULL;
}

void MemBread_setMockInput(MemBread* mem_bread, const char* input)
{
	mem_bread->_input = input;
	mem_bread->_len = strnlen_s(input, 65536);
	mem_bread->_index = 0;
}