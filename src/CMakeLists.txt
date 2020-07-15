set(stot_src "")

INCL_FILE(stot_src "main.c")

INCL_FILE(stot_src "stot_test.h")
INCL_FILE(stot_src "test_mem_poo.c")
INCL_FILE(stot_src "test_hash_table.c")
INCL_SRC(stot_src "assrt")

INCL_SRC(stot_src "lib/mem_poo")
INCL_SRC(stot_src "lib/hash_table")
INCL_SRC(stot_src "lib/prime")

add_executable(stot_test ${stot_src})