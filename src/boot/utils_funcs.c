#include "utils_funcs.h"

int len(char* s) {
	int i = 0;
	while (s[i++] != '\0');
	return i -1;
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
	if (x == 0) {
		return 1;
	}
	int c = x;
	int len = 0;
	while (c > 0) {
		c /= base;
		len++;
	}
	return len;
}