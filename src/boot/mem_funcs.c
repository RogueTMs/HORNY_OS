#include "mem_funcs.h"

void mem_zero(short int* start, int len){
	for (int index = 0; index < len; index++){
		*((short int*) start++) = 0;
	}
}

void mem_cpy(short int* src, short int* dst, int len){
	for (int i = 0; i < len; i++){
		dst[i]= src[i];
	}
}

void myMemset(byte* ptr, int size) {
    for (int i = 0; i < size; i++) {
        *((byte*)ptr + i) = 0;
    }
}