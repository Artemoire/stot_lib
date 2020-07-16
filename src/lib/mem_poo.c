#include <stdlib.h>

#include "stot/mem_poo.h"

MemPoo* MemPoo_ctor(MemPoo* previous)
{
	MemPoo* mem = malloc(sizeof(MemPoo) + sizeof(unsigned char)*MEMPOO_PAGESIZ);	
	mem->_previous = previous;	
	mem->_commited = 0;
	return mem;
}

void* MemPoo_alloc(MemPoo** mem, size_t size)
{
	if (size > MEMPOO_PAGESIZ) return NULL;

	if (((*mem)->_commited + size) > MEMPOO_PAGESIZ) {
		*mem = MemPoo_ctor(*mem);
	}

	void* alloced = (void*)&(*mem)->data[(*mem)->_commited];
	(*mem)->_commited += size;

	return alloced;
}

void MemPoo_free(MemPoo* mem)
{
	MemPoo* prev;
	while (mem != NULL) {
		prev = mem->_previous;
		free(mem);
		mem = prev;
	}
}
