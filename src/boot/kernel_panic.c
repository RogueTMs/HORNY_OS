#include "vga_funcs.h"
#include "utils_funcs.h"

void kernel_panic(char* fmt, ...) {
    __asm__ ("cli");
    init_printer();
    char* pointer = (void*) &fmt;
    pointer += sizeof(char*);
    print_impl(fmt, pointer);
    for (;;);
}

