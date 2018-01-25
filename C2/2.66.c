#include <stdio.h>

// ×Ö³¤Îª32 
int leftmost_one(unsigned x) {
	x |= (x >> 1);
    x |= (x >> 2);
    x |= (x >> 4);
    x |= (x >> 8);
    x |= (x >> 16);
    return x^(x>>1);
}

int main() {
	printf("%08x", leftmost_one(0x6600)); 
	return 0;
} 
