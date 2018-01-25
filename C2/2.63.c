#include <stdio.h>
#include <math.h>

int sra(int x, int k);
unsigned srl(unsigned x, int k);

int sra(int x, int k) {
	// ���߼����ƣ���ֵxsrl����������������� 
	int xsrl = (unsigned) x >> k;
	int w    = sizeof(int) << 3;    // ����ֳ� 
    unsigned z     = 1 << (w-k-1);   
    unsigned mask  = z - 1;         // ��÷���λ��ȫΪ1��mask 
    unsigned right = mask & xsrl;   // ����λ����ǰȫ������ 
    unsigned left  = ~mask & (~(z&xsrl) + z); // �������������÷���λ����ȫ����λ��֮ǰ
    return left | right; // ������� 
}

unsigned srl(unsigned x, int k) {
	// ���������ƣ���ֵxsra����������߼����� 
	unsigned xsra = (int) x >> k;
	int w         = sizeof(int) << 3;    // ����ֳ� 
	unsigned z    = 2 << (w-k-1);        // ��1�Ļ���k=0����� 
	unsigned mask = z-1;
	
	return xsra & mask;
} 

int main() {
	unsigned x = srl(0x80000000, 0);
	
	printf("%d\n", 0x80000000);
	printf("%08x\n", x); 
	
	return 0;
}
