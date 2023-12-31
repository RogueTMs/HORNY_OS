#include "vga_funcs.h"
#include "utils_funcs.h"
#include "mem_funcs.h"


#define SIZE 4000
#define START 0xB8000
#define LENGTH 80
#define HEIGHT 25

static int X;
static int Y;


void init_printer(){
	X = 0;
	Y = 0;
	vga_clear_screen();
}


void vga_clear_screen(){
	short* start = (short*) START;
	myMemset(start, SIZE * sizeof(short));
	
}

void vga_print_char(char symbol, int x, int y){
	if (symbol != '\n') {
		short int bit_mask = 0b0000101000000000;
		bit_mask |= (short) symbol;
		*((short*) START + (y * LENGTH + x)) = bit_mask;  
	}
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

void scroll() {
	short* start = (short*) START;
	mem_cpy(start + LENGTH, start, sizeof(short) * (SIZE - LENGTH));
	myMemset(start + SIZE - LENGTH, sizeof(short) * LENGTH);
	// Y = HEIGHT - 1;
}

void scroll_check(int i) {
	int y = Y + (X + i) / LENGTH;
	// printNum(y, 2, 10);
	if (y >= HEIGHT) {
		int mod = ((X + i) % LENGTH == 0) ? 0 : 1;
		int diff = y - HEIGHT + mod;
		for (int i = 0; i < diff; i++) {
			scroll();
		}
		Y -= diff;
	}
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


void print_impl(char* fmt, char* ptr) {
    while (*fmt != '\0'){
        char curr = *fmt++;

        if (curr == '%') {
            int l;
            int n;
            switch (*fmt++)
            {
                case 's':
                    char* s = *((char**) ptr);
                    ptr += sizeof(char*);
                    l = len(s);
                    scroll_check(l);
                    vga_print_str(s, X, Y);
                    X = (X + l) % LENGTH;
                    break;
                case 'd':
                    n = *((int*) ptr);
                    ptr += sizeof(int);
                    l = numLen(n, 10);
                    scroll_check(l);
                    printNum(n, l, 10);
                    break;
                case 'x':
                    n = *((int*) ptr);
                    ptr += sizeof(int);
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


void print(char* fmt, ...){
	char* pointer = (void*) &fmt;
	pointer += sizeof(char*);
    print_impl(fmt, pointer);
}

