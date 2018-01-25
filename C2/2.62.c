#include <stdio.h>

/**
逻辑右移前面补0，算术右移前面补符号位 
*/

int int_shifts_are_logical();

// 是逻辑右移返回1，算术右移返回0 
int int_shifts_are_logical() {
	int x = -1; 
	int offset = (sizeof(int) << 3) - 1; 
	
	// 右移一位，截取第一位 
	return !((x >> 1) & (0x1 << offset));
}

int main() {
	printf("%d", int_shifts_are_logical());
	
	return 0;
}
