
with open("src/boot/tramplins.c", "w", encoding="ASCII") as file:
    print("#include \"kernel_alloc.h\"\n", file=file)
    print("#include \"tramplins.h\"\n", file=file)
    
    s = '''static void panic_handler(int vector) {
    kernel_panic("Unhandled interrupt %x", vector);
}'''
    print(s, file=file)
    
    print("GateDescriptor* idt = (GateDescriptor*) kernel_malloc(sizeof(GateDescriptor) * 256);\n", file=file)
    
    
    for i in range(256):
        interupt = hex(i)[2:]
        if len(interupt) == 1:
            interupt = "0" + interupt
        file.write(f"static void tramplin_{interupt}()" + "{" + f"panic_handler(0x{interupt});" + "}\n")
    file.write("static void** tramplins = {")

    for i in range(256):
        interupt = hex(i)[2:]
        if len(interupt) == 1:
            interupt = "0" + interupt
        if i != 255:
            print(f"tramplin_{interupt}", end=", ", file=file)
        else:
            print(f"tramplin_{interupt}", end="};", file=file)
            
            
    print("\n", file=file)
    
    s = """for (int vector = 0; vector < IDT_SIZE; vector++) {
    byte* handler = tramplins[vector];
    u16 low_16_bits = (u16) handler;
    u16 high_16_bits = (u16) ((u32) handler) >> 16);
    idt[vector].offset_1 = low_16_bits;
    idt[vector].selector = 0x8;
    idt[vector].zero = 0;
    idt[vector].gate_type = 0xE;
    idt[vector].dpl = 0;
    idt[vector].offset_2 = high_16_bits;
}

DIDT didt;
init(&didt, sizeof(GateDescriptor*) * 256 - 1, idt);

u16 adr = (u16) &didt;


__asm__ ("lidt %0": "=r" (adr));
__asm__ ("int 0x13");
"""
    print(s, file=file)
    

with open("src/boot/tramplins.h", "w", encoding="ASCII") as file:

    s = '''#pragma once

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

void init(DIDT* didt, int size, void* address);'''
    
    print(s, file=file)
    
    print("static void panic_handler(int vector);", file=file)
    
    for i in range(256):
        interupt = hex(i)[2:]
        if len(interupt) == 1:
            interupt = "0" + interupt
        file.write(f"static void tramplin_{interupt}();\n")

