#include <stdio.h>

/**
�߼�����ǰ�油0����������ǰ�油����λ 
*/

int int_shifts_are_logical();

// ���߼����Ʒ���1���������Ʒ���0 
int int_shifts_are_logical() {
	int x = -1; 
	int offset = (sizeof(int) << 3) - 1; 
	
	// ����һλ����ȡ��һλ 
	return !((x >> 1) & (0x1 << offset));
}

int main() {
	printf("%d", int_shifts_are_logical());
	
	return 0;
}
