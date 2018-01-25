#include <stdio.h>

int main() {
	
	unsigned x = 0x89abcdef, y = 0x765432ef, tmpx, tmpy;
	
	printf("%x\n", (x&0xFF) | (y&~0xFF));
	
	return 0;
} 
