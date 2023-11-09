#pragma once

typedef char byte;

typedef unsigned int u32;

typedef unsigned short u16;

typedef char u8;


#define ALLOC_START 0x100000
#define ALLOC_END 0x400000

// #define MAX_SIZE 0x400000 - 0x100000
// #define BLOCK_SIZE 0x500
// 0x2FFFFF % 0x17FD = 0
// byte* curr = (byte*) START;
// byte* next = (byte*) START;

void* curr = (void*) ALLOC_START;


byte* kernel_malloc(u32 size);
byte* kernel_calloc(u32 size);
byte* kernel_realloc(void* old_addr, u32 new_size);
void  kernel_free(void* addr);
void myMemset(byte* ptr, int size);
 