set(stot_lib_src "")
set(stot_lib_test_src "")

stot_set_prop(stot_lib_test_src "main.c")

stot_set_prop(stot_lib_test_src "stot_test.h")
stot_set_prop(stot_lib_test_src "test_mem_poo.c")
stot_set_prop(stot_lib_test_src "test_hash.c")
stot_set_prop(stot_lib_test_src "assrt.h")
stot_set_prop(stot_lib_test_src "assrt.c")

# Public Files
stot_set_prop(stot_lib_src "incl/stot/mem_poo.h")
stot_set_prop(stot_lib_src "incl/stot/hash.h")
stot_set_prop(stot_lib_src "incl/stot/lp_string.h")
stot_set_prop(stot_lib_src "incl/stot/list.h")
stot_set_prop(stot_lib_src "incl/stot/bread.h")
stot_set_prop(stot_lib_src "incl/stot/mem_bread.h")
# Internal Files
stot_set_prop(stot_lib_src "lib/mem_poo.c")
stot_set_prop(stot_lib_src "lib/hash_set.c")
stot_set_prop(stot_lib_src "lib/hash_internal.h")
stot_set_prop(stot_lib_src "lib/hash_internal.c")
stot_set_prop(stot_lib_src "lib/lp_string.c")
stot_set_prop(stot_lib_src "lib/mem_bread.c")

if(CMAKE_PROJECT_NAME STREQUAL "stot_lib")
    add_executable(stot ${stot_lib_test_src} ${stot_lib_src})
    target_include_directories(stot PUBLIC "incl")
else()
    add_library(stot_lib ${stot_lib_src})
    target_include_directories(stot_lib PUBLIC "incl")
endif()

if(CMAKE_GENERATOR MATCHES "Visual Studio")
	source_group("src" FILES ${stot_lib_src})
	source_group("test" FILES ${stot_lib_test_src})
endif()