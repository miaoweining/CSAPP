#include <stdio.h>
#include <math.h>

int sra(int x, int k);
unsigned srl(unsigned x, int k);

int sra(int x, int k) {
	// 用逻辑右移（由值xsrl给出）完成算术右移 
	int xsrl = (unsigned) x >> k;
	int w    = sizeof(int) << 3;    // 获得字长 
    unsigned z     = 1 << (w-k-1);   
    unsigned mask  = z - 1;         // 获得符号位后全为1的mask 
    unsigned right = mask & xsrl;   // 符号位及以前全部置零 
    unsigned left  = ~mask & (~(z&xsrl) + z); // 巧妙利用溢出获得符号位，补全符号位及之前
    return left | right; // 左右组合 
}

unsigned srl(unsigned x, int k) {
	// 用算术右移（由值xsra给出）完成逻辑右移 
	unsigned xsra = (int) x >> k;
	int w         = sizeof(int) << 3;    // 获得字长 
	unsigned z    = 2 << (w-k-1);        // 用1的话，k=0会出错 
	unsigned mask = z-1;
	
	return xsra & mask;
} 

int main() {
	unsigned x = srl(0x80000000, 0);
	
	printf("%d\n", 0x80000000);
	printf("%08x\n", x); 
	
	return 0;
}
