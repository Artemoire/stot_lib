#ifndef stot_lib_mem_poo_h
#define stot_lib_mem_poo_h

#include <stdlib.h>

#ifndef MEMPOO_PAGESIZ
#define MEMPOO_PAGESIZ 16384
#endif

/*
 *
 * Linked list of "large" memory blocks
 *
 */
typedef struct _MemPoo {
	struct _MemPoo* _previous;
	size_t _commited;

	unsigned char data[];
} MemPoo;

/**/
MemPoo* MemPoo_ctor(MemPoo* previous);
/*
 *
 * Tries to return a ptr to memory size of 'size' inside 'mem';
 * If not enough space allocates a new MemPoo and repoints 'mem';
 * If size > MEMPOO_PAGESIZ returns NULL;
 */
void* MemPoo_alloc(MemPoo** mem, size_t size);
/*
 *
 * Iterates through the linked list of MemoryBlocks and frees each one;
 */
void MemPoo_free(MemPoo* mem);

#endif