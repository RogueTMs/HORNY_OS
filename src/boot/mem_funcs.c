#include "mem_funcs.h"

void mem_cpy(void* src, void* dst, int len){
	for (int i = 0; i < len; i++){
		*((byte*) dst + i) = *((byte*) src + i);
	}
}

void myMemset(void* ptr, int size) {
    for (int i = 0; i < size; i++) {
        *((byte*) ptr + i) = 0;
    }
}