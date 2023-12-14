#include "vga_funcs.h"
#include "tramplins.h"
#include "pics.h"
#include "console.h"
#include "kernel_alloc.h"
#include "handlers.h"
#include "mem_funcs.h"


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
void pr_1();
void process();
void change_esp(u32 esp);
context ctx;

void* processes[4];

console cons;

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
      processes[i] = kernel_malloc(0x50000);
    }
    init_pics();
    // experiment();
    init_console(&cons, 0, 0, 12, 40);
    void (*process_ptr)(void) = &process;
    // print("%x", processes[0]);
    init_fake_context(&ctx, (u32) process_ptr);
    mem_cpy(&ctx, processes[0], sizeof(context));
    change_esp((u32)((byte*) processes[0] + sizeof(context)));
    // console_print(&cnsl1, "%d ", 123);
    // for (u32 i = 0; i < 500; i++) {
    //   console_print(&cnsl1, "%d ", i);
    // }
    // asm("sti");
    // for (int i = 0;;i++) {
    //   print("*");
    // }
    for(;;);
}

void process() {
  for (;;) {
    pr_1();
  }
}