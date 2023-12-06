#include "vga_funcs.h"
#include "kernel_panic.h"

void kernel_panic(char* fmt, ...) {
    init_printer();
    char* pointer = (void*) &fmt;
    pointer += sizeof(char*);
    print_impl(fmt, pointer);
    for(;;);
}

