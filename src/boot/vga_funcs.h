#pragma once

void init_printer();
void vga_clear_screen();
void vga_print_char(char symbol, int x, int y);
void vga_print_str(char* str, int x, int y);
void scroll();
void scroll_check(int i);
void print(char* fmt, ...);
void printNum(int x, int len, int base);
void print_impl(char* fmt, char* ptr);