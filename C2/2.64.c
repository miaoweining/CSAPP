#include <stdio.h>

int any_even_one(unsigned x);

//×Ö³¤Îª32 
int any_even_one(unsigned x) {
	return !(x ^ 0xaaaaaaaa); 
}

int main() {
	printf("%d", any_even_one(0xaaaaaaac));
	
	return 0;
}
