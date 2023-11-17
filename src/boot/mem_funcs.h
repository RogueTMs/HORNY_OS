#pragma once

typedef char byte;

void mem_cpy(short int* src, short int* dst, int len);
void mem_zero(short int* start, int len);
void myMemset(byte* ptr, int size);