#pragma once

#define SIZE 4000
#define START 0xB8000
#define LENGTH 80
#define HEIGHT 25

static int X;
static int Y;

void init_printer();
void mem_zero(short int  * start, int len);
void mem_cpy(short int  * src, short int  * dst, int len);
void vga_clear_screen();
void vga_print_char(char symbol, int x, int y);
void vga_print_str(char* str, int x, int y);
void scroll();
void scroll_check(int i);
void print(char* fmt, ...);
void printNum(int x, int len, int base);