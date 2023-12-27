#include "vga_funcs.h"
#include "tramplins.h"
#include "pics.h"
#include "console.h"
#include "kernel_alloc.h"
#include "handlers.h"
#include "mem_funcs.h"


#define STACK_SIZE 0x10000

/*

- 80*25 - columns * lines 
- RAM range [0xB8000 - 0xB8FA0) - 4000 in dec -> instant screen display
- coords (x, y) -> 0xB8000 + 2*(y*80 + x) -> btw we use byte type that takes 2bytes
-> 0xB8000 + (y*80 + x)  (defined after several experiments)
- bit mask  | bgc    | fgc  |  symbol code  | <- bitwise OR or +
-           |{1/0}000| 0000 |   10101010    |

*/

// 

void experiment();

void entry1();

void entry2();

void entry3();

void entry4();

void process_1();

void process_2();

void process_3();

void process_4();

context ctx;
context* stack_ptrs[4];
u32 eips[4];

void *processes[4];

console consoles[4];

void __main() {
    init_printer();
    init_IDT();
    char *s =
            "\n\n\n\n\n\n\n \
                                      ______________\n\
                                      |              |\n\
                                      |   H O R N Y  |\n\
                              /\\      |______________|\n\
                            | |   ( \\_/ )   ||    \n\
                            | |   (^ 3 ^)   ||     \n\
                            _| |_  /     \\   ||     \n\
                              q===|       |===p     \n\
                                  \\_ o _/        \n\
                                    ^   ^";

    for (u32 i = 0; i < 4; i++) {
        processes[i] = kernel_malloc(STACK_SIZE);
    }
    init_pics();
    // experiment();
    init_console(consoles, 0, 0, 12, 39, 0b0000000100000000);
    init_console(consoles + 1, 41, 0, 12, 39, 0b0000011100000000);
    init_console(consoles + 2, 0, 13, 12, 39, 0b0000010100000000);
    init_console(consoles + 3, 41, 13, 12, 39, 0b000001100000000);

    void (*ptr_1)(void) = &process_1;
    void (*ptr_2)(void) = &process_2;
    void (*ptr_3)(void) = &process_3;
    void (*ptr_4)(void) = &process_4;

    stack_ptrs[0] = create_context(processes[0], STACK_SIZE, (u32) ptr_1);
    stack_ptrs[1] = create_context(processes[1], STACK_SIZE, (u32) ptr_2);
    stack_ptrs[2] = create_context(processes[2], STACK_SIZE, (u32) ptr_3);
    stack_ptrs[3] = create_context(processes[3], STACK_SIZE, (u32) ptr_4);

    asm("sti");
    for (;;);
}

void process_1() {
    for (;;) {
        entry1();
    }
}

void process_2() {
    for (;;) {
        entry2();
    }
}

void process_3() {
    for (;;) {
        entry3();
    }
}

void process_4() {
    for (;;) {
        entry4();
    }
}