#include "kernel_alloc.h"

void myMemset(void* ptr, int size) {
    for (int i = 0; i < size; i++) {
        *((byte*)ptr + i) = 0;
    }
}


byte* kernel_malloc(u32 size) {
    if ((byte*) curr + size < ALLOC_END) {
        byte* tmp = curr;
        (byte*) curr += size;
        return tmp;
    } else {
        kernel_panic("PANIC IN MALLOC");
    }
}


byte* kernel_calloc(u32 size) {
    byte* res = kernel_malloc(size);
    memset(res, size);
    return res; 
}

//  [1 1 1 1 1 1 0 0 0 0]
//     ^

byte* kernel_realloc(void* old_addr, u32 new_size) {
    if ((byte*)old_addr + new_size < ALLOC_END) {
        curr = (byte*) old_addr + new_size;
        return old_addr;
    } else {
        kernel_panic("PANIC IN REALLOC");
    }
}

void  kernel_free(void* addr);