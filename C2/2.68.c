#include <stdio.h>

int lower_bits(int x, int n) {
	return (2 << (n-1)) - 1;
}

int main() {
	printf("%08x", lower_bits(0, 32));
	
	return 0;
}
