#include "kernel_alloc.h"
#include "kernel_panic.h"

void myMemset(byte* ptr, int size) {
    for (int i = 0; i < size; i++) {
        *((byte*)ptr + i) = 0;
    }
}


byte* kernel_malloc(u32 size) {
    if ((byte*) curr + size < end) {
        byte* tmp = curr;
        curr = ((byte*) curr) + size;
        return tmp;
    } else {
        kernel_panic("PANIC IN MALLOC");
        return (void*) 0;
    }
}


byte* kernel_calloc(u32 size) {
    byte* res = kernel_malloc(size);
    myMemset(res, size);
    return res; 
}


byte* kernel_realloc(void* old_addr, u32 new_size) {
    if ((byte*)old_addr + new_size < end) {
        curr = (byte*) old_addr + new_size;
        return old_addr;
    } else {
        kernel_panic("PANIC IN REALLOC");
    }
}

void  kernel_free(void* addr);