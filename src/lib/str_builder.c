#include <string.h>

#include "stot/str_builder.h"

bool ts_str_builder_init(ts_str_builder* builder, tstack* ts)
{
	builder->_ts = ts;
	builder->state = tstack_alloc(ts, sizeof(str));
	if (!builder->state) return false;
	builder->state->buffer = tstack_alloc(ts, sizeof(char));
	builder->state->cap = 0;
	builder->state->len = 0;
	builder->state->raw = false;

	return true;
}

bool ts_str_builder_append(ts_str_builder* builder, const char* data, size_t len)
{
	if (!tstack_alloc(builder->_ts, sizeof(char) * len)) {
		return false;
	}

	memcpy_s(builder->state->buffer + builder->state->len, len, data, len);
	builder->state->len += len;
	builder->state->cap += len;
	builder->state->buffer[builder->state->len] = '\0';

	return true;
}

void ts_str_builder_destroy(ts_str_builder* builder)
{
	builder->_ts->_commited -= builder->state->len;
	builder->_ts->_commited -= sizeof(char);
	builder->_ts->_commited -= sizeof(str);
	builder->_ts = NULL;
	builder->state = NULL;
}