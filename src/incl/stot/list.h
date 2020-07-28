#ifndef stot_lib_list_h
#define stot_lib_list_h

typedef struct _ptr_list {
	struct _ptr_list* next;
	void* curr;
} ptr_list;

#endif