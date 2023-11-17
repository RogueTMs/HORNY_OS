#include "kernel_alloc.h"
#include "kernel_panic.h"
#include "mem_funcs.h"

static void* curr = (void*) ALLOC_START;
static byte* const end = (void*) ALLOC_END;


byte* kernel_malloc(u32 size) {
    if ((byte*) curr + size < end) {
        byte* tmp = curr;
        curr = ((byte*) curr) + size;
        return tmp;
    } else {
        kernel_panic("PANIC IN MALLOC");
    }
}


byte* kernel_calloc(u32 size) {
    byte* res = kernel_malloc(size);
    myMemset(res, size);
    return res; 
}


byte* kernel_realloc(void* old_addr, u32 new_size) {

    byte* new_addr = kernel_malloc(new_size);
    mem_cpy(old_addr, new_addr, new_size);
    return new_addr;
}

void  kernel_free(void* addr){};