#include "stot_test.h"

#include "stot/str_builder.h"
#include "stot/transient_stack.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void building()
{
#define B_APPEND(x) ts_str_builder_append(&builder, x, sizeof(x)-1)
	ts_str_builder builder;
	tstack* tstack = tstack_ctor();
	ts_str_builder_init(&builder, tstack);

	B_APPEND("abc");
	B_APPEND("123");

	ASSRT_EQ(builder.state->len, 6);
	printf("%s\n", builder.state->buffer);
	
	free(tstack);
#undef B_APPEND
}

void releasing()
{
#define B_APPEND(x) ts_str_builder_append(&builder, x, sizeof(x)-1)

	ts_str_builder builder;
	tstack* tstack = tstack_ctor();
	tstack_alloc(tstack, 5);
	ts_str_builder_init(&builder, tstack);

	B_APPEND("abc123\n");

	ts_str_builder_destroy(&builder);
	ASSRT_EQ(tstack->_commited, 5);
	free(tstack);

#undef B_APPEND
}

void test_str_builder()
{
	TEST_FUNC(test_str, building);
	TEST_FUNC(test_str, releasing);
}