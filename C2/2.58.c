#include <stdio.h>

int is_little_endian();

int main() {
	printf("%d", is_little_endian());
	
	return 0;
}

int is_little_endian() {
	int a = 1;
	
	return *((char*)&a);
	// 大端法返回0，小端法返回1，原因在于ASCII码不管是大端法还是小端法的表示形式都一样 
}
