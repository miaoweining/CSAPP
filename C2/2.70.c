#include <stdio.h>

int fits_bits(int x, int n) {
	x >>= (n-1);
    return !x || !(~x);
}

int main() {
	printf("%d", fits_bits(0x0, 1));
	return 0;
} 
