#include <stdio.h>

/**
a==b �ȼ��� !(a^b) 
*/

int main() {
	int x = 0xff000000;
	int offset = (sizeof(int) - 1) << 3;
	
	// x���κ�λ������1
	printf("%d\n", !(x ^ (~0x0)));
	
	// x���κ�λ������0
	printf("%d\n", !(x ^ (0x0)));
	
	// x�������Ч�ֽ��е�λ������1
	printf("%d\n", !((x & (0xFF << offset)) ^ (0xFF << offset)));
	
	// x�������Ч�ֽ��е�λ������0 
	printf("%d\n", !((x & 0xFF) ^ 0x0));
	

	return 0;
} 
