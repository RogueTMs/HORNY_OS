#pragma once

typedef unsigned int u32;
typedef unsigned short u16;

typedef struct {
    u16* start;
    u32 X;
    u32 Y;
    u32 HEIGHT;
    u32 LENGTH;
    u32 shift_X;
    u32 shift_Y;
} console;


void init_console(console* cnsl, u32 shift_X, u32 shift_Y, u32 HEIGHT, u32 LENGTH);
void console_print(console* cnsl, char* fmt, ...);