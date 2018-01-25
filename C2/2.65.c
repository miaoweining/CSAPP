#include <stdio.h>

// 字长为32 
/**
 * x的每个位进行异或，如果为0就说明是偶数个1，如果为1就是奇数个1。
 * 那么可以想到折半缩小规模。最后一句也可以是 return (x^1)&1
 */

int even_ones(unsigned x) {
	x ^= (x >> 16);
    x ^= (x >> 8);
    x ^= (x >> 4);
    x ^= (x >> 2);
    x ^= (x >> 1);
    
    return !(x&1);
}

int main() {
	printf("%d", even_ones(3)); 
	return 0;
} 
