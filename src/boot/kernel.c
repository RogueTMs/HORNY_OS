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
void set_esp(u32 esp);

void process_1();
void process_2();
void process_3();
void process_4();

context ctx;
u32 stack_ptrs[4];
u32 eips[4];

void* processes[4];

console consoles[4];

void __main(){
    init_printer();
    init_IDT();
    char* s =
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
    // for (int i = 0; i < 4000; i++) {
    //   print('?');
    // }
    // print("b");
    // vga_print_char('A', 0, 0);
    // printNum(0x0, numLen(0, 10), 10);
    for (u32 i = 0; i < 4; i++) {
      processes[i] = kernel_malloc(STACK_SIZE);
//      print("%x\n", processes[i]);
      stack_ptrs[i] = (u32) (processes[i] + STACK_SIZE - sizeof(context));
    }
    init_pics();
    // experiment();
    init_console(consoles, 0, 0, 12, 40);
    init_console(consoles + 1, 40, 0, 12, 40);
    init_console(consoles + 2, 0, 13, 12, 40);
    init_console(consoles + 3, 40, 13, 12, 40);

    void (*ptr_1)(void) = &process_1;
    void (*ptr_2)(void) = &process_2;
    void (*ptr_3)(void) = &process_3;
    void (*ptr_4)(void) = &process_4;

//    print("%x\n", ptr_1);
//    print("%x\n", ptr_2);
//    print("%x\n", ptr_3);
//    print("%x\n", ptr_4);
//    void* ptr_1 = &process_1;
//    void* ptr_2 = &process_2;
//    void* ptr_3 = &process_3;
//    void* ptr_4 = &process_4;
//    eips[0] = (u32) ptr_1;
//    eips[1] = (u32) ptr_2;
//    eips[2] = (u32) ptr_3;
//    eips[3] = (u32) ptr_4;
    create_context(processes[0], STACK_SIZE, (u32) ptr_1);
    create_context(processes[1], STACK_SIZE, (u32) ptr_2);
    create_context(processes[2], STACK_SIZE, (u32) ptr_3);
    create_context(processes[3], STACK_SIZE, (u32) ptr_4);

//    print("%x\n", ((context* ) (stack_ptrs[0]))->eip);
//    print("%x\n", ((context* ) (stack_ptrs[1]))->eip);
//    print("%x\n", ((context* ) (stack_ptrs[2]))->eip);
//    print("%x\n", ((context* ) (stack_ptrs[3]))->eip);
    // print("%x", processes[0]);
    // console_print(&cnsl1, "%d ", 123);
    // for (u32 i = 0; i < 500; i++) {
    //   console_print(&cnsl1, "%d ", i);
    // }
//    set_esp(stack_ptrs[0]);
    asm("sti");
//    process_1();
//    process_2();
//    process_3();
//    process_4();
    // for (int i = 0;;i++) {
    //   print("*");
    // }
    for(;;);
//    asm("hlt");
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