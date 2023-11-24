#pragma once

typedef char byte;

typedef unsigned int u32;

typedef unsigned short u16;

typedef char u8;

byte* kernel_malloc(u32 size);
byte* kernel_calloc(u32 size);
byte* kernel_realloc(void* old_addr, u32 new_size);
void  kernel_free(void* addr);
 