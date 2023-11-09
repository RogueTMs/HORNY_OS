#pragma once

#pragma pack(push, 1)
typedef struct {
    u16 offset_1;
    u16 selector;
    u8 zero : 8;
    u8 gate_type : 4;
    u8 reserved0 : 1 = 0;
    u8 dpl : 2;
    u8 reserved1 : 1 = 1;
    u16 offset_2;
} GateDescriptor;


typedef struct {
    u16 idt_size;
    u32 idt_address;
} DIDT;
#pragma pack(pop)

void init(DIDT* didt, int size, void* address);