#include "stot_test.h"

#include "stot/mem_poo.h"

#include  <stdio.h>

static void mem_write()
{
	// Should crash horribly if doesn't pass (R/W Exception or smth)
	MemPoo* mem = MemPoo_ctor(NULL);
	mem->data[MEMPOO_PAGESIZ - 1] = 69;
	ASSRT_EQ(mem->data[MEMPOO_PAGESIZ - 1], 69);
	MemPoo_free(mem);
}

static void mem_alloc()
{
	MemPoo* mem = MemPoo_ctor(NULL);
	char* str_o = MemPoo_alloc(&mem, 1);
	char* str_k = MemPoo_alloc(&mem, 10);
	char* check = MemPoo_alloc(&mem, 10);
	str_o[0] = 'o';
	str_o[1] = 'k';
	ASSRT_EQ(str_k[0], 'k'); // Test if continuous allocation
	ASSRT_EQ((check - str_k), 10); // Same
	MemPoo_free(mem);
}

static void page_alloc()
{
	MemPoo* mem = MemPoo_ctor(NULL);
	MemPoo* old_mem = mem;
	void* b1 = MemPoo_alloc(&mem, MEMPOO_PAGESIZ / 2);
	void* b2 = MemPoo_alloc(&mem, MEMPOO_PAGESIZ / 2);
	void* b3 = MemPoo_alloc(&mem, MEMPOO_PAGESIZ / 2); // should allocate second block meaning mem != old_mem
	ASSRT_NEQ(mem, old_mem);
	MemPoo_free(mem);
}

static void no_alloc()
{
	MemPoo* mem = MemPoo_ctor(NULL);
	void* no_mem = MemPoo_alloc(&mem, MEMPOO_PAGESIZ + 1);
	ASSRT_EQ(no_mem, NULL);
	MemPoo_free(mem);
}

static void mem_reuse() {
	MemPoo* mem = MemPoo_ctor(NULL);	
	MemPoo_free(mem);

	MemPoo* mem_2 = MemPoo_ctor(NULL);
	ASSRT_EQ(mem, mem_2); // If this doesn't work, there's no point to MemPoo
}

void test_MemPoo()
{
	TEST_FUNC(test_MemPoo, mem_write);
	TEST_FUNC(test_MemPoo, mem_alloc);
	TEST_FUNC(test_MemPoo, page_alloc);
	TEST_FUNC(test_MemPoo, no_alloc);
	TEST_FUNC(test_MemPoo, mem_reuse);
}