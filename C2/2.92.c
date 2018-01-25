#include <stdio.h>

typedef unsigned float_bits;

float_bits float_negate(float_bits f) {
	unsigned exp  = f >> 23 & 0xff; // 获取阶码 
	unsigned frac = f & 0x7fffff;
    
	// 如果是NaN，返回-f
	if((exp == 0xff) && (frac != 0)) {
		return f;
	} else {
		return f ^ 0x80000000;
	}
} 

int main() {
	printf("%08x", float_negate(0x6F800001));
	
	return 0;
} 
