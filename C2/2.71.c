#include <stdio.h>
typedef unsigned packed_t;

/*
 * ʹ��int��������ȡ�ֽ����Ƶ�����ֽڣ������Ƶ�����ֽڼ��ɡ�
 */
int xbyte(packed_t word, int bytenum) {
	int ret = word << ((3 - bytenum)<<3);
	
    return ret >> 24;
} 

int main() {
	printf("%08x", xbyte(0x89abcdef, 1));
	
	return 0;
} 
