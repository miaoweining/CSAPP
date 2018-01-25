#include <stdio.h>

// �ֳ�Ϊ32 
/**
 * x��ÿ��λ����������Ϊ0��˵����ż����1�����Ϊ1����������1��
 * ��ô�����뵽�۰���С��ģ�����һ��Ҳ������ return (x^1)&1
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
