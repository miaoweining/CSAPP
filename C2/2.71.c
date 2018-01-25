#include <stdio.h>
typedef unsigned packed_t;

/*
 * 使用int，将待抽取字节左移到最高字节，再右移到最低字节即可。
 */
int xbyte(packed_t word, int bytenum) {
	int ret = word << ((3 - bytenum)<<3);
	
    return ret >> 24;
} 

int main() {
	printf("%08x", xbyte(0x89abcdef, 1));
	
	return 0;
} 
