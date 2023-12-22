#include "console.h"
#include "mem_funcs.h"
#include "utils_funcs.h"

#define START 0xB8000
#define SCREEN_LENGTH 80
#define SCREEN_HEIGHT 25

short int bit_mask;

static void scroll(console* cnsl) {
    u16* start = cnsl->start;
    for (u32 i = 1; i < cnsl->HEIGHT; i++) {
        mem_cpy(cnsl->start + SCREEN_LENGTH * i,cnsl->start + SCREEN_LENGTH * (i - 1), sizeof(u16) * cnsl->LENGTH);
    }
    myMemset(cnsl->start + SCREEN_LENGTH * (cnsl->HEIGHT - 1), sizeof(u16) * cnsl->LENGTH);
}

static void scroll_check(console* cnsl) {
	if (cnsl->Y >= cnsl->HEIGHT) {
        scroll(cnsl);
        cnsl->Y--;
	}
}

static void check_newline(console* cnsl) {
    if (cnsl->X >= cnsl->LENGTH) {
        cnsl->Y++;
        scroll_check(cnsl);
        cnsl->X = 0;
    }
}

static void clear_console(console* cnsl) {
    u16* start = cnsl->start;
    for (u32 i = 0; i < cnsl->HEIGHT; i++) {
        myMemset(start, sizeof(u16) * cnsl->LENGTH);
        start += SCREEN_LENGTH;
    }
}


void init_console(console* cnsl, u32 shift_X, u32 shift_Y, u32 HEIGHT, u32 LENGTH, u16 color_mask){
    cnsl->start = (short*) START + shift_X + shift_Y * SCREEN_LENGTH;
    cnsl->HEIGHT = HEIGHT;
    cnsl->LENGTH = LENGTH;
    cnsl->X = 0;
    cnsl->Y = 0;
    cnsl->color_mask = color_mask;
}

static void console_print_char(console* cnsl, char symbol){
    if (symbol != '\n') {
        short int bit_mask = cnsl->color_mask;
        bit_mask |= (short) symbol;
        check_newline(cnsl);
        *(cnsl->start + cnsl->Y * SCREEN_LENGTH + cnsl->X) = bit_mask;
        cnsl->X++;
    }
}

static void console_print_str(console* cnsl, char* str) {
    u32 index = 0;
    while (str[index] != '\0') {
        if (str[index] == '\n') {
            cnsl->X = cnsl->LENGTH;
        }
        console_print_char(cnsl, str[index]);
        index++;
    }
}



static void printNum(console* cnsl, int x, int base) {
	u32 len = numLen(x, base);
	if (base == 10) {
		if (x < 0) {
			console_print_char(cnsl, '-');
			x *= -1;
		}
	}
	while (len > 0) {
		int p = power(base, --len);
		int curr = x / p;
		char c_curr;
		if (curr < 10) {
			c_curr = '0' + curr;
		} else {
			c_curr = 'A' + curr - 10;
		}
		console_print_char(cnsl, c_curr);
		x %= p;
	}
}


void console_print(console* cnsl, char* fmt, ...) {
	char* pointer = (void*) &fmt;
	pointer += sizeof(char*);
    while (*fmt != '\0'){
    char curr = *fmt++;

        if (curr == '%') {
            int l;
            int n;
            switch (*fmt++) {
                case 's':
                    char* s = *((char**) pointer);
                    pointer += sizeof(char*);
                    console_print_str(cnsl, s);

                    break;
                case 'd':
                    n = *((int*) pointer);
                    pointer += sizeof(int);
                    printNum(cnsl, n, 10);
                    break;
                case 'x':
                    n = *((int*) pointer);
                    pointer += sizeof(int);;
                    printNum(cnsl, n, 16);
                    break;

                default:
                    console_print_char(cnsl, '%');
                    break;
            }
        } else {
            console_print_char(cnsl, curr);
        }
    }
}
