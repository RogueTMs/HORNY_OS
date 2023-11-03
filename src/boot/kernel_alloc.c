#include "kernel_alloc.h"

void memset(void* ptr, int size) {
    for (int i = 0; i < size; i++) {
        *((byte*)ptr + i) = 0;
    }
}


int isNull(byte* ptr) {
    if (!(ptr)) {
        return 1;
    }
    return 0;
}



byte* kernel_malloc(u32 size) {
    if ((byte*) curr + size < END) {
        byte* tmp = curr;
        (byte*)curr += size;
        return tmp;
    } else {
        return NULL;
    }
}


byte* kernel_calloc(u32 size) {
    byte* res = kernel_malloc(size);
    if (isNull(res)) {
        return NULL;
    }
    memset(res, size);
    return res; 
}

byte* kernel_realloc(void* old_addr, u32 new_size) {
    if ((byte*)old_addr + new_size < END) {
        curr = (byte*)old_addr + new_size;
        return old_addr;
    } else {
        return NULL;
    }
}

void  kernel_free(void* addr);