#ifndef stot_lib_transient_stack_h
#define stot_lib_transient_stack_h

#include <stddef.h>

#ifndef TSTACK_SIZ
#define TSTACK_SIZ 16384
#endif

typedef struct {
	size_t _commited;
	unsigned char data[];
} tstack;

tstack* tstack_ctor();
void* tstack_alloc(tstack* ts, size_t size);

#endif