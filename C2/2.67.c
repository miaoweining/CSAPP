#include <stdio.h>

// 字长为32 
int int_size_is_32() {
	int set_msb = 1 << 31;
	int beyond_msb = 2 << 31;
    return set_msb && !beyond_msb;
}

// 字长为16
int int_size_is_16() {
	int a = 1 << 15;
	a <<= 15;
	int set_msb = a << 1;
	int beyond_msb = a << 2;
    return set_msb && !beyond_msb;
}

int main() {
	printf("%08x", int_size_is_32()); 
	return 0;
} 
