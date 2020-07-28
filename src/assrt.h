#ifndef tests_assrt_h
#define tests_assrt_h

#include <stdbool.h>

#define TEST_FUNC(suite, func) test_func(#suite, #func, &func)

typedef void(*TestFunc)();

void test_func(const char* suite_name, const char* func_name, TestFunc test_func);

#define ASSRT_TRU(x) _assrt_tru(x)
#define ASSRT_EQ(a, b) _assrt_eq((void*)(a), (void*)(b))
#define ASSRT_NEQ(a, b) _assrt_neq((void*)(a), (void*)(b))

void _assrt_tru(bool x);
void _assrt_eq(void* a, void* b);
void _assrt_neq(void* a, void* b);
void test_conclude();

#endif