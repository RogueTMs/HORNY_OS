#include "vga_funcs.h"
#include "utils_funcs.h"
#include "kernel_panic.h"
#include "kernel_alloc.h"
#include "tramplins.h"
#include "pics.h"



/*

- 80*25 - columns * lines 
- RAM range [0xB8000 - 0xB8FA0) - 4000 in dec -> instant screen display
- coords (x, y) -> 0xB8000 + 2*(y*80 + x) -> btw we use byte type that takes 2bytes
-> 0xB8000 + (y*80 + x)  (defined after several experiments)
- bit mask  | bgc    | fgc  |  symbol code  | <- bitwise OR or +
-           |{1/0}000| 0000 |   10101010    |

*/

// 


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
  // print("%s", s);
  // init_pics(1, 1);
  extern void notsti();
  notsti();
  // int i = 1 / 0;
  // printNum(0x0, numLen(0, 10), 10);
	for (;;);
}

