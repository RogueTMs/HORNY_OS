#include "vga_funcs.h"
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

void experiment();

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
  init_pics();
  experiment();
  // asm("sti");
  // for (int i = 0;;i++) {
  //   print("*");
  // }
}

