#include <stdlib.h>

#include "stot/transient_stack.h"

tstack* tstack_ctor()
{
	tstack* ts = malloc(sizeof(tstack) + sizeof(unsigned char) * TSTACK_SIZ);
	ts->_commited = 0;
	return ts;
}

void* tstack_alloc(tstack* ts, size_t size)
{
	if ((ts->_commited + size) > TSTACK_SIZ) {
		// TODO: error reporting
		return NULL;
	}

	ts->_commited += size;
	return ts->data + size;
}