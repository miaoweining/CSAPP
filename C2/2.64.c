#include <stdio.h>

int any_even_one(unsigned x);

//�ֳ�Ϊ32 
int any_even_one(unsigned x) {
	return !(x ^ 0xaaaaaaaa); 
}

int main() {
	printf("%d", any_even_one(0xaaaaaaac));
	
	return 0;
}
