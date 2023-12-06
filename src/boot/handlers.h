#pragma once

typedef unsigned int u32;
typedef unsigned short u16;

void default_handler(u32 edi, u32 esi, u32 ebp, u32 esp, u32 ebx, u32 edx, u32 ecx, u32 eax, u16 gs, u16 fs,\
u16 es, u16 ds, u32 vector, u32 errorCode, u32 eip, u16 cs, u32 eflags, u32 process_esp, u16 ss);

void timer_interrupt(u32 edi, u32 esi, u32 ebp, u32 esp, u32 ebx, u32 edx, u32 ecx, u32 eax, u16 gs, u16 fs,\
u16 es, u16 ds, u32 vector, u32 errorCode, u32 eip, u16 cs, u32 eflags, u32 process_esp, u16 ss);
