#ifndef stt_lib_mem_poo_h
#define stt_lib_mem_poo_h

#include <stdlib.h>

#ifndef MEMPOO_PAGESIZ
#define MEMPOO_PAGESIZ 16384
#endif

typedef struct _MemPoo {
	struct _MemPoo* _previous;
	size_t _commited;

	unsigned char data[];
} MemPoo;

MemPoo* MemPoo_ctor(MemPoo* previous);
void* MemPoo_alloc(MemPoo** mem, size_t size);
void MemPoo_free(MemPoo* mem);

#endif