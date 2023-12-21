#pragma once

typedef unsigned int u32;
typedef unsigned short u16;

typedef struct {
    u32 edi;
    u32 esi;
    u32 ebp;
    u32 esp; 
    u32 ebx;
    u32 edx;
    u32 ecx;
    u32 eax;
    u16 gs;
    u16 p1;
    u16 fs;
    u16 p2;
    u16 es;
    u16 p3;
    u16 ds;
    u16 p4;
    u32 vector;
    u32 errorCode;
    u32 eip;
    u16 cs;
    u16 p5;
    u32 eflags;
    u32 esp_1;
    u16 ss;
} context;

void create_context(void* ptr, u32 size, u32 eip);

void default_handler(context* ctx);

void timer_handler(context* ctx);

void print_interrupt(context* ctx);

void set_esp(u32 esp);
