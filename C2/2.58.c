#include <stdio.h>

int is_little_endian();

int main() {
	printf("%d", is_little_endian());
	
	return 0;
}

int is_little_endian() {
	int a = 1;
	
	return *((char*)&a);
	// ��˷�����0��С�˷�����1��ԭ������ASCII�벻���Ǵ�˷�����С�˷��ı�ʾ��ʽ��һ�� 
}
