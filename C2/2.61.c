#include <stdio.h>

/**
a==b 等价于 !(a^b) 
*/

int main() {
	int x = 0xff000000;
	int offset = (sizeof(int) - 1) << 3;
	
	// x的任何位都等于1
	printf("%d\n", !(x ^ (~0x0)));
	
	// x的任何位都等于0
	printf("%d\n", !(x ^ (0x0)));
	
	// x的最高有效字节中的位都等于1
	printf("%d\n", !((x & (0xFF << offset)) ^ (0xFF << offset)));
	
	// x的最低有效字节中的位都等于0 
	printf("%d\n", !((x & 0xFF) ^ 0x0));
	

	return 0;
} 
