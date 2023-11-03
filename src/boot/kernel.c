/*

- 80*25 - columns * lines 
- RAM range [0xB8000 - 0xB8FA0) - 4000 in dec -> instant screen display
- coords (x, y) -> 0xB8000 + 2*(y*80 + x) -> btw we use byte type that takes 2bytes
-> 0xB8000 + (y*80 + x)  (defined after several experiments)
- bit mask  | bgc    | fgc  |  symbol code  | <- bitwise OR or +
-           |{1/0}000| 0000 |   10101010    |

*/

// 


#define SIZE 4000
#define START 0xB8000
#define LENGTH 80
#define HEIGHT 25

typedef char byte;

int X;
int Y;

void mem_zero(short int* start, int len){
	for (int index = 0; index < len; index++){
		*((short int*) start++) = 0;
	}
}

void mem_cpy(short int* src, short int* dst, int len){
	for (int i = 0; i < len; i++){
		*((short int*) (dst + i)) = *((short int*) (src + i));
	}
}

void vga_clear_screen(){
	short int* start = (short int*) START;
	mem_zero(start, SIZE);
	
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


void scroll() {
	short int* start = (short int*) START;
	mem_cpy(start + 80, start, SIZE);
	Y = HEIGHT - 1;
}


void vga_print_str(char* str, int x, int y){
	int index = 0;
	int x_coord = x;
	int y_coord = y;

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
	}
}

void init_printer(){
	X = 0;
	Y = 0;
	vga_clear_screen();
}

int len(char* s) {
	int i = 0;
	while (*(s + i++) != '\0');
	return i -1;
}

void scroll_check(int i) {
	int y = Y + (X + i) / LENGTH;
	if (y >= HEIGHT) {
		int diff = y - HEIGHT + 1;
		for (int i = 0; i < diff; i++) {
			scroll();
		}
		Y -= diff;
	}
}


int power(int x, int y) {
    int res = 1;
	if (y == 0) {
		return 1;
	}
	for (int i = 0; i < y; i++) {
		res *= x;
	}
	return res;
}

int numLen(int x, int base) {
	int c = x;
	int len = 0;
	while (c > 0) {
		c /= base;
		len++;
	}
	return len;
}


void printNum(int x, int len, int base) {
	len--;
	if (base == 10) {
		if (x < 0) {
			scroll_check(1);
			vga_print_char('-', X++, Y);
			x *= -1;
		}
	}
	while (len >= 0) {
		int p = power(base, len--);
		int curr = x / p;
		char c_curr;
		if (curr < 10) {
			c_curr = '0' + curr;
		} else {
			c_curr = 'A' + curr - 10;
		}
		vga_print_char(c_curr, X++, Y);
		x %= p;
	}
}

void print(char* fmt, ...){
	char* pointer = (void*) &fmt;
	pointer += sizeof(char*);

	while (*fmt != '\0'){
		char curr = *fmt++;  

		if (curr == '%') {
			int l;
			int n;
			switch (*fmt++)
			{
			case 's':
				char* s = *((char**) pointer);
				pointer += sizeof(char*);
				l = len(s);
				scroll_check(l);
				vga_print_str(s, X, Y);
				X = (X + l) % LENGTH;
				break;
			case 'd':
				n = *((int*) pointer);
				pointer += sizeof(int);
				l = numLen(n, 10);
				scroll_check(l);
				printNum(n, l, 10);
				break;
			case 'x':
				n = *((int*) pointer);
				pointer += sizeof(int);
				l = numLen(n, 16);
				scroll_check(l);
				printNum(n, l, 16);
				break;

			default:
				scroll_check(1);
				vga_print_char('%', X++, Y);
				break;
			}
		} else {
			if (curr == '\n') {
				scroll_check(LENGTH);
				Y++;
				X = 0;
			} else { 
				scroll_check(1);
				vga_print_char(curr, X++, Y);
			}
		}
	}
}

void __main(){
	init_printer();
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
	print("%s", s);
	// print("%%");

	// for(int i =0; i<40; i++){
	// 	for(int j = 0; j<i; j++){
	// 		print(" ");
	// 	}
	// 	print("%d\n", i);
	// }

	for (;;);
}

