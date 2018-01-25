#include <stdio.h>

unsigned rotate_right(unsigned x, int n) {
	unsigned left, right;
	int w = sizeof(unsigned) << 3;
	right = x >> n;
	left  = x << (w-n-1) << 1; // ±Ü¿ªn=0 
	
	return left | right;
}

int main() {
	printf("%08x", rotate_right(0x12345678, 0));
	
	return 0;
} 
