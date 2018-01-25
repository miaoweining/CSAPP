#include <stdio.h>

// 计算x和y的乘积的高w位 
unsigned unsigned_high_prod(unsigned x, unsigned y) {
	int w = sizeof(int)<<3;
    return signed_high_prod(x, y) + (x>>(w-1))*y + x*(y>>(w-1));
}

int main() {
	printf("%d", staurating_add());
	
	return 0;
} 
