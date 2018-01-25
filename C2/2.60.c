#include <stdio.h>

unsigned replace_byte (unsigned x, unsigned char b, int i) {
	unsigned result = 0;
	
	return (x & ~(0xff << (i << 3))) | (b << (i << 3));
}

int main() {
	
	printf("%08x\n", replace_byte (0x12345678, 0xab, 2));
	printf("%08x", replace_byte (0x12345678, 0xab, 0));
	return 0;
} 
