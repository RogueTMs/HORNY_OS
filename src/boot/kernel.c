/*

- 80*25 - columns * lines 
- RAM range [0xB8000 - 0xB8FA0) - 4000 in dec -> instant screen display
- coords (x, y) -> 0xB8000 + 2*(y*80 + x) -> btw we use short int type that takes 2bytes
-> 0xB8000 + (y*80 + x)  (defined after several experiments)
- bit mask  | bgc    | fgc  |  symbol code  | <- bitwise OR or +
-           |{1/0}000| 0000 |   10101010    |

*/

#define SIZE 4000
#define START 0xB8000
#define LENGTH 80
#define HEIGHT 25


// int check_overflow_len(int coord){
// 	int coord = coord % LENGTH;
// 	if (coord < 0) return coord + LENGTH;
// 	return coord;
// }

// int check_overflow_height(int coord){
// 	int coord = coord % HEIGHT;
// 	if (coord < 0) return coord + HEIGHT;
// 	return coord;
// }


int X;
int Y;



void vga_clear_screen(){
	short int* start = (short int*) START;
	for (int index = 0; index < SIZE; index++){
		*((short int*) start++) = 0;
	}
}

void vga_print_char(char symbol, int x, int y){
	if (symbol != '\n') {
		short int bit_mask = 0b0000101000000000;
		bit_mask |= (short int) symbol;
		*((short int*) START + (y * LENGTH + x)) = bit_mask;  
	}
}

void vga_test_fill_screen(char symbol){
	for(int i = 0; i < LENGTH; i++){
		for (int j = 0; j < HEIGHT; j++){
			vga_print_char(symbol, i, j);
		}
	}
}

void vga_print_str(char* str, int x, int y){
	int index = 0;
	int x_coord = x;
	int y_coord = y;
	int start = START;

	while (str[index] != '\0'){
		char curr = str[index++];
		if (curr == '\n') {
			x_coord = LENGTH;
		}
		vga_print_char(curr, x_coord, y_coord);
		x_coord++;
		if (x_coord >= LENGTH){
			y_coord++;
			x_coord = 0;
		}
		if (y_coord >= HEIGHT){
			short int* start = (short int*) START;
			for (int i = 0; i < SIZE - LENGTH; i++){
				*((short int*) (start + i)) = *((short int*) (start + i + LENGTH));
			}
			y_coord = HEIGHT - 1;
			vga_print_char(curr, x_coord, y_coord);
		}

	}
}

void init_printer(){
	X = 0;
	Y = 0;
	vga_clear_screen();
}

void print(char* fmt, ...){
}

void __main(){
	// vga_clear_screen();	
	// vga_print_char('G', 10, 10);
	*((short int*) START) = 0;
	// vga_print_str("q\ng\nve\nr\nt\ny\nu\ni\no\nqvd\nf\ng\nh\nj\nj\ng\n\nv\nf\nv\ng\nh\nj\nv\nj\nj\nk\nd", 0, 0);

	// int stack_pointer;
	// __asm__("movl %1, esp");
	for (;;);
}

