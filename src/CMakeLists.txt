set(stot_src "")

INCL_FILE(stot_src "main.c")

INCL_FILE(stot_src "stot_test.h")
INCL_FILE(stot_src "test_mem_poo.c")
INCL_SRC(stot_src "assrt")

INCL_SRC(stot_src "lib/mem_poo")

add_executable(stot_test ${stot_src})